#include <cys-engine/cys-engine.h>
#include <string>
#include <iostream>

using namespace cys;
using namespace cys::story;
using namespace cys::story::entities;
using namespace std;

int main(int argc, const char *argv[])
{
  system("rm -rf ./tmp");
  system("mkdir -p ./tmp");

  // create the db
  nge::orm::database::connections::Sqlite3Connection db;

  if(!db.open("tmp/db.sqlite3")) {
    cout << "Can't open tmp/db.sqlite3" << endl;
    return -1;
  }
  
  
  // create the cys-engine schema
  db.create_table(new cys::story::entities::StoryDefinition());
  db.create_table(new cys::story::entities::character::CharacterDefinition());
  
  
  // create the story
  cys::story::entities::Story story(db.get_context());
  
  story.set_id(1);
  story.set_title("First Story");
  
  db.insert(story);
  
  // create 2 characters
  cys::story::entities::character::Character characters[2];

  characters[0].__set_context(db.get_context());
  characters[1].__set_context(db.get_context());
  
  characters[0].set_id(1);
  characters[0].set_story_id(1);
  characters[0].set_name("Sir Mc Yolo");
  characters[0].set_gender(0);
  //characters[0].set_gender(cys::story::character::MALE);

  characters[1].set_id(2);
  characters[1].set_story_id(1);
  characters[1].set_name("The Pink Warlord");
  characters[0].set_gender(1);
  //characters[1].set_gender(cys::story::character::MALE);
  
  db.insert(characters[0]);
  db.insert(characters[1]);

  return 0;
}
