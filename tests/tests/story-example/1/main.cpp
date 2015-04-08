#include <cys-engine/cys-engine.h>
#include <string>

#include "cys-engine/utils/database/connections/Sqlite3Connection.h"

using namespace cys;
using namespace cys::data;
using namespace std;

int main(int argc, const char *argv[])
{
  system("rm -rf ./tmp");
  system("mkdir -p ./tmp");

  // create the db
  cys::database::SQLite3Connection db("tmp/db");
  // create the cys-engine schema
  db.execute_file("../../../sql/01-story.sql");
  db.execute_file("../../../sql/02-character.sql");
  db.execute_file("../../../sql/03-events.sql");
  
  // create the story
  cys::story::Story story;
  cys::story::StoryDataType storydt;

  story.set_id(1);
  story.set_title("First Story");
  
  db.insert(&storydt, &story);
  
  // create 2 characters
  cys::story::character::Character characters[2];
  cys::story::character::CharacterDataType characterdt;

  characters[0].set_id(1);
  characters[0].set_story_id(1);
  characters[0].set_name("Sir Mc Yolo");
  characters[0].set_gender(cys::story::character::MALE);


  characters[1].set_id(2);
  characters[1].set_story_id(1);
  characters[1].set_name("The Pink Warlord");
  characters[1].set_gender(cys::story::character::MALE);
  
  db.insert(&characterdt, &characters[0]);
  db.insert(&characterdt, &characters[1]);

  // create the born events
  cys::story::event::Event event;
  cys::story::event::EventDataType eventdt;

  cys::story::event::character::SubjectEvent subjectevent;
  cys::story::event::character::SubjectEventDataType subjecteventdt;

  event.set_id(1);
  event.set_story_id(*(story.get_id()));
  event.set_type(cys::story::event::CHARACTER);
  event.set_date("0");

  subjectevent.set_id(1);
  subjectevent.set_story_id(*(story.get_id()));
  subjectevent.set_event_id(*(event.get_id()));
  subjectevent.set_type(cys::story::event::character::BORN);
  subjectevent.set_character_id(*(characters[0].get_id()));
  //subjectevent.set_text("");

  db.insert(&eventdt, &event);
  db.insert(&subjecteventdt, &subjectevent);

  return 0;
}
