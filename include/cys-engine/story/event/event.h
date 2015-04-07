#ifndef CYS_ENGINE__STORY_EVENT_EVENT_H
#define	CYS_ENGINE__STORY_EVENT_EVENT_H

#include <string>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace story {
namespace event {

  enum EventType {
    CHARACTER = 0
  };  

  class Event : public data::Entity {
  public: 
    
    Event();
    ~Event();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(story_id, Uint32)
    ACCESS_DEF(type, Uint8)
    ACCESS_DEF(date, std::string); // to replace by a real datetime
    
  private:
    
    Uint32 _id;
    Uint32 _story_id;
    Uint8 _type;
    std::string _date;
  };
  
  FACTORY_DEF(Event)
  DATA_DEF(Event)

}
}
}

#endif

