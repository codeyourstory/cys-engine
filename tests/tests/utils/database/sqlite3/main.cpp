/*
 Test of utils/database/connections/Sqlite3Connection 
 
 Don't forget to prefix '_' the attributes of the entity ! 
 
 */

#include <cys-engine/utils/database/connections/Sqlite3Connection.h>
#include <string>
#include <string.h>
#include <unistd.h>


using namespace cys;
using namespace cys::data;
using namespace cys::database;
using namespace std;

// definition of the datatype
DATA_DEF(TestEntity)
// definition of our entity

class TestEntity : public Entity {
public:
  
  TestEntity();
  ~TestEntity();
    
  
  ACCESS_DEF(id, Sint32)
  
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
  
  Sint32 _id;
  
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
  
ACCESS_DECL(TestEntity, id, Sint32)
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
  DATA_DEF_VAR(id,  SINT32)
  
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

void setCurrentDir(const char *argv0);

int main(int argc, char** argv)
{
  setCurrentDir(argv[0]);
  
  DATA(TestEntity) myDatatype;
  TestEntity my_entity;
  my_entity._set_datatype(&myDatatype); // don't forget this !
  
  // remove the db if exists
  system("rm -f db_test");
  
  // create the db
  SQLite3Connection connection("db_test");
  
  ASSERT_OK(connection.get_db() != nullptr)
    
  // create the schema
    
  connection.execute(
    "CREATE TABLE test_entity(\n"
    "  id INTEGER PRIMARY KEY,\n"
    "  u8 INTEGER,\n"
    "  u16 INTEGER,\n"
    "  u32 INTEGER,\n"
    "  u64 INTEGER,\n"
    "  s8 INTEGER,\n"
    "  s16 INTEGER,\n"
    "  s32 INTEGER,\n"
    "  s64 INTEGER,\n"
    "  str VARCHAR(100)\n"
    ");"
  );
  
  // set the entity some values
#define TEST_ENTITY_SET(varname, val) \
  my_entity.set_##varname(val); \
  ASSERT_OK(*(my_entity.get_##varname()) == val)
  
  TEST_ENTITY_SET(id, (connection.get_max_id("test_entity") + 1) )
  TEST_ENTITY_SET(u8, 5)
  TEST_ENTITY_SET(u16, 6)
  TEST_ENTITY_SET(u32, 7)
  TEST_ENTITY_SET(u64, 8)
    
  TEST_ENTITY_SET(s8, -42)
  TEST_ENTITY_SET(s16, 73)
  TEST_ENTITY_SET(s32, -255)
  TEST_ENTITY_SET(s64, 99)
  
  TEST_ENTITY_SET(str, "yolo")
      
  // insert the entity in the db
  connection.insert(&myDatatype, &my_entity);
  
  // get the entity back
  TestEntity *from_db = (TestEntity *) connection.load_single(
    std::string("id = 1"),
    &myDatatype
  );
  
  ASSERT_OK(from_db != nullptr)
 
#define TEST_ENTITY_VAL(varname, val) \
    ASSERT_OK(*(my_entity.get_##varname()) == val)
    
  TEST_ENTITY_VAL(id, 1)
  TEST_ENTITY_VAL(u8, 5)
  TEST_ENTITY_VAL(u16, 6)
  TEST_ENTITY_VAL(u32, 7)
  TEST_ENTITY_VAL(u64, 8)
    
  TEST_ENTITY_VAL(s8, -42)
  TEST_ENTITY_VAL(s16, 73)
  TEST_ENTITY_VAL(s32, -255)
  TEST_ENTITY_VAL(s64, 99)
  
  TEST_ENTITY_VAL(str, "yolo")
  
  
  return 0;
}

void setCurrentDir(const char *argv0)
{
    int i, l;	
    char *s;

    s = strdup(argv0);
    l = strlen(s);

    for(i = l - 1; (i >= 0) && (s[i] != '/'); i--)
      ;

    if((i >= 0) && (i < (l - 1)))
            s[i+1] = 0;
    else;

    chdir(s);

    free(s);

    return;
}