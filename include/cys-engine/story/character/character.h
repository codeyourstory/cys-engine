#ifndef CYS_ENGINE__STORY_CHARACTER_CHARACTER_H
#define	CYS_ENGINE__STORY_CHARACTER_CHARACTER_H

#include <string>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace story {
namespace character {

  enum Gender {
    ASEXUATE = 0,
    MALE = 1,
    FEMALE = 2
  };

  // A character can be anything (animal, tree,

  class Character : public data::Entity {
  public: 
    
    Character();
    ~Character();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(story_id, Uint32)
    ACCESS_DEF(name, std::string)
    ACCESS_DEF(gender, Uint8);
    
  private:
    
    Uint32 _id;
    Uint32 _story_id;
    std::string _name;
    Uint8 _gender;
  };
  
  FACTORY_DEF(Character)
  DATA_DEF(Character)

}
}
}

#endif

