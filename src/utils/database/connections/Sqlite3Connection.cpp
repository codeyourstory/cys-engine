#include <cys-engine/utils/database/connections/Sqlite3Connection.h>
#include <stdio.h>
#include <string.h>

using namespace cys;
using namespace cys::data;
using namespace cys::database;

#define verify_err() if(err) {\
    printf("SQL: failure with request '%s'\n", query.c_str());\
    printf("SQL Error: %s\n", err);\
    sqlite3_free(err);\
  }

namespace cys {
namespace database {
  
struct TmpStruct {
  SQLite3Connection *connection;
  data::DataType *table_info;
  Entity *data;
  bool loaded;

  // for multiple loading
  std::vector<Entity *> *vect;
};

int callback_load(void *data, int argc, char **argv, char **colname)
{
  TmpStruct *tmp = (TmpStruct *) data;
  std::map<std::string, data::VariableDefinition> *vars;
  data::VariableDefinition var;
  char *p;

  vars = tmp->table_info->get_vars();
  
  /*for(auto it = vars->begin(), end = vars->end(); it != end; it++) {
    printf("VARS: %s\n", it->first.c_str());
  }*/
  
  // on parcourt les arguments
  for(int i = 0; i < argc; i++) {
    
    // 1) on récupère l'info sur la variable
    if(vars->find(colname[i]) != vars->end()) {
      var = (*vars)[colname[i]];

      // 2) on place le pointeur p à la bonne position
      p = (char *) tmp->data;
      p += var.offset;

      //printf("variable: %s\n", colname[i]);
      // 3) on récupère le contenu de la variable
      tmp->connection->str_to_variable(var.type, std::string(argv[i]), p);
    }
    else {
      printf("colonne %s non trouvée dans le descripteur\n", colname[i]);
    }
  }
  
  tmp->loaded = true;

  // voilà, data a été complété

  return 0;
}

int callback_load_multiple(void *data, int argc, char **argv, char **colname)
{
  TmpStruct *tmp = (TmpStruct *) data;
  EntityFactory fn_ptr = *(tmp->table_info->get_factory());
  
  Entity *p = fn_ptr();
  p->_set_datatype(tmp->table_info);
  tmp->data = p;
  printf("call back load multiple: %c [", argc);
  for(int i = 0; i < argc; i++) printf("%s , ", colname[i]);
  printf("]\n");
  callback_load(data, argc, argv, colname);
  
  tmp->vect->push_back(p);

  return 0;
}

int callback_get_max_id(void *data, int argc, char **argv, char **colname)
{
  int *p = (int *) data;

  for(int i = 0; i < argc; i++) {
    if(!strcmp(colname[i], "id")) {
      sscanf(argv[i], "%d", p); // on récupère l'ID
    }
    else;
  }

  return 0;
}

}
}

SQLite3Connection::SQLite3Connection(const char *filename)
{
  if(sqlite3_open(filename, &_db)) {
    // failure to open db
    fprintf(stderr, "database/Sqlite3: can't open '%s'\n", filename);
    _db = nullptr;
  }
  else;
}

SQLite3Connection::~SQLite3Connection()
{
  sqlite3_close(_db);
}

void SQLite3Connection::set_db(sqlite3 *db)
{
  _db = db;
}

sqlite3 *SQLite3Connection::get_db()
{
  return _db;
}

int SQLite3Connection::execute(std::string sql)
{
  char *err_msg = NULL;
  int ret;

  ret = sqlite3_exec(_db, sql.c_str(), NULL, NULL, &err_msg) == SQLITE_ABORT;

  if(err_msg)
    printf("err_msg: %s | %s\n", err_msg, sql.c_str());
  else;

  return ret;
}

int SQLite3Connection::execute_file(std::string filename)
{
  FILE *f = fopen(filename.c_str(), "r");

  if(!f) {
    printf("Script '%s' non trouvé", filename.c_str());
    return 1;
  }
  else;

  char *mem;
  int l;

  fseek(f, 0, SEEK_END);
  l = ftell(f);
  fseek(f, 0, SEEK_SET);

  mem = (char *) malloc(l + 1);
  mem[l] = 0; // '\0'

  fread(mem, 1, l, f);

  fclose(f);

  int ret = this->execute(mem) == SQLITE_ABORT;

  free(mem);

  return ret;
}

