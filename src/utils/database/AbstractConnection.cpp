#include <sstream>
#include <string>
#include <cys-engine/utils/database/AbstractConnection.h>

using namespace cys;
using namespace cys::database;

AbstractConnection::AbstractConnection()
{
  
}

AbstractConnection::~AbstractConnection()
{
  
}

std::string AbstractConnection::variable_to_str(std::string varname, data::VariableType type, void *var)
{
  std::string str;
  std::ostringstream o;

  switch(type) {
    case data::UINT8:
      o << (int) *((Uint8 *) var); // else it is read as an char *
      str = o.str();
      break;
    case data::UINT16:
      o << *((Uint16 *) var);
      str = o.str();
      break;
    case data::UINT32:
      o << *((Uint32 *) var);
      str = o.str();
      break;
    case data::UINT64:
      o << *((Uint64 *) var);
      str = o.str();
      break;
    case data::SINT8:
      o << (int) *((Sint8 *) var); // else it is read as an char *
      str = o.str();
      break;
    case data::SINT16:
      o << *((Sint16 *) var);
      str = o.str();
      break;
    case data::SINT32:
      o << *((Sint32 *) var);
      str = o.str();
      break;
    case data::SINT64:
      o << *((Sint64 *) var);
      str = o.str();
      break;
    case data::FLOAT:
      o << *((float *) var);
      str = o.str();
      break;
    case data::DOUBLE:
      o << *((double *) var);
      str = o.str();
      break;
    case data::STRING:
      str = "'";
      str += this->_convert_str_to_db_str(*((std::string *) var));
      str += "'";
      break;
    default:
      printf("/!\\DBConnection::Variable_To_Str: %s of unknown type '%d' !\n", varname.c_str(), type);
      break;
  }

  return str;
}

void AbstractConnection::str_to_variable(data::VariableType type, std::string str, void *var)
{
  std::string *s;
  Uint16 c;
  
  switch(type) {
    case data::UINT8:
      std::istringstream ( str ) >> c;
      *((Uint8 *) var) = (Uint8) c;
      break;
    case data::UINT16:
      std::istringstream ( str ) >> *((Uint16 *) var);
      break;
    case data::UINT32:
      std::istringstream ( str ) >> *((Uint32 *) var);
      break;
    case data::UINT64:
      std::istringstream ( str ) >> *((Uint64 *) var);
      break;
    case data::SINT8:
      std::istringstream ( str ) >> c;
      *((Sint8 *) var) = (Sint8) c;
      break;
    case data::SINT16:
      std::istringstream ( str ) >> *((Sint16 *) var);
      break;
    case data::SINT32:
      std::istringstream ( str ) >> *((Sint32 *) var);
      break;
    case data::SINT64:
      std::istringstream ( str ) >> *((Sint64 *) var);
      break;
    case data::FLOAT:
      std::istringstream ( str ) >> *((float *) var);
      break;
    case data::DOUBLE:
      std::istringstream ( str ) >> *((double *) var);
      break;
    case data::STRING:
      str = this->_convert_db_str_to_str(str);
      
      s = (std::string *) var;
      new (s) std::string(str);
      
      break;
    default:
      printf("/!\\DBConnection::Str_To_Variable: Type inconnu %d !\n", type);
      break;
  }
}

std::string AbstractConnection::_convert_str_to_db_str(std::string to_convert)
{
  std::string str;
  uint32_t i;

  for(i = 0; i < to_convert.size(); i++) {
    if(to_convert[i] == '\'') {
      str += "''";
    }
    else
      str += to_convert[i];
  }

  return str;
}

std::string AbstractConnection::_convert_db_str_to_str(std::string to_convert)
{
  std::string str;
  uint32_t i;

  for(i = 0; i < to_convert.size(); i++) {
    if(to_convert[i] == '\'') {
      if(to_convert[i + 1] == '\'')
        str += "'";
    }
    else
      str += to_convert[i];
  }

  return str;
}
