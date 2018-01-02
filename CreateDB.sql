-- Создание БД

use master;

drop database BicRF;
create database BicRF;

use BicRF;

create table "PZN" (VKEY char(2) not null, PZN char(2), IMY char(4), NAME varchar(40), CB_DATE datetime, CE_DATE datetime, primary key(VKEY));

create table "TNP" (VKEY char(2) not null, TNP char(2), FULLNAME varchar(25), SHORTNAME varchar(5), primary key(VKEY));
create table "UER" (VKEY char(2) not null, UER char(2), UERNAME varchar(70), primary key(VKEY));
create table "REG" (VKEY char(2) not null, RGN char(2), NAME varchar(40), CENTER varchar(30), NAMET varchar(40), primary key(VKEY));
create table "BNKSEEK" (REAL char(4), PZN char(2), UER char(2) not null, RGN char(2) not null, IND char(6),
	TNP char(2), NNP varchar(25), ADR varchar(30), RKC char(9), NAMEP varchar(45),
	NEWNUM char(9) not null, TELEF varchar(25), REGN varchar(9), OKPO char(8),
	DT_IZM datetime not null, KSNP char(20), DATE_IN datetime not null,
	DATE_CH datetime, primary key(NEWNUM));

