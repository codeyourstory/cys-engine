CREATE TABLE character(
  id INTEGER PRIMARY KEY,
  story_id INTEGER REFERENCES story(id) NOT NULL,
  name VARCHAR(128) NOT NULL,
  gender INTEGER NOT NULL
); 


