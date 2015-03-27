#ifndef CYS_ENGINE__STORY_STORY_STORY_H
#define	CYS_ENGINE__STORY_STORY_STORY_H

#include <string>
#include <cys-engine/utils/macros.h>

namespace cys {
namespace story {
  
  class Story {
  public: 
    
    Story();
    Story(const std::string &title);
    ~Story();
    
    ACCESS_DEF(title, std::string)
    
  private:
    
    std::string _title;
  };
  
}
}

#endif
