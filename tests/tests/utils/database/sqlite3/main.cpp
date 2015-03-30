/*
 Test of utils/data/datatype.h classes
 
 Don't forget to prefix '_' the attributes of the entity ! 
 
 */

#include <cys-engine/utils/data/datatype.h>
#include <string>

using namespace cys;
using namespace cys::data;
using namespace std;

// definition of the datatype
DATA_DEF(TestEntity)
// definition of our entity

class TestEntity : public Entity {
public:
  
  TestEntity();
  ~TestEntity();
    
  ACCESS_DEF(u8, Uint8)
  ACCESS_DEF(u16, Uint16)
  ACCESS_DEF(u32, Uint32)
  ACCESS_DEF(u64, Uint64)
  
  ACCESS_DEF(s8, Sint8)
  ACCESS_DEF(s16, Sint16)
  ACCESS_DEF(s32, Sint32)
  ACCESS_DEF(s64, Sint64)
  
  ACCESS_DEF(str, string)
  
private:
  
  Uint8 _u8;
  Uint16 _u16;
  Uint32 _u32;
  Uint64 _u64;
  Sint8 _s8;
  Sint16 _s16;
  Sint32 _s32;
  Sint64 _s64;
  std::string _str;
  
};

// constructor, destructor

TestEntity::TestEntity() : Entity(nullptr)
{
  _u8 = 0;
  _u16 = 0;
  _u32 = 0;
  _u64 = 0;
  _s8 = 0;
  _s16 = 0;
  _s32 = 0;
  _s64 = 0;
  // _str is egal to "" thanks to its constructor
}

TestEntity::~TestEntity()
{
}

// Full declaration of the entity
  
ACCESS_DECL(TestEntity, u8, Uint8)
ACCESS_DECL(TestEntity, u16, Uint16)
ACCESS_DECL(TestEntity, u32, Uint32)
ACCESS_DECL(TestEntity, u64, Uint64)

ACCESS_DECL(TestEntity, s8, Sint8)
ACCESS_DECL(TestEntity, s16, Sint16)
ACCESS_DECL(TestEntity, s32, Sint32)
ACCESS_DECL(TestEntity, s64, Sint64)

ACCESS_DECL(TestEntity, str, string)

// Declare the factory
FACTORY_DECL(TestEntity)

// Now the Datatype
DATA_DECL(TestEntity, "test_entity", 
  DATA_DEF_VAR(u8,  UINT8)
  DATA_DEF_VAR(u16, UINT16)
  DATA_DEF_VAR(u32, UINT32)
  DATA_DEF_VAR(u64, UINT64)

  DATA_DEF_VAR(s8,  SINT8)
  DATA_DEF_VAR(s16, SINT16)
  DATA_DEF_VAR(s32, SINT32)
  DATA_DEF_VAR(s64, SINT64)

  DATA_DEF_VAR(str, STRING)
)

// -----

#define ASSERT_OK(val) if(val); else { printf("test_failed line %d of file %s\n", __LINE__, __FILE__);exit(1); }

int main(int argc, char** argv)
{
  DATA(TestEntity) myDatatype;
  TestEntity my_entity;
  
  my_entity._set_datatype(&myDatatype); // don't forget this !
  
  // 1) we test my_entity.set_X(Y) and my_entity.get_X(Y) 
#define TEST_ENTITY_SET(varname, val) \
  my_entity.set_##varname(val); \
  ASSERT_OK(*(my_entity.get_##varname()) == val)
  
  TEST_ENTITY_SET(u8, 5)
  TEST_ENTITY_SET(u16, 6)
  TEST_ENTITY_SET(u32, 7)
  TEST_ENTITY_SET(u64, 8)
    
  TEST_ENTITY_SET(s8, -42)
  TEST_ENTITY_SET(s16, 73)
  TEST_ENTITY_SET(s32, -255)
  TEST_ENTITY_SET(s64, 99)
  
  TEST_ENTITY_SET(str, "yolo")
    
  // 2) we test my_entity.set(X, Y) and my_entity.get(X, Y)
  #define TEST_ENTITY_DYNAMIC_SET(varname, val, type) \
  type tmp1_##varname = val;\
  my_entity.set(#varname, &tmp1_##varname); \
  ASSERT_OK(*( (type *) my_entity.get(#varname)) == val)

  TEST_ENTITY_DYNAMIC_SET(u8, 89, Uint8)
  TEST_ENTITY_DYNAMIC_SET(u16, 425, Uint16)
  TEST_ENTITY_DYNAMIC_SET(u32, 745, Uint32)
  TEST_ENTITY_DYNAMIC_SET(u64, 8785785, Uint64)
    
  TEST_ENTITY_DYNAMIC_SET(s8, 55, Sint8)
  TEST_ENTITY_DYNAMIC_SET(s16, -73, Sint16)
  TEST_ENTITY_DYNAMIC_SET(s32, 255, Sint32)
  TEST_ENTITY_DYNAMIC_SET(s64, 99, Sint64)
  
  TEST_ENTITY_DYNAMIC_SET(str, "yolo42", string)
  
  return 0;
}
