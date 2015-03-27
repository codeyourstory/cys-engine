#include <cys-engine/story/story/story.h>

using namespace cys;
using namespace cys::story;

Story::Story()
{
}

Story::Story(const std::string &title)
{
  _title = title;
}

Story::~Story()
{
  
}

ACCESS_DECL(Story, title, std::string)
