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
  
  // create a character
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

  return 0;
}