Entity *SQLite3Connection::load_single(std::string query, data::DataType *table)
{
  char *err;
  TmpStruct tmp;
  EntityFactory factory_ptr = *(table->get_factory());
  Entity *dest = factory_ptr();
  dest->_set_datatype(table);

  tmp.connection = this;
  tmp.data = dest;
  tmp.table_info = table;
  tmp.loaded = false;
  
  std::string sql = "SELECT * FROM " + *(table->get_name());
  if(query.length() > 0)
    sql += " WHERE " + query;
  
  //printf("%s\n", sql.c_str());

  // exec requete

  sqlite3_exec(_db, 
    sql.c_str(),
    ::cys::database::callback_load, &tmp, &err);
  
  if(!tmp.loaded) {
    free(dest);
    dest = nullptr;
  }

  verify_err()
  
  return dest;
}
std::vector<Entity *> SQLite3Connection::load_multiple(std::string query, data::DataType *table)
{   
  char *err;
  TmpStruct tmp;
  std::vector<Entity *> vect;
  //void *dest = calloc(1, info->size);

  tmp.connection = this;
  //tmp.data = dest;
  tmp.vect = &vect;
  tmp.table_info = table;
  
  std::string sql = "SELECT * FROM " + *(table->get_name());
  if(query.length() > 0)
    sql += " WHERE " + query;
  
  // exec requete

  sqlite3_exec(_db, 
    sql.c_str(),
    ::cys::database::callback_load_multiple, &tmp, &err);

  verify_err()
  
  return vect;
}

int  SQLite3Connection::insert(data::DataType *table, Entity *data)
{
  std::map<std::string, data::VariableDefinition>::iterator it = table->get_vars()->begin();
  std::map<std::string, data::VariableDefinition>::iterator end = table->get_vars()->end();
  
  std::string req = "INSERT INTO ";
  req += *(table->get_name());
  req += "(";
  
  for(; it != end; it++) {
    req += it->first;
    req += ",";
  }
  
  req.erase(req.length() - 1, 1);
  req += ") VALUES (";
  
  char *p = (char *) data;
  it = table->get_vars()->begin();
  
  for(; it != end; it ++) {
    req += this->variable_to_str(it->first, it->second.type, &p[it->second.offset]);
    req += ",";
  }
  
  req.erase(req.length() - 1, 1);
  req += ");";
  
  //printf("request: %s\n", req.c_str());
  
  return this->execute(req.c_str());
}
void SQLite3Connection::update(data::DataType *table, Entity *data)
{
  char *err;
  char *p = (char *) data;
  Sint32 *t;
  std::string req = "UPDATE ";
  req += *(table->get_name());
  
  // on met les variables

  req += " SET ";
  int nb = (*(table->get_vars())).size();
  std::map<std::string, data::VariableDefinition>::iterator itr, itrend;

  int i = 0;
  nb --;

  for(itr = (*(table->get_vars())).begin(), itrend = (*(table->get_vars())).end(); (itr != itrend) && (i < nb); itr++) {
    req += itr->first;
    req += " = ";
    req += this->variable_to_str(itr->first, itr->second.type, p + itr->second.offset);
    req += ", ";
    i ++;
  }

  req += itr->first;
  req += " = ";
  req += this->variable_to_str(itr->first, itr->second.type, p + itr->second.offset);
  
  req += " WHERE id = ";
  t = (Sint32 *) &p[(*(table->get_vars()))["id"].offset];
  
  req += this->variable_to_str("id", (*(table->get_vars()))["id"].type, t);
  req += ";";

  // exec requete

  sqlite3_exec(_db, 
    req.c_str(),
  NULL, NULL, &err);
#define query req
 verify_err()
}

int SQLite3Connection::get_max_id(std::string tablename)
{
  int id = 0;
  std::string query;
  
  query = "SELECT id FROM ";
  query += tablename;
  query += " ORDER BY id DESC LIMIT 1;";
  
  char *err;
  
  sqlite3_exec(_db, 
    query.c_str(),
    ::cys::database::callback_get_max_id, &id, &err);
  
  verify_err()
  
  return id;
}
