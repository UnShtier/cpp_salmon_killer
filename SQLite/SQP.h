//---------------------------------------------------------------------------

#ifndef SQPH
#define SQPH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VST;
	TButton *Select;
	TButton *Load;
	TOpenDialog *fd;
	TButton *Delete;
	TButton *Truncate;
	void __fastcall SelectClick(TObject *Sender);
	void __fastcall LoadClick(TObject *Sender);
	void __fastcall VSTGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall TruncateClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
