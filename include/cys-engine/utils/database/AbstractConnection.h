#ifndef CYS_ENGINE__UTILS_DATABASE_ABSTRACTCONNECTION_H
#define	CYS_ENGINE__UTILS_DATABASE_ABSTRACTCONNECTION_H

/*
 Each table MUST have a PRIMARY KEY of INTEGER type CALLED id.
 */

#include <vector>
#include <string>
#include <map>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace database {
 
 class AbstractConnection {
 public:
      AbstractConnection();
      virtual ~AbstractConnection();

      virtual int execute(std::string sql) = 0;
      virtual int execute_file(std::string filename) = 0;

      virtual data::Entity *load_single(std::string query, data::DataType *table) = 0;
      virtual std::vector<data::Entity *>load_multiple(std::string query, data::DataType *table) = 0;

      virtual int  insert(data::DataType *table, data::Entity *data) = 0;
      virtual void update(data::DataType *table, data::Entity *data) = 0;
      
      virtual int get_max_id(std::string tablename) = 0;

      std::string variable_to_str(std::string varname, data::VariableType type, void *var);
      void str_to_variable(data::VariableType type, std::string str, void *var);
private:

      std::string _convert_str_to_db_str(std::string to_convert);
      std::string _convert_db_str_to_str(std::string to_convert);
 }; 
  
}
}

#endif
