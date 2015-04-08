CREATE TABLE event(
  id INTEGER PRIMARY KEY,
  story_id INTEGER REFERENCES story(id) NOT NULL,
  type INTEGER NOT NULL,
  date VARCHAR(40) NOT NULL
); 

CREATE TABLE event_character_subject(
  id INTEGER PRIMARY KEY,
  story_id INTEGER REFERENCES story(id) NOT NULL,
  event_id INTEGER REFERENCES event(id) NOT NULL,
  type INTEGER NOT NULL,
  character_id INTEGER NOT NULL,
  text TEXT NULL
);

CREATE TABLE event_character_subject_target(
  id INTEGER PRIMARY KEY,
  story_id INTEGER REFERENCES story(id) NOT NULL,
  event_id INTEGER REFERENCES event(id) NOT NULL,
  type INTEGER NOT NULL,
  character1_id INTEGER NOT NULL,
  character2_id INTEGER NOT NULL,
  text TEXT NULL
);

