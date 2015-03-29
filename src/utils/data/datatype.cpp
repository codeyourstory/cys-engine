#include <cys-engine/utils/data/datatype.h>
#include <string.h>

using namespace cys;
using namespace cys::data;

VariableDefinition::VariableDefinition()
{ 
  this->offset = 0;
  this->type = UNKNOWN;
}

VariableDefinition::VariableDefinition(VariableType type, cys::Uint32 offset)
{
  this->offset = offset;
  this->type = type;
}

Entity::Entity(DataType *datatype)
{
  _datatype = datatype;
}

Entity::~Entity()
{
  
}

void Entity::set(std::string name, void *p)
{
  cys::Uint8 *q = nullptr;
  std::string *current, *target;
  
  
  if(_datatype && 
     _datatype->get_vars()->find(name) != _datatype->get_vars()->end()) {
    VariableDefinition vardef = _datatype->get_vars()->at(name);
    q = (cys::Uint8 *) this;
    q += vardef.offset;
    
   switch(vardef.type) {
     case UINT8:
       memcpy(q, p, 1);
       break;
     case UINT16:
       memcpy(q, p, 2);
       break;
     case UINT32:
       memcpy(q, p, 4);
       break;
     case UINT64:
       memcpy(q, p, 8);
       break;
     case SINT8:
       memcpy(q, p, 1);
       break;
     case SINT16:
       memcpy(q, p, 2);
       break;
     case SINT32:
       memcpy(q, p, 4);
       break;
     case SINT64:
       memcpy(q, p, 8);
       break;
     case FLOAT:
       memcpy(q, p, sizeof(float));
       break;
     case DOUBLE:
       memcpy(q, p, sizeof(double));
       break;
     case STRING:
       current = (std::string *) p;
       target = (std::string *) q;
       *target = *current;
       break;
     default:
       break;
   }
  }
  
}

void *Entity::get(std::string name)
{
  cys::Uint8 *ret = nullptr;
  
  if(_datatype && 
     _datatype->get_vars()->find(name) != _datatype->get_vars()->end()) {
    VariableDefinition vardef = _datatype->get_vars()->at(name);
    ret = (cys::Uint8 *) this;
    ret += vardef.offset;
  }
  
  return ret;
}

void Entity::_set_datatype(DataType *datatype)
{
  _datatype = datatype;
}

// --

ACCESS_DECL(DataType, name, std::string)
ACCESS_DECL(DataType, factory, EntityFactory)
ACCESS_DECL(DataType, vars, VariableDefAssoc)

DataType::DataType(std::string name, Entity *(*factory_ptr)())
{
  _name = name;
  _factory = factory_ptr;
}

DataType::~DataType()
{
  
}

void DataType::define_var(std::string name, VariableType type, void *struct_addr, void *struct_var_addr)
{
  cys::Uint8 *p1, *p2;
  p2 = (cys::Uint8 *) struct_addr;
  p1 = (cys::Uint8 *) struct_var_addr; 
  this->_vars.insert(
    std::make_pair(
      name,
      cys::data::VariableDefinition(type, p1 - p2)
    )
  );
}
