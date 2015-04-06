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
  
  cys::story::Story story;
  cys::story::StoryDataType storydt;

  story.set_id(1);
  story.set_title("First Story");
  
  db.insert(&storydt, &story);
  
  return 0;
}
