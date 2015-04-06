#include <cys-engine/story/map/map.h>

using namespace cys;
using namespace cys::story;

Map::Map()
{
  
}

Map::~Map()
{
  
}

ACCESS_DECL(Map, id, Uint32)
ACCESS_DECL(Map, story_id, Uint32)
ACCESS_DECL(Map, name, std::string)
ACCESS_DECL(Map, size_w, Uint32)
ACCESS_DECL(Map, size_h, Uint32)

FACTORY_DECL(Map)
