drop schema if exists amouroug cascade;

create schema amouroug;

create table amouroug.STATE(ID int primary key, IName varchar(50), Min_Latitude varchar(10), Max_Latitude varchar(10), Min_Longitude varchar(10), Max_Longitude varchar(10));
create table amouroug.COUNTY(ID int primary key, IName varchar(50), Min_Latitude varchar(10), Max_Latitude varchar(10), Min_Longitude varchar(10), Max_Longitude varchar(10));
create table amouroug.PLACE(ID int primary key, IName varchar(50), Min_Latitude varchar(10), Max_Latitude varchar(10), Min_Longitude varchar(10), Max_Longitude varchar(10));
create table amouroug.SUBCOUNTY(ID int primary key, IName varchar(50), Min_Latitude varchar(10), Max_Latitude varchar(10), Min_Longitude varchar(10), Max_Longitude varchar(10));
