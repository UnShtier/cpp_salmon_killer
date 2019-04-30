//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SQP.h"
#include "SQLiteInterface.h"
#include <string>
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
DBWorker db;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SelectClick(TObject *Sender)
{
	fd->Options.Clear();
	fd->Options << ofFileMustExist;
	fd->Filter = "DB files (*.db)|*.db|All files (*.*)|*.*";
	fd->FilterIndex = 2;
	if (fd->Execute()) {
		db.DBConnect(AnsiString(fd->Files->Strings[0]).c_str());
		if(db.DBGetResult() != 1) {
			ShowMessage(db.DBInterpretError());
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadClick(TObject *Sender)
{
	VST->Clear();
	VST->BeginUpdate();
	db.DBPrepareQuery("select customerid, Country, Email from customers");
	while (db.DBIterator())

	{
		VST -> NodeDataSize = sizeof(DBNode);
		PVirtualNode entryNode = VST->AddChild(VST->RootNode);
		DBNode *nodeData = (DBNode*)VST->GetNodeData(entryNode);
		db.DBDataFilling(nodeData);
	}
	VST->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VSTGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVSTTextType TextType, UnicodeString &CellText)
{
	if(!Node) return;
	DBNode *nodeData = (DBNode*)Sender->GetNodeData(Node);
	switch(Column)
	{
		case 0:CellText = nodeData->id; break;
		case 1:CellText = nodeData->country; break;
		case 2:CellText = nodeData->mail; break;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DeleteClick(TObject *Sender)
{
	PVirtualNode node = VST->GetFirstSelected(False);
	DBNode *nd = (DBNode*)VST->GetNodeData(node);
	std::ostringstream stm;
	stm << nd->id;
	std::string query = "delete from customers where CustomerId = " + stm.str();
	db.DBExec(query);
	for (int i = 1; i < VST->SelectedCount; i++) {
		node = VST->GetNextSelected(node);
		nd = (DBNode*)VST->GetNodeData(node);
		std::ostringstream stm;
		stm << nd->id;
		std::string query = "delete from customers where CustomerId = " + stm.str();
		db.DBExec(query);
	}
	Form1->LoadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TruncateClick(TObject *Sender)
{
	std::string query = "delete from customers";
	db.DBExec(query);
	Form1->LoadClick(Sender);
}
//---------------------------------------------------------------------------

