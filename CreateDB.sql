-- Создание БД

drop database BicRF;
create database BicRF;

use BicRF;

drop table TNP;
create table "TNP" ("VKEY" char(2) not null, "TNP" char(2), "FULLNAME" char(25), "SHORTNAME" char(5), primary key("VKEY"));

/*
drop table UER;
-- create table "UER" ("VKEY" CHAR(2) NOT NULL, "UER" CHAR(2), "UERNAME" CHAR(45), primary key("VKEY"));

drop table PZN;
create table "PZN" ("VKEY" CHAR(2) NOT NULL, "PZN" CHAR(2), "IMY" CHAR(4), "NAME" VARCHAR(50), primary key("VKEY"));

create table "PZN" ("VKEY" CHAR(2) NOT NULL, "UER" CHAR(2), "UERNAME" CHAR(45), primary key("VKEY"));

-- select * from TNP;
*/