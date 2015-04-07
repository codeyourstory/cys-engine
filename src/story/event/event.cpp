#include <cys-engine/story/event/event.h>

using namespace cys;
using namespace cys::data;
using namespace cys::story::event;

Event::Event() : data::Entity(nullptr)
{
}

Event::~Event()
{
  
}

ACCESS_DEF(id, Uint32)
ACCESS_DEF(story_id, Uint32)
ACCESS_DEF(type, Uint8)
ACCESS_DEF(date, std::string); 

ACCESS_DECL(Event, id, Uint32)
ACCESS_DECL(Event, story_id, Uint32)
ACCESS_DECL(Event, type, Uint8)
ACCESS_DECL(Event, date, std::string)

FACTORY_DECL(cys::story::event::Event)
  
DATA_DECL(Event, "event",
  DATA_DEF_VAR(id, UINT32)
  DATA_DEF_VAR(story_id, UINT32)
  DATA_DEF_VAR(type, UINT8)
  DATA_DEF_VAR(date, STRING)      
)
