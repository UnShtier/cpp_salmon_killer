//---------------------------------------------------------------------------

#pragma hdrstop

#include "SQLiteInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DBWorker::DBWorker() {
	dataBase = NULL;
	errmsg = NULL;
	pStatement = NULL;
	lastResult = 666;
}

void DBWorker::DBConnect(AnsiString fileName) {
	this->lastResult = sqlite3_open(fileName.c_str(), &this->dataBase);
}

void DBWorker::DBDisconnect() {
	sqlite3_close(this->dataBase);
}

void DBWorker::DBPrepareQuery(AnsiString sqlQuery) {
	this->lastResult = sqlite3_prepare_v2(this->dataBase, sqlQuery.c_str(), -1, &this->pStatement, NULL);
}

bool DBWorker::DBIterator() {
	this->lastResult = sqlite3_step(pStatement);
	return this->lastResult == 100;
}

void DBWorker::DBDataFilling(DBNode *nodeData) {
	nodeData->id = sqlite3_column_int(this->pStatement, 0);
	nodeData->country = (UnicodeString)(char*)sqlite3_column_text(this->pStatement,1);
	nodeData->mail = (UnicodeString)(char*)sqlite3_column_text(this->pStatement,2);
}

AnsiString DBWorker::DBInterpretError() {
	switch (this->lastResult) {
		case 0	: return "Successful result";
		case 1	: return "Generic error";
		case 2	: return "Internal logic error in SQLite";
		case 3	: return "Access permission denied";
		case 4	: return "Callback routine requested an abort";
		case 5	: return "The database file is locked";
		case 6	: return "A table in the database is locked";
		case 7	: return "A malloc() failed";
		case 8	: return "Attempt to write a readonly database";
		case 9	: return "Operation terminated by sqlite3_interrupt()";
		case 10	: return "Some kind of disk I/O error occurred";
		case 11	: return "The database disk image is malformed";
		case 12	: return "Unknown opcode in sqlite3_file_control()";
		case 13	: return "Insertion failed because database is full";
		case 14	: return "Unable to open the database file";
		case 15	: return "Database lock protocol error";
		case 16	: return "Internal use only";
		case 17	: return "The database schema changed";
		case 18	: return "String or BLOB exceeds size limit";
		case 19	: return "Abort due to constraint violation";
		case 20	: return "Data type mismatch";
		case 21	: return "Library used incorrectly";
		case 22	: return "Uses OS features not supported on host";
		case 23	: return "Authorization denied";
		case 24	: return "Not used";
		case 25	: return "2nd parameter to sqlite3_bind out of range";
		case 26	: return "File opened that is not a database file";
		case 27	: return "Notifications from sqlite3_log()";
		case 28	: return "Warnings from sqlite3_log()";
		case 100: return "sqlite3_step() has another row ready";
		case 101: return "sqlite3_step() has finished executing";
	default:
		return "Int value is not recognizable";
	}
}

int DBWorker::DBGetResult() {
	return this->lastResult;
}

void DBWorker::DBSetResult(int state) {
	this->lastResult = state;
}

void DBWorker::DBKillStatement() {
	sqlite3_finalize(this->pStatement);
}

int DBWorker::DBExec(std::string query) {
	this->lastResult = sqlite3_exec(this->dataBase, query.c_str() , NULL, NULL, NULL);
}




