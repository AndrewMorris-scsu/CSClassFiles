Create Table Veterinarians (
    licenseNum INTEGER,
    vetName varchar(10),
    PRIMARY KEY (licenseNum)
);

Create Table Dogs (
    did INTEGER,
    dogName varchar(10),
    PRIMARY KEY (did)
);

Create Table Location (
    lid INTEGER,
    locName varchar(15)
);

Create Table Examine (
    licenseNum INTEGER,
    did INTEGER,
    lid INTEGER,
    fee FLOAT,
    PRIMARY KEY (licenseNum, did, lid),
    FOREIGN KEY (licenseNum) REFERENCES Veterinarians,
    FOREIGN KEY (did) REFERENCES Dogs,
    FOREIGN KEY (lid) REFERENCES Location
);

INSERT INTO Veterinarians (vetName, licenseNum) VALUES ('Alice', 112);
INSERT INTO Veterinarians (vetName, licenseNum) VALUES ('Mary', 211);
INSERT INTO Veterinarians (vetName, licenseNum) VALUES ('Jim', 111);

INSERT INTO Dogs (dogName, did) VALUES ('Spot', 324);
INSERT INTO Dogs (dogName, did) VALUES ('Fido', 582); 
INSERT INTO Dogs (dogName, did) VALUES ('Tiger', 731);

INSERT INTO Location (lid, locName) VALUES (1001, 'St. Cloud');
INSERT INTO Location (lid, locName) VALUES (1002, 'Minneapolis');
INSERT INTO Location (lid, locName) VALUES (1003, 'Duluth');

INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (111, 324, 1001, 10);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (111, 731, 1003, 20);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (112, 324, 1001, 30);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (112, 582, 1001, 50);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (112, 731, 1002, 35);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (211, 324, 1001, 25);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (211, 582, 1002, 35);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (211, 731, 1001, 20);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (211, 582, 1001, 25);
INSERT INTO Examine (licenseNum, did, lid, fee)
    VALUES (211, 582, 1003, 55);



