#ifndef CYS_ENGINE__UTILS_DATABASE_CONNECTIONS_SQLITE3CONNECTION_H
#define	CYS_ENGINE__UTILS_DATABASE_CONNECTIONS_SQLITE3CONNECTION_H

#include <cys-engine/utils/database/AbstractConnection.h>
#include <sqlite3.h>
#include <string>

namespace cys {
namespace database {

  class SQLite3Connection : public AbstractConnection {
    public:

      SQLite3Connection(const char *filename);
      virtual ~SQLite3Connection();

      void set_db(sqlite3 *db);
      sqlite3 *get_db();

      int execute(std::string sql);
      int execute_file(std::string filename);

      virtual data::Entity *load_single(std::string query, data::DataType *table);
      virtual std::vector<data::Entity *> load_multiple(std::string query, data::DataType *table);

      int  insert(data::DataType *table, data::Entity *data);
      void update(data::DataType *table, data::Entity *data);
      
      int get_max_id(std::string tablename);
      
      /*
      void remove(std::string query);
      */

    protected:

      sqlite3 *_db;

  };

}
}

#endif
