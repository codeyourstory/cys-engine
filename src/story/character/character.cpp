#include <cys-engine/story/character/character.h>

using namespace cys;
using namespace cys::data;
using namespace cys::story::character;

Character::Character() : data::Entity(nullptr)
{
}

Character::~Character()
{
  
}

ACCESS_DECL(Character, id, Uint32)
ACCESS_DECL(Character, story_id, Uint32)
ACCESS_DECL(Character, name, std::string)
ACCESS_DECL(Character, gender, Uint8)

FACTORY_DECL(cys::story::character::Character)

DATA_DECL(Character, "character",
  DATA_DEF_VAR(id, UINT32)
  DATA_DEF_VAR(story_id, UINT32)
  DATA_DEF_VAR(name, STRING)
  DATA_DEF_VAR(gender, UINT8)
)

