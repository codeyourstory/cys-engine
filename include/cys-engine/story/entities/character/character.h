#ifndef __nge_orm__Character_H
#define __nge_orm__Character_H

#include <ngengine/orm/orm.h>

#include <string>

namespace cys {
namespace story {
namespace entities {
namespace character {

class CharacterDefinition : public nge::entity::EntityDefinition {
public:
  CharacterDefinition();
};


class Character : public nge::orm::Entity {
public:

  Character();
  Character(nge::orm::Context *context);
  nge::entity::EntityDefinition *__get_definition() const;

  void set_story_id(uint32_t);
  uint32_t get_story_id();
  uint32_t *get_story_id_ptr();

  void set_title(std::string);
  std::string get_title();
  std::string *get_title_ptr();

  void set_name(std::string);
  std::string get_name();
  std::string *get_name_ptr();

  void set_gender(uint8_t);
  uint8_t get_gender();
  uint8_t *get_gender_ptr();


private:

  //uint32_t _id; -> inherited
  uint32_t _story_id;
  std::string _title;
  std::string _name;
  uint8_t _gender;

};

}
}
}
}

#endif
