//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#include <StrUtils.hpp>

#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>

#include "TForm1.h"
#include "TForm2.h"
#include "TOptionDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ExitClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OpenClick(TObject *Sender)
{
      if(MemoChanged)
      {
                if(Application->MessageBox("�ı����ݱ��ı䣬�Ƿ�����ı䣿","��Ϣ",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
                        MemoChanged=false;
      }
        if(!MemoChanged)
        {
                OpenDialog1->InitialDir=CppPath;
                OpenDialog1->FileName="";
                if(OpenDialog1->Execute())
                {
                        Memo1->Clear();
                        Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
                        FileName=OpenDialog1->FileName;
                        Caption=Hint+" ��"+FileName;
                        MemoChanged=false;
                        Memo1->SelStart=0;
                        EnableEditSubMenu();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewClick(TObject *Sender)
{
       if(MemoChanged)
       {
                if(Application->MessageBox("�ı����ݱ��ı䣬�Ƿ�����ı䣿","��Ϣ",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
                        MemoChanged=false;
       }
        if(!MemoChanged)
        {
                Memo1->Clear();
                FileName="noname.c";
                Caption=Hint+" ��"+FileName;
                EnableEditSubMenu();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SaveAsClick(TObject *Sender)
{
        SaveDialog1->FileName=ExtractFileName(FileName);
        SaveDialog1->InitialDir=CppPath;
        if(SaveDialog1->Execute())
	{
                Memo1->Lines->SaveToFile(SaveDialog1->FileName);
                FileName=SaveDialog1->FileName;
                Caption=Hint+" ��"+FileName;
                MemoChanged=false;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatusBarDisplay(AnsiString mesg)
{
        StatusBar1->Panels->Items[0]->Text="  "+mesg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DisplayCaretPosOnStatusBar1()
{
        StatusBar1->Panels->Items[0]->Text="  ��������"+IntToStr(Memo1->Lines->Count);
        StatusBar1->Panels->Items[1]->Text="  ���λ�ã�"+IntToStr(Memo1->CaretPos.y+1)+"��, "+IntToStr(Memo1->CaretPos.x+1)+"��";
}




//---------------------------------------------------------------------------


void __fastcall TForm1::Form1Create(TObject *Sender)
{
        HomePath=ExtractFilePath(ParamStr(0));
        BinPath=HomePath+"TC\\BIN\\";
        FILE *fp=fopen((HomePath+"config.txt").c_str(),"r");
        if(fp!=NULL)
        {
                //��ȡ·��
                char tmp[300];
                fgets(tmp,298,fp);
                IncludePath=tmp;
                IncludePath=IncludePath.TrimRight();

                fgets(tmp,298,fp);
                LibraryPath=tmp;
                LibraryPath=LibraryPath.TrimRight();

                fgets(tmp,298,fp);
                CppPath=tmp;
                CppPath=CppPath.TrimRight();

                fgets(tmp,298,fp);
                ExePath=tmp;
                ExePath=ExePath.TrimRight();

                m=fgetc(fp);                //��ȡ����ģʽ
                p=fgetc(fp);                //��ȡ�Ƿ�ʹ��C++������
                g=fgetc(fp);                //��ȡ�Ƿ�ʹ��ͼ�ο�

                fclose(fp);
        }
        else
        {
                IncludePath=HomePath+"TC\\INCLUDE\\";
                LibraryPath=HomePath+"TC\\LIB\\";
                CppPath=HomePath;
                ExePath=HomePath;
                m='s';//���ñ���ģʽsmall
                p='p';//����ʹ��C++������
                g='G';//���ò�ʹ��Turbo C++3.0ͼ�ο�
        }
        //char m,p,g; ��TForm1.h�ж���
        //m��ʾ����ģʽ(t-tiny,s-small,c-compact,m-medium,l-large,h-huge)
        //p��ʾ��ʹ��C++������(p�ǣ�P��)
        //g��ʾ�Ƿ�ʹ��ͼ�ο�(g�ǣ�G��)

        OpenDialog1->InitialDir=CppPath;
        SaveDialog1->InitialDir=CppPath;

        StatusBarDisplay("�� �� ...");

        Memo1->SelStart=0;
        MemoChanged=false;
        FileName="noname.c";
        Caption=Hint+" ��"+FileName;
        EnableEditSubMenu();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Form1Close(TObject *Sender, TCloseAction &Action)
{
       if(MemoChanged && Memo1->Lines->Count>0){
                if(Application->MessageBox("�ı����������ݱ��ı䣬�Ƿ�����ı䣿","��Ϣ",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                        Action= caFree;
                }
                else
                        Action= caNone;
        }
        else{
                        Action= caFree;
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)

{
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveClick(TObject *Sender)

{
     if((FileName=="noname.c"||FileName=="noname.cpp")&& (Sender==Save||Sender==SaveToolButton))
     {
                SaveDialog1->FileName=ExtractFileName(FileName);
                SaveDialog1->InitialDir=CppPath;
                if(SaveDialog1->Execute())
                {
                        Memo1->Lines->SaveToFile(SaveDialog1->FileName);
                        FileName=SaveDialog1->FileName;
                        Caption=Hint+" ��"+FileName;
                        MemoChanged=false;
                        Save->Enabled=false;
                        SaveToolButton->Enabled=false;
                    
                }
        }
        else
        {//���FileName!="nomame.c" &&FileName!="noname.cpp"
             //�� Sender==Compile��Sender==CompileButton��
             //�� Sender==CompileLink��Sender==CompileLinkButton�����Ǵӱ������Ӱ�ť�����ã����س��ֱ���Ի���
                if(FileName=="noname.c"||FileName=="noname.cpp")FileName=CppPath+FileName;
                Memo1->Lines->SaveToFile(FileName);
                MemoChanged=false;
                Save->Enabled=false;
                SaveToolButton->Enabled=false;


        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo1Change(TObject *Sender)
{
        MemoChanged=true;
        Save->Enabled=MemoChanged;
        SaveToolButton->Enabled=MemoChanged;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UndoClick(TObject *Sender)
{
        if(Memo1->CanUndo)
        {
                Memo1->Undo();
                MemoChanged=true;
                EnableEditSubMenu();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CutClick(TObject *Sender)
{
        Memo1->CutToClipboard();
        MemoChanged=true;
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PasteClick(TObject *Sender)
{
       if(Clipboard()->AsText!=NULL)
       {
                Memo1->PasteFromClipboard();
                MemoChanged=true;
                EnableEditSubMenu();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteClick(TObject *Sender)
{
         
        Memo1->ClearSelection();
        MemoChanged=true;
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindClick(TObject *Sender)
{
      if(Memo1->SelLength>0)
        FindDialog1->FindText=Memo1->SelText;
        FindDialog1->Execute();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FindDialog1Find(TObject *Sender)
{
        if(Sender==ReplaceDialog1)
	{              //�滻�Ի�����"������һ��"��ťʱ���ô˾�
                FindDialog1->FindText=ReplaceDialog1->FindText;
        }
        FindNextClick(Sender);
        if(Sender==FindDialog1)
                FindDialog1->CloseDialog();
        else if(Sender==ReplaceDialog1)
                ReplaceDialog1->CloseDialog();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindNextClick(TObject *Sender)
{
        bool down=FindDialog1->Options.Contains(frDown);//��ȷ�����ҷ���down=true�£�false��
        //��ȡ��ǰ���λ��
        int ColNum=(int)Memo1->CaretPos.x;//��0��ʼ����
        int RowNum=(int)Memo1->CaretPos.y;//��0��ʼ����
        AnsiString FindRange=Memo1->Lines->Strings[RowNum];//ȡ����RowNum��
        AnsiString FindText=FindDialog1->FindText;
        if((Sender==FindDialog1||Sender==FindNext||Sender==FindNextPopupItem)&&!FindDialog1->Options.Contains(frMatchCase)||Sender==ReplaceDialog1&&!ReplaceDialog1->Options.Contains(frMatchCase))
        {
                FindRange=FindRange.LowerCase();
                FindText=FindText.LowerCase();
        }

        if(down)//���ڲ�ѯ�����У�������²�ѯ�������ǰ�������ȥ��
                FindRange=FindRange.SubString(ColNum,FindRange.Length()-ColNum-1);
        else    //���ڲ�ѯ�����У�������ϲ�ѯ���������������ȥ��
                FindRange=FindRange.SubString(0,ColNum+1-Memo1->SelLength);

        while(down?RowNum<Memo1->Lines->Count:RowNum>=0)
        {
                int index;
                if(down)
                {
                        index=FindRange.Pos(FindText); //index��ֵ��1��ʼ
                }
                else
                {
                        ColNum=FindRange.Length()-1;
                        int length=1;
                        for(index=0; ColNum>=0 && index<=0; ColNum--,length++){
                                AnsiString PartFindRange=FindRange.SubString(ColNum,length);
                                index=PartFindRange.Pos(FindText);

                        }
                }
                if(index<=0)
                {   //<=0��ʾδ����
                        down?RowNum++:RowNum--; //��һ�в�ѯ
                        ColNum=0;
                        FindRange=Memo1->Lines->Strings[RowNum];//���ǲ�ѯ�����У��򲻱ؽ�ȡ
                        continue;
                }
                if(down)
                        ColNum=ColNum==0?index-1:ColNum+index-2;
                Memo1->CaretPos=TPoint(ColNum,RowNum);
                Memo1->SelLength=FindText.Length();
                break;
        }
        if(down?RowNum>=Memo1->Lines->Count:RowNum<0)
                Application->MessageBox(("�Ҳ���"+FindDialog1->FindText).c_str(),"��Ϣ",MB_OK|MB_ICONINFORMATION);
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReplaceDialog1Replace(TObject *Sender)
{
      int index;
        if(ReplaceDialog1->Options.Contains(frMatchCase))
                index=Memo1->Text.AnsiPos(ReplaceDialog1->FindText)-1;
        else
                index=Memo1->Text.LowerCase().AnsiPos(ReplaceDialog1->FindText.LowerCase())-1;
        if(index>=0)
        {
                if(ReplaceDialog1->Options.Contains(frReplaceAll))
                {
                        if(ReplaceDialog1->Options.Contains(frMatchCase))
                                Memo1->Text=AnsiReplaceStr(Memo1->Text,ReplaceDialog1->FindText,ReplaceDialog1->ReplaceText);
                        else
                                Memo1->Text=AnsiReplaceText(Memo1->Text,ReplaceDialog1->FindText,ReplaceDialog1->ReplaceText);
                }
                else{
                        Memo1->SelStart=index;
                        Memo1->SelLength=strlen(ReplaceDialog1->FindText.c_str());
                        Memo1->SelText=ReplaceDialog1->ReplaceText;
                }
                ReplaceDialog1->CloseDialog();
        }
        else
                Application->MessageBox("δ���֡�           ","��Ϣ",MB_OK|MB_ICONINFORMATION);

        EnableEditSubMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReplaceClick(TObject *Sender)
{
        if(Memo1->SelLength>0)
                ReplaceDialog1->FindText=Memo1->SelText;
        ReplaceDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectAllClick(TObject *Sender)
{
        Memo1->SelectAll();
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FontClick(TObject *Sender)
{
        if(Memo2->Focused())
      	        FontDialog1-> Font= Memo2->Font;
       else
       	        FontDialog1-> Font= Memo1->Font;

        if(FontDialog1->Execute()){
                if(Memo2->Focused())
         	        Memo2-> Font= FontDialog1->Font;
                else
         	        Memo1-> Font= FontDialog1->Font;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorClick(TObject *Sender)
{
        if(ColorDialog1->Execute())
                if(Memo2->Focused())
                        if(Sender==BackgroundColor)
                	        Memo2->Color= ColorDialog1->Color;
                        else
                	        Memo2-> Font->Color= ColorDialog1->Color;
                else
                        if(Sender==BackgroundColor)
                	        Memo1->Color= ColorDialog1->Color;
                        else
                	        Memo1-> Font->Color= ColorDialog1->Color;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::BackgroundColorClick(TObject *Sender)
{
        if(ColorDialog1->Execute())
                if(Memo1->Focused())
                        if(Sender==BackgroundColor)
                	        Memo1->Color= ColorDialog1->Color;
                        else
                	        Memo1-> Font->Color= ColorDialog1->Color;
                else
                        if(Sender==BackgroundColor)
                	        Memo2->Color= ColorDialog1->Color;
                        else
                	        Memo2-> Font->Color= ColorDialog1->Color;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::CompileLinkClick(TObject *Sender)
{
        if(!DirectoryExists(BinPath)||!DirectoryExists(IncludePath)||!DirectoryExists(LibraryPath)){
          Application->MessageBox("��������ӳ���δ��װ��ʧ","����",MB_OK|MB_ICONSTOP);
          return;
        }
        AnsiString FileExt=ExtractFileExt(FileName);
        FileExt=FileExt.LowerCase();
        if(FileExt!=".c" && FileExt!=".cpp" && FileExt!=".h"){
          Application->MessageBox("Դ�����׺���󣬺�׺������c��cpp��h","����",MB_OK|MB_ICONSTOP);
          return;
        }
        SaveClick(Sender);//�ȱ���Դ�����ļ�
        AnsiString MessageFile=HomePath+"tmp.txt";//������Ϣ�ļ���tmp.txt
        AnsiString BatFile=HomePath+"tmp.bat"; //�������ļ���tmp.bat

        if (FileExists(BatFile)) DeleteFile(BatFile);//���������ļ�ɾ��
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//�Ƚ�������Ϣ�ļ�ɾ��

        //���������ַ���,������������Ϣ�����ڱ�����Ϣ�ļ�tmp.txt�У������������£�
        //  AnsiString CompileCommand="tcc -ms -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath+" -P -y -ll "+FileName+" graphics.lib > "+MessageFile;
        //  -Iָ��Iclude·����-Lָ��Lib·����-nָ��exe�ļ�����·����-P��ʾʹ��C++���룬-y��ʾ��������к���Ϣ��-ll��ʾ����ѡ��

        AnsiString CompileCommand="tcc";
        //���ñ���ģʽ

        CompileCommand+=" -m"+AnsiString(m);

        //����Include,Library�� EXE�ļ� ·��
        CompileCommand+=" -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath;

        //�����Ƿ�ʹ��C++������
        if(p=='p' || FileExt==".cpp")
                CompileCommand+=" -P";        //����ʹ��C++������
        else
                CompileCommand+=" -P-";       //���ò�ʹ��C++������

        if(Sender==Compile||Sender==CompileToolButton)CompileCommand+=" -c"; //�����Compile��ť����ֻ���룬������.
        //�����кŵ�
        CompileCommand+=" -y -ll "+FileName;
        //����ͼ�ο�
        if(g=='g')CompileCommand+=" graphics.lib";

        //������Ϣ�ļ���
        CompileCommand+=" > "+MessageFile;

        CreateBatFile(BatFile, CompileCommand);//�����������ļ�tmp.bat�������б���������������
        if((int)ShellExecute(this->Handle,"open",BatFile.c_str(),NULL,HomePath.c_str(),SW_HIDE)<=32){//ִ���������ļ�tmp.bat
          Application->MessageBox("��������ӳ���δ��װ��ʧ","����",MB_OK|MB_ICONSTOP);
          return;
        }
        Memo2->Lines->Clear();
        if(Sender==Compile||Sender==CompileToolButton){
                Memo2->Text="���ڱ��룬���Ե�...";
                Application->MessageBox("������ɡ�        ","��Ϣ",MB_OK|MB_ICONINFORMATION);
        }
        else{
                Memo2->Text="���ڱ������ӣ����Ե�...";
                Application->MessageBox("����������ɡ�        ","��Ϣ",MB_OK|MB_ICONINFORMATION);
        }
//        this->Cursor=crHourGlass;
        while(!FileExists(MessageFile)){
                Sleep(2000);//�����Ϣ�ļ�δ���ɣ���ʾ��������δ��ɣ���ȴ�1�롣
        }
//        this->Cursor=crDefault;
        Memo2->Lines->Clear();
        if (FileExists(MessageFile)){
                while(1){
                        try{
                                Memo2->Lines->LoadFromFile(MessageFile.c_str());//��Memo2��ʾ����������Ϣ�ļ�tmp.txt
                                break;
                        }catch(Exception &ex){Sleep(2000);}
                }
                Memo2->Lines->Delete(0);
                if (Memo2->Text.Pos("Error")!=0 || Memo2->Text.Pos("error")!=0 ||Memo2->Text.Pos("ERROR")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������������˫�����д�����Ϣ�У�������Դ������������С�":"����������Ӵ���δ����EXE���������˫�����д�����Ϣ�У�������Դ������������С�");
                        Memo2->SetFocus();
                }
                else if (Memo2->Text.Pos("Warning")!=0 || Memo2->Text.Pos("warning")!=0 ||Memo2->Text.Pos("WARNING")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������ȷ�������о�����Ϣ��":"�������������ȷ���������У������о�����Ϣ��");
                        Memo2->SetFocus();
                }
                else
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������ȫ��ȷ":"�������������ȫ��ȷ���������С�");
        }
        if (FileExists(BatFile)) DeleteFile(BatFile);//���������ļ�ɾ��
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//��������Ϣ�ļ�ɾ��
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RunClick(TObject *Sender)
{
        AnsiString ExeFileName=FileName.SubString(0,FileName.Pos("."))+"exe";
        ExeFileName=ExtractFileName(ExeFileName);
        Memo2->Lines->Clear();
        Memo2->Lines->Add("����"+ExePath+ExeFileName+"...");
        if((int)ShellExecute(this->Handle,"open",ExeFileName.c_str(),NULL,ExePath.c_str(),SW_SHOW)<=32)
                Application->MessageBox("����δ��������","����",MB_OK|MB_ICONSTOP);
        Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateBatFile(AnsiString BatFile, AnsiString cmd)
{
        FILE *fp=fopen(BatFile.c_str(),"w+");
        if(fp==NULL)return;
        AnsiString ChangeDir="cd\\\ncd "+BinPath;
        fprintf(fp,"%s\n",ChangeDir);
        fprintf(fp,"%s\n",cmd);
        ChangeDir="cd\\\ncd "+HomePath;
        fprintf(fp,"%s\n",ChangeDir);
        fclose(fp);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OptionClick(TObject *Sender)
{
        //����·��ѡ��
        OptionDlg->Edit1->Text=IncludePath;
        OptionDlg->Edit2->Text=LibraryPath;
        OptionDlg->Edit3->Text=CppPath;
        OptionDlg->Edit4->Text=ExePath;
       //���ñ���ģʽѡ��
        switch(m){
                case 't':
                        OptionDlg->TinyRadioButton->Checked=true;
                        break;
                case 's':
                        OptionDlg->SmallRadioButton->Checked=true;
                        break;
                case 'c':
                        OptionDlg->CompactRadioButton->Checked=true;
                        break;
                case 'm':
                        OptionDlg->MediumRadioButton->Checked=true;
                        break;
                case 'l':
                        OptionDlg->LargeRadioButton->Checked=true;
                        break;
                case 'h':
                        OptionDlg->HugeRadioButton->Checked=true;
                        break;
       }
       //�����Ƿ�ʹ��C++������ѡ��
       if(p=='p')
                OptionDlg->CppAlwaysRadioButton->Checked=true;
       else
                OptionDlg->CppOnlyRadioButton->Checked=true;
       //�����Ƿ�ʹ��ͼ�ο�ѡ��
       if(g=='g')
                OptionDlg->GraphicsCheckBox->Checked=true;
       else
                OptionDlg->GraphicsCheckBox->Checked=false;

        if(OptionDlg->ShowModal()==IDOK)
        {
                IncludePath=OptionDlg->Edit1->Text;
                LibraryPath=OptionDlg->Edit2->Text;
                CppPath=OptionDlg->Edit3->Text;
                ExePath=OptionDlg->Edit4->Text;
                OpenDialog1->InitialDir=CppPath;
                SaveDialog1->InitialDir=CppPath;

                FILE *fp=fopen((HomePath+"config.txt").c_str(),"w+");
                if(fp!=NULL){
                        //����·��ѡ��
                        fprintf(fp,"%s\n",IncludePath.c_str());
                        fprintf(fp,"%s\n",LibraryPath.c_str());
                        fprintf(fp,"%s\n",CppPath.c_str());
                        fprintf(fp,"%s\n",ExePath.c_str());

                        //�������ģʽ
                        if(OptionDlg->TinyRadioButton->Checked)
                                fputc(m='t',fp);
                        else if(OptionDlg->SmallRadioButton->Checked)
                                fputc(m='s',fp);
                        else if(OptionDlg->CompactRadioButton->Checked)
                                fputc(m='c',fp);
                        else if(OptionDlg->MediumRadioButton->Checked)
                                fputc(m='m',fp);
                         else if(OptionDlg->LargeRadioButton->Checked)
                                fputc(m='l',fp);
                        else if(OptionDlg->HugeRadioButton->Checked)
                                fputc(m='h',fp);

                        //�����Ƿ�ʹ��C++������ѡ��
                        if(OptionDlg->CppAlwaysRadioButton->Checked)
                                fputc(p='p',fp);//ʹ��C++������
                        else
                                fputc(p='P',fp);//��ʹ��C++������

                        //�����Ƿ�ʹ��ͼ�ο�ѡ��
                        if(OptionDlg->GraphicsCheckBox->Checked)
                                fputc(g='g',fp); //ʹ��ͼ�ο�
                        else
                                fputc(g='G',fp); //��ʹ��ͼ�ο�

                        fclose(fp);
                }
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CompileClick(TObject *Sender)
{
        if(!DirectoryExists(BinPath)||!DirectoryExists(IncludePath)||!DirectoryExists(LibraryPath)){
          Application->MessageBox("��������ӳ���δ��װ��ʧ","����",MB_OK|MB_ICONSTOP);
          return;
        }
        AnsiString FileExt=ExtractFileExt(FileName);
        FileExt=FileExt.LowerCase();
        if(FileExt!=".c" && FileExt!=".cpp" && FileExt!=".h"){
          Application->MessageBox("Դ�����׺���󣬺�׺������c��cpp��h","����",MB_OK|MB_ICONSTOP);
          return;
        }
        SaveClick(Sender);//�ȱ���Դ�����ļ�
        AnsiString MessageFile=HomePath+"tmp.txt";//������Ϣ�ļ���tmp.txt
        AnsiString BatFile=HomePath+"tmp.bat"; //�������ļ���tmp.bat

        if (FileExists(BatFile)) DeleteFile(BatFile);//���������ļ�ɾ��
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//�Ƚ�������Ϣ�ļ�ɾ��

        //���������ַ���,������������Ϣ�����ڱ�����Ϣ�ļ�tmp.txt�У������������£�
        //  AnsiString CompileCommand="tcc -ms -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath+" -P -y -ll "+FileName+" graphics.lib > "+MessageFile;
        //  -Iָ��Iclude·����-Lָ��Lib·����-nָ��exe�ļ�����·����-P��ʾʹ��C++���룬-y��ʾ��������к���Ϣ��-ll��ʾ����ѡ��

        AnsiString CompileCommand="tcc";
        //���ñ���ģʽ

        CompileCommand+=" -m"+AnsiString(m);

        //����Include,Library�� EXE�ļ� ·��
        CompileCommand+=" -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath;

        //�����Ƿ�ʹ��C++������
        if(p=='p' || FileExt==".cpp")
                CompileCommand+=" -P";        //����ʹ��C++������
        else
                CompileCommand+=" -P-";       //���ò�ʹ��C++������

        if(Sender==Compile||Sender==CompileToolButton)CompileCommand+=" -c"; //�����Compile��ť����ֻ���룬������.
        //�����кŵ�
        CompileCommand+=" -y -ll "+FileName;
        //����ͼ�ο�
        if(g=='g')CompileCommand+=" graphics.lib";

        //������Ϣ�ļ���
        CompileCommand+=" > "+MessageFile;

        CreateBatFile(BatFile, CompileCommand);//�����������ļ�tmp.bat�������б���������������
        if((int)ShellExecute(this->Handle,"open",BatFile.c_str(),NULL,HomePath.c_str(),SW_HIDE)<=32){//ִ���������ļ�tmp.bat
          Application->MessageBox("��������ӳ���δ��װ��ʧ","����",MB_OK|MB_ICONSTOP);
          return;
        }
        Memo2->Lines->Clear();
        if(Sender==Compile||Sender==CompileToolButton){
                Memo2->Text="���ڱ��룬���Ե�...";
                Application->MessageBox("������ɡ�        ","��Ϣ",MB_OK|MB_ICONINFORMATION);
        }
        else{
                Memo2->Text="���ڱ������ӣ����Ե�...";
                Application->MessageBox("����������ɡ�        ","��Ϣ",MB_OK|MB_ICONINFORMATION);
        }
//        this->Cursor=crHourGlass;
        while(!FileExists(MessageFile)){
                Sleep(2000);//�����Ϣ�ļ�δ���ɣ���ʾ��������δ��ɣ���ȴ�1�롣
        }
//        this->Cursor=crDefault;
        Memo2->Lines->Clear();
        if (FileExists(MessageFile)){
                while(1){
                        try{
                                Memo2->Lines->LoadFromFile(MessageFile.c_str());//��Memo2��ʾ����������Ϣ�ļ�tmp.txt
                                break;
                        }catch(Exception &ex){Sleep(2000);}
                }
                Memo2->Lines->Delete(0);
                if (Memo2->Text.Pos("Error")!=0 || Memo2->Text.Pos("error")!=0 ||Memo2->Text.Pos("ERROR")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������������˫�����д�����Ϣ�У�������Դ������������С�":"����������Ӵ���δ����EXE���������˫�����д�����Ϣ�У�������Դ������������С�");
                        Memo2->SetFocus();
                }
                else if (Memo2->Text.Pos("Warning")!=0 || Memo2->Text.Pos("warning")!=0 ||Memo2->Text.Pos("WARNING")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������ȷ�������о�����Ϣ��":"�������������ȷ���������У������о�����Ϣ��");
                        Memo2->SetFocus();
                }
                else
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"���������ȫ��ȷ":"�������������ȫ��ȷ���������С�");
        }
        if (FileExists(BatFile)) DeleteFile(BatFile);//���������ļ�ɾ��
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//��������Ϣ�ļ�ɾ��        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindRowClick(TObject *Sender)
{
         AnsiString RowNum=InputBox("�кŲ���","�������к�:","");
        if(RowNum!="")
                FindRowInMemo1(RowNum.ToInt());
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::FindRowInMemo1(int RowNum)
{
                Memo1->SetFocus();
                if(RowNum>Memo1->Lines->Count){
                        Application->MessageBox("δ���֡�           ","����",MB_OK|MB_ICONSTOP);
                        return;
                }
                Memo1->CaretPos=TPoint(0,RowNum);
                Memo1->SelLength=Memo1->Lines->Strings[RowNum].Length();
}




//---------------------------------------------------------------------------







void __fastcall TForm1::CopyClick(TObject *Sender)
{

        Memo1->CopyToClipboard();
        EnableEditSubMenu();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::AboutClick(TObject *Sender)
{
        Form2->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EnableEditSubMenu()
{


        Undo->Enabled=true;
        UndoToolButton->Enabled=true;
        UndoPopupItem->Enabled=true;


        Copy->Enabled=true;
        CopyToolButton->Enabled=true;
        CopyPopupItem->Enabled=true;

        Cut->Enabled=true;
        CutToolButton->Enabled=true;
        CutPopupItem->Enabled=true;

        Delete->Enabled=true;
        DeleteToolButton->Enabled=true;
        DeletePopupItem->Enabled=true;



        Paste->Enabled=true;
        PasteToolButton->Enabled=true;
        PastePopupItem->Enabled=true;

        Save->Enabled=MemoChanged;
        SaveToolButton->Enabled=MemoChanged;
        DisplayCaretPosOnStatusBar1();
     }




//---------------------------------------------------------------------------
void __fastcall TForm1::HelpTopicClick(TObject *Sender)
{
        if((int)ShellExecute(this->Handle,"open","C�����ٲ�.chm",NULL,HomePath.c_str(),SW_SHOW)<=32)
        Application->MessageBox("�����ļ�'C�����ٲ�.chm'��ʧ","����",MB_OK|MB_ICONSTOP);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo2DblClick(TObject *Sender)
{
        //˫����������������
     try{
        int ErrorRow;
        //�ڱ�����Ϣ��˫�������������������С�
        AnsiString ErrorClicked=Memo2->Lines->Strings[Memo2->CaretPos.y];
        int ErrorRowStartPos=ErrorClicked.Pos(FileName.LowerCase());
        int ErrorRowEndPos=ErrorClicked.Pos(": ");
        if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos)
        {//������Ϣ�а����кţ����ҵ��к�
                ErrorRowStartPos+=FileName.Length()+1;
                ErrorRow=ErrorClicked.SubString(ErrorRowStartPos,ErrorRowEndPos-ErrorRowStartPos).ToInt()-1;
                FindRowInMemo1(ErrorRow);
        }
        else{//������Ϣ�в������кţ����ҵ��ؼ��֣�����������
                if(FindDialog1->Options.Contains(frDown))
                        Memo1->SelStart=0;//�������Memo1��ͷ
                else
                        Memo1->SelStart=Memo1->Text.Length()-1;//�������Memo1��β��
                ErrorRowStartPos=ErrorClicked.Pos("_");//���溯��δ�������
                ErrorRowEndPos=ErrorClicked.Pos(" in module");
                if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos){
                        Memo1->SetFocus();
                        FindDialog1->FindText=ErrorClicked.SubString(ErrorRowStartPos+1,ErrorRowEndPos-ErrorRowStartPos-1);
                        FindDialog1Find(NULL);
                }
                else{
                        ErrorRowStartPos=ErrorClicked.Pos("::");//���к�����Աδ�������
                        ErrorRowEndPos=ErrorClicked.Pos("(");
                        if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos){
                                Memo1->SetFocus();
                                FindDialog1->FindText=ErrorClicked.SubString(ErrorRowStartPos+2,ErrorRowEndPos-ErrorRowStartPos-2);
                                FindDialog1Find(NULL);
                        }
                        else{
                                ErrorRowStartPos=ErrorClicked.Pos("::");//�������ݳ�Աδ��ʼ������
                                ErrorRowEndPos=ErrorClicked.Pos(" in module");
                                if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos){
                                        Memo1->SetFocus();
                                        FindDialog1->FindText=ErrorClicked.SubString(ErrorRowStartPos+2,ErrorRowEndPos-ErrorRowStartPos-2);
                                        FindDialog1Find(NULL);
                                }//if
                        }//if
                }//if
        }//if
    }catch(Exception &ex){};        
}
//---------------------------------------------------------------------------

