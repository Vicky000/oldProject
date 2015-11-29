//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TOptionDlg.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TOptionDlg *OptionDlg;
//---------------------------------------------------------------------
__fastcall TOptionDlg::TOptionDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TOptionDlg::BrowseButton1Click(TObject *Sender)
{
        OpenDialog1->FileName="当前文件夹";
        OpenDialog1->InitialDir=Edit1->Text;
        if(OpenDialog1->Execute()==IDOK)
        {
                Edit1->Text=ExtractFileDir(OpenDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

void __fastcall TOptionDlg::BrowseButton2Click(TObject *Sender)
{
        OpenDialog1->FileName="当前文件夹";
        OpenDialog1->InitialDir=Edit2->Text;
        if(OpenDialog1->Execute()==IDOK)
        {
                Edit2->Text=ExtractFileDir(OpenDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

void __fastcall TOptionDlg::BrowseButton3Click(TObject *Sender)
{
        OpenDialog1->FileName="当前文件夹";
        OpenDialog1->InitialDir=Edit3->Text;
        if(OpenDialog1->Execute()==IDOK)
        {
                Edit3->Text=ExtractFileDir(OpenDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

void __fastcall TOptionDlg::BrowseButton4Click(TObject *Sender)
{
        OpenDialog1->FileName="当前文件夹";
        OpenDialog1->InitialDir=Edit4->Text;
        if(OpenDialog1->Execute()==IDOK)
        {
                Edit4->Text=ExtractFileDir(OpenDialog1->FileName);
        }
}
//---------------------------------------------------------------------------

