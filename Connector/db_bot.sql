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
   idEvent INTEGER NOT NULL,
   Ests text NOT NULL,
   Cr_ID INTEGER NOT NULL,
   More INTEGER NOT NULL,
   Review text NOT NULL
);
