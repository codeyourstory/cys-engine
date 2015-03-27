#ifndef CYS_ENGINE__UTILS_DATA_DATATYPE_H
#define CYS_ENGINE__UTILS_DATA_DATATYPE_H

#include <cys-engine/utils/types.h>
#include <cys-engine/utils/macros.h>

#include <string>
#include <map>

namespace cys {
namespace data {

  enum VariableType {
    Unknow = 0,
    UINT8  = 1,
    UINT16 = 2,
    UINT32 = 3,
    UINT64 = 4,
    SINT8  = 5,
    SINT16 = 6,
    SINT32 = 7,
    SINT64 = 8,
    FLOAT  = 9,   // on 4 bytes
    DOUBLE = 10,  // on 8 bytes
    STRING = 11   // std::string
  };

  struct VariableDefinition {
    VariableType type;
    std::string name;
    
    VariableDefinition();
    VariableDefinition(VariableType type, cys::Uint32 offset);
  };

  // 
  class Entity {
  public:
    virtual ~Entity();
    
    virtual void set(std::string name, void *p) = 0; // p is a pointer on the value
    virtual void *get(std::string name) = 0; // returns a pointer to the value
  };
  
  typedef std::map<std::string, VariableDefinition> VariableDefAssoc;
  
  class DataType {
    
  public:
    
    DataType();
    ~DataType();
    
    void define_var(std::string name, VariableType type);
    
    ACCESS_DEF(name, std::string)
    ACCESS_DEF(vars,  VariableDefAssoc)
    
  private:
    std::string name; // table name for sql, could be used in other classes
    Entity *(*factory)();
    
    VariableDefAssoc vars; // définition des variables/types
    
  };
  
}
}

// Macros to create faster the DataType classes
#define DATA(ClassName) ClassName##DataType

#define DATA_DEF(ClassName) \
class DATA(ClassName) : public nge::data::DataType {\
  public:\
    ClassName##DataType();\
  };\
  
#define DATA_DECL(ClassName, TableName, CODE)\
DATA(ClassName)::DATA(ClassName)() { \
  CODE\
  this->name = TableName ;  \
}

#define DATA_DEF_VAR(varname, type) \
this->define_var(#varname, type);

#endif
