//---------------------------------------------------------------------------

#ifndef SQLiteInterfaceH
#define SQLiteInterfaceH
#include "sqlite3.h"
//---------------------------------------------------------------------------
typedef struct {
	int id;
	UnicodeString country;
	UnicodeString mail;
} DBNode;

class DBWorker
{
	sqlite3* dataBase;
	char *errmsg;
	sqlite3_stmt *pStatement;
	int lastResult;

	public:

	DBWorker();

	void DBConnect(AnsiString fileName);

	void DBDisconnect();

	void DBPrepareQuery(AnsiString sqlQuery);

	bool DBIterator();

	void DBDataFilling(DBNode *nodeData);

	AnsiString DBInterpretError();

	int DBGetResult();

	void DBSetResult(int state);

	void DBKillStatement();

	int DBWorker::DBExec(std::string query);

};
#endif


