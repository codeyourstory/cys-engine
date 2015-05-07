#include "cys-engine/story/entities/character/character.h"
using namespace cys::story::entities::character;
CharacterDefinition::CharacterDefinition()
{
  Character entity(nullptr);
  
  this->define_attribute("id", nge::entity::UINT32, &entity, entity.get_id_ptr());
  this->define_attribute("story_id", nge::entity::UINT32, &entity, entity.get_story_id_ptr());
  this->define_attribute("title", nge::entity::STRING, &entity, entity.get_title_ptr());
  this->define_attribute("name", nge::entity::STRING, &entity, entity.get_name_ptr());
  this->define_attribute("gender", nge::entity::UINT8, &entity, entity.get_gender_ptr());
  
  this->set_table("character");
}

// 

Character::Character()
{
}

Character::Character(nge::orm::Context *context):
nge::orm::Entity(context)
{
  _story_id = 0;
  _gender = 0;
}

void Character::set_story_id(uint32_t story_id)
{
  _story_id = story_id;
}

uint32_t Character::get_story_id()
{
  return _story_id;
}

uint32_t *Character::get_story_id_ptr()
{
  return &_story_id;
}

void Character::set_title(std::string title)
{
  _title = title;
}

std::string Character::get_title()
{
  return _title;
}

std::string *Character::get_title_ptr()
{
  return &_title;
}

void Character::set_name(std::string name)
{
  _name = name;
}

std::string Character::get_name()
{
  return _name;
}

std::string *Character::get_name_ptr()
{
  return &_name;
}

void Character::set_gender(uint8_t gender)
{
  _gender = gender;
}

uint8_t Character::get_gender()
{
  return _gender;
}

uint8_t *Character::get_gender_ptr()
{
  return &_gender;
}

nge::entity::EntityDefinition *Character::__get_definition() const
{
  nge::entity::EntityDefinition *ret = nullptr;
  
  if(!_context) return ret;
  
  auto it = _context->get_entity_definitions()->find("character"),
       end = _context->get_entity_definitions()->end();
  if(it != end) {
    // found => to return
    
    ret = it->second;
  }
  else {
    // not found

    // so we create the definition
    ret = new CharacterDefinition();
    // and we add it in the orm
    _context->get_entity_definitions()->insert(std::make_pair(ret->get_table(), ret));
  }
  
  return ret;
}


