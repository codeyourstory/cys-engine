#ifndef CYS_ENGINE__UTILS_DATA_DATATYPE_H
#define CYS_ENGINE__UTILS_DATA_DATATYPE_H

#include <cys-engine/utils/types.h>
#include <cys-engine/utils/macros.h>

#include <string>
#include <map>

namespace cys {
namespace data {

  enum VariableType {
    UNKNOWN = 0,
    UINT8   = 1,
    UINT16  = 2,
    UINT32  = 3,
    UINT64  = 4,
    SINT8   = 5,
    SINT16  = 6,
    SINT32  = 7,
    SINT64  = 8,
    FLOAT   = 9,   // on 4 bytes
    DOUBLE  = 10,  // on 8 bytes
    STRING  = 11   // std::string
  };

  struct VariableDefinition {
    VariableType type;
    cys::Uint32 offset;
    
    VariableDefinition();
    VariableDefinition(VariableType type, cys::Uint32 offset);
  };

  class DataType;
  
  // 
  class Entity {
  public:
    Entity(DataType *datatype);
    virtual ~Entity();
    
    void set(std::string name, void *p); // p is a pointer on the value
    void *get(std::string name); // returns a pointer to the value
    
    void _set_datatype(DataType *datatype);
    
  protected:
    DataType *_datatype;
  };
  
  typedef std::map<std::string, VariableDefinition> VariableDefAssoc;
  typedef Entity *(*EntityFactory)();
  
  class DataType {
    
  public:
    
    DataType(std::string name, Entity *(*factory_ptr)());
    ~DataType();
    
    void define_var(std::string name, VariableType type, void *struct_addr, void *struct_var_addr);
    
    ACCESS_DEF(name, std::string)
    ACCESS_DEF(factory, EntityFactory)
    ACCESS_DEF(vars,  VariableDefAssoc)
    
  private:
    std::string _name; // table name for sql, could be used in other classes
    Entity *(*_factory)();
    
    VariableDefAssoc _vars; // définition des variables/types
    
  };
  
}
}

// Macros to create faster the DataType classes
#define DATA(ClassName) ClassName##DataType

#define DATA_DEF(ClassName) \
class DATA(ClassName) : public cys::data::DataType {\
  public:\
    ClassName##DataType();\
  };
  
#define DATA_DECL(ClassName, TableName, CODE)\
DATA(ClassName)::DATA(ClassName)() : cys::data::DataType(TableName, (EntityFactory) FACTORY(ClassName) ) { \
  ClassName t;\
  CODE\
}

#define DATA_DEF_VAR(varname, type) \
this->define_var(#varname, type, &t, t.get_##varname());

#endif
