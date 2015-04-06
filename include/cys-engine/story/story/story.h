#ifndef CYS_ENGINE__STORY_STORY_STORY_H
#define	CYS_ENGINE__STORY_STORY_STORY_H

#include <string>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace story {
  
  class Story : public data::Entity {
  public: 
    
    Story();
    Story(const std::string &title);
    ~Story();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(title, std::string)
    
  private:
      
    Uint32 _id;
    std::string _title;
  };
  
  FACTORY_DEF(Story)
  DATA_DEF(Story)
  
}
}

#endif
