/*
 Test of utils/data/datatype.h classes
 
 Don't forget to prefix '_' the attributes of the entity ! 
 
 */

#include <cys-engine/utils/data/datatype.h>
#include <string>

using namespace cys;
using namespace cys::data;
using namespace std;

// definition of our entity

class TestEntity {
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

TestEntity::TestEntity()
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

DATA_DEF(TestEntity)
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


int main(int argc, char** argv)
{
  DATA(TestEntity) myDatatype;
  
  
  
  return 0;
}

