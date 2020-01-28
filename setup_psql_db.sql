DROP DATABASE IF EXISTS shape_file_database CASCADE;
CREATE DATABASE shape_file_database;
CREATE USER amouroug WITH PASSWORD 'FullMetalAlchemist#8';
ALTER USER amouroug WITH SUPERUSER CREATEDB CREATEROLE;
GRANT ALL PRIVILEGES ON DATABASE shape_file_database TO amouroug;
