#include <cys-engine/story/event/character/character.h>

using namespace cys;
using namespace cys::data;
using namespace cys::story::event::character;

SubjectEvent::SubjectEvent() : data::Entity(nullptr)
{
}

SubjectEvent::~SubjectEvent()
{
  
}
    
ACCESS_DECL(SubjectEvent, id, Uint32)
ACCESS_DECL(SubjectEvent, story_id, Uint32)
ACCESS_DECL(SubjectEvent, event_id, Uint32)
ACCESS_DECL(SubjectEvent, type, Uint32)
ACCESS_DECL(SubjectEvent, character_id, Uint32)
ACCESS_DECL(SubjectEvent, text, std::string)

FACTORY_DECL(cys::story::event::character::SubjectEvent)
  
DATA_DECL(SubjectEvent, "event",
  DATA_DEF_VAR(id, UINT32)
  DATA_DEF_VAR(story_id, UINT32)
  DATA_DEF_VAR(event_id, UINT32)
  DATA_DEF_VAR(type, UINT32)
  DATA_DEF_VAR(character_id, UINT32)
  DATA_DEF_VAR(text, STRING)      
)

// ----

SubjectTargetEvent::SubjectTargetEvent() : data::Entity(nullptr)
{
}

SubjectTargetEvent::~SubjectTargetEvent()
{
  
}

ACCESS_DEF(id, Uint32)
ACCESS_DEF(story_id, Uint32)
ACCESS_DEF(type, Uint8)
ACCESS_DEF(date, std::string); 

ACCESS_DECL(SubjectTargetEvent, id, Uint32)
ACCESS_DECL(SubjectTargetEvent, story_id, Uint32)
ACCESS_DECL(SubjectTargetEvent, event_id, Uint32)
ACCESS_DECL(SubjectTargetEvent, type, Uint32)
ACCESS_DECL(SubjectTargetEvent, character1_id, Uint32)
ACCESS_DECL(SubjectTargetEvent, character2_id, Uint32)
ACCESS_DECL(SubjectTargetEvent, text, std::string)

FACTORY_DECL(cys::story::event::character::SubjectTargetEvent)
  
DATA_DECL(SubjectTargetEvent, "event",
  DATA_DEF_VAR(id, UINT32)
  DATA_DEF_VAR(story_id, UINT32)
  DATA_DEF_VAR(event_id, UINT32)
  DATA_DEF_VAR(type, UINT32)
  DATA_DEF_VAR(character1_id, UINT32)
  DATA_DEF_VAR(character2_id, UINT32)
  DATA_DEF_VAR(text, STRING)
)

