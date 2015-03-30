#include <cys-engine/story/story/story.h>

using namespace cys;
using namespace cys::data;
using namespace cys::story;

Story::Story() : data::Entity(nullptr)
{
}

Story::Story(const std::string &title) : data::Entity(nullptr)
{
  _title = title;
}

Story::~Story()
{
  
}

ACCESS_DECL(Story, id, Uint32)
ACCESS_DECL(Story, title, std::string)

FACTORY_DECL(Story)
  
DATA_DECL(Story, "story",
  DATA_DEF_VAR(id, UINT32)
  DATA_DEF_VAR(title, STRING)      
)
