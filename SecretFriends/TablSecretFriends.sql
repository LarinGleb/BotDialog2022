
USE `psny`; //вписать название бд

CREATE TABLE `Ы` (
    id MEDIUMINT NOT NULL AUTO_INCREMENT,
    podsk CHAR(255) NOT NULL,
    sex CHAR(8) NOT NULL,
    price CHAR(16) NOT NULL,
    eat BOOL NOT NULL,
    PRIMARY KEY (id)
);