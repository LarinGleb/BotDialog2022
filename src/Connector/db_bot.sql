USE Dialog;
DROP TABLE IF EXISTS Events;
DROP TABLE IF EXISTS Reviews;
CREATE TABLE Events (
  Name text NOT NULL,
  Time datetime NOT NULL,
  EventType int NOT NULL,
  EventStructType int NOT NULL,
  EventCommandType int NOT NULL,
  id int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (id)
);

CREATE TABLE Reviews (
   NameEvent text NOT NULL,
   Ests text NOT NULL,
   Cr_ID INTEGER NOT NULL,
   More INTEGER NOT NULL,
   Review text NOT NULL
);