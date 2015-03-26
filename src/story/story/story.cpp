#include <cys-engine/story/story/story.h>

using namespace story;

Story::Story(const std::string &title)
{
  _title = title;
}

Story::~Story()
{
  
}

ACCESS_DECL(Story, title, std::string)
