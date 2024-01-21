# Project Info
This is a simple project for testing QSql and PostgreSQL.

## Project Details
The project provides user with:
- Ability to connect to PostgreSQL database;
- Ability to create new users inside the table with columns `**login** [PK] character varying(20)` and `**password** character varying(20)`;
- Ability to login if user exists;
- Error handling.

List of possible improvements:
- Move database init logic in some *.ini* file;
- Better error handling;
- Better GUI.
