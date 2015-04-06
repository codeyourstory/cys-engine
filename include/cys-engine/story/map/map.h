#ifndef MAP_H
#define	MAP_H

#include <string>
#include <cys-engine/utils/data/datatype.h>

namespace cys {
namespace story {
  
  class Map {
  public:
    
    Map();
    ~Map();
    
    ACCESS_DEF(id, Uint32)
    ACCESS_DEF(story_id, Uint32)
    ACCESS_DEF(name, std::string)
    ACCESS_DEF(size_w, Uint32)
    ACCESS_DEF(size_h, Uint32)
    
  private:
    Uint32 _id;
    Uint32 _story_id;
    std::string _name;
    
    Uint32 _size_w;
    Uint32 _size_h;
    
  };
 
  FACTORY_DEF(Map)
  
}
}

#endif
