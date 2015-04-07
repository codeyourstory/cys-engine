#ifndef CYS_ENGINE__STORY_EVENT_EVENT_H
#define	CYS_ENGINE__STORY_EVENT_EVENT_H

#include <string>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace story {
namespace event {
namespace character {
  
  enum EventType {
    SUBJECT = 1,        // subject <action>
    SUBJECT_TARGET = 2, // subject <action> target
  };
  
  enum SubjectEventName {
    APPEAR = 0,
    DISAPPEAR = 1,
    BORN = 2,
    DEAD = 3,
    SPEAK_ALONE = 4
  };
  
  enum SubjectTargetEventName {
    SPEAK_TO = 0,
    KILL = 1
  };
  
  class SubjectEvent : public data::Entity {
  public: 
    
    SubjectEvent();
    ~SubjectEvent();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(story_id, Uint32)
    ACCESS_DEF(event_id, Uint32)
    ACCESS_DEF(type, Uint32)
    ACCESS_DEF(character_id, Uint32)
    ACCESS_DEF(text, std::string)
    
  private:
    
    Uint32 _id;
    Uint32 _story_id;
    Uint32 _event_id;
    Uint32 _type; // SubjectEventType
    Uint32 _character_id;
    std::string _text;
  };
  
  FACTORY_DEF(SubjectEvent)
  DATA_DEF(SubjectEvent)

  class SubjectTargetEvent : public data::Entity {
  public: 
    
    SubjectTargetEvent();
    ~SubjectTargetEvent();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(story_id, Uint32)
    ACCESS_DEF(event_id, Uint32)
    ACCESS_DEF(type, Uint32)
    ACCESS_DEF(character1_id, Uint32)
    ACCESS_DEF(character2_id, Uint32)
    ACCESS_DEF(text, std::string)
    
  private:
    
    Uint32 _id;
    Uint32 _story_id;
    Uint32 _event_id;
    Uint32 _type; // SubjectTargetEventType
    Uint32 _character1_id;
    Uint32 _character2_id;
    std::string _text;
  };

  FACTORY_DEF(SubjectTargetEvent)
  DATA_DEF(SubjectTargetEvent)
}
}
}
}

#endif

