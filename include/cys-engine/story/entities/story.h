#ifndef __nge_orm__Story_H
#define __nge_orm__Story_H

#include <ngengine/orm/orm.h>

#include <string>

namespace cys {
namespace story {
namespace entities {

class StoryDefinition : public nge::entity::EntityDefinition {
public:
  StoryDefinition();
};


class Story : public nge::orm::Entity {
public:

  Story(nge::orm::ORM *orm);
  nge::entity::EntityDefinition *__get_definition() const;

  void set_title(std::string);
  std::string get_title();
  std::string *get_title_ptr();


private:

  //uint32_t _id; -> inherited
  std::string _title;

};

}
}
}

#endif
