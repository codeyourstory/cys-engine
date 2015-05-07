#include "cys-engine/story/entities/story.h"
using namespace cys::story::entities;
StoryDefinition::StoryDefinition()
{
  Story entity(nullptr);
  
  this->define_attribute("id", nge::entity::UINT32, &entity, entity.get_id_ptr());
  this->define_attribute("title", nge::entity::STRING, &entity, entity.get_title_ptr());
  
  this->set_table("story");
}

// 

Story::Story()
{
}

Story::Story(nge::orm::Context *context):
nge::orm::Entity(context)
{
}

void Story::set_title(std::string title)
{
  _title = title;
}

std::string Story::get_title()
{
  return _title;
}

std::string *Story::get_title_ptr()
{
  return &_title;
}

nge::entity::EntityDefinition *Story::__get_definition() const
{
  nge::entity::EntityDefinition *ret = nullptr;
  
  if(!_context) return ret;
  
  auto it = _context->get_entity_definitions()->find("story"),
       end = _context->get_entity_definitions()->end();
  if(it != end) {
    // found => to return
    
    ret = it->second;
  }
  else {
    // not found

    // so we create the definition
    ret = new StoryDefinition();
    // and we add it in the orm
    _context->get_entity_definitions()->insert(std::make_pair(ret->get_table(), ret));
  }
  
  return ret;
}


