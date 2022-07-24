USE Dialog;
DROP TABLE IF EXISTS Events;
DROP TABLE IF EXISTS Reviews;
CREATE TABLE Events (
  Name text NOT NULL,
  Time datetime NOT NULL,
  BodyType int NOT NULL,
  StructType int NOT NULL,
  CommandType int NOT NULL,
  id int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id)
);

CREATE TABLE Reviews (
   NameEvent text NOT NULL,
   ActionEsts text NOT NULL,
   StructEsts text NOT NULL,
   CommandEsts text NOT NULL,
   Review text NOT NULL,
   More INTEGER NOT NULL
);