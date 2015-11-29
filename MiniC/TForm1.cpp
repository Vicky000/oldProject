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
                if(Application->MessageBox("文本内容被改变，是否放弃改变？","信息",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
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
                        Caption=Hint+" —"+FileName;
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
                if(Application->MessageBox("文本内容被改变，是否放弃改变？","信息",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
                        MemoChanged=false;
       }
        if(!MemoChanged)
        {
                Memo1->Clear();
                FileName="noname.c";
                Caption=Hint+" —"+FileName;
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
                Caption=Hint+" —"+FileName;
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
        StatusBar1->Panels->Items[0]->Text="  总行数："+IntToStr(Memo1->Lines->Count);
        StatusBar1->Panels->Items[1]->Text="  光标位置："+IntToStr(Memo1->CaretPos.y+1)+"行, "+IntToStr(Memo1->CaretPos.x+1)+"列";
}




//---------------------------------------------------------------------------


void __fastcall TForm1::Form1Create(TObject *Sender)
{
        HomePath=ExtractFilePath(ParamStr(0));
        BinPath=HomePath+"TC\\BIN\\";
        FILE *fp=fopen((HomePath+"config.txt").c_str(),"r");
        if(fp!=NULL)
        {
                //读取路径
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

                m=fgetc(fp);                //读取编译模式
                p=fgetc(fp);                //读取是否使用C++编译器
                g=fgetc(fp);                //读取是否使用图形库

                fclose(fp);
        }
        else
        {
                IncludePath=HomePath+"TC\\INCLUDE\\";
                LibraryPath=HomePath+"TC\\LIB\\";
                CppPath=HomePath;
                ExePath=HomePath;
                m='s';//设置编译模式small
                p='p';//设置使用C++编译器
                g='G';//设置不使用Turbo C++3.0图形库
        }
        //char m,p,g; 在TForm1.h中定义
        //m表示编译模式(t-tiny,s-small,c-compact,m-medium,l-large,h-huge)
        //p表示否使用C++编译器(p是，P否)
        //g表示是否使用图形库(g是，G否)

        OpenDialog1->InitialDir=CppPath;
        SaveDialog1->InitialDir=CppPath;

        StatusBarDisplay("就 绪 ...");

        Memo1->SelStart=0;
        MemoChanged=false;
        FileName="noname.c";
        Caption=Hint+" —"+FileName;
        EnableEditSubMenu();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Form1Close(TObject *Sender, TCloseAction &Action)
{
       if(MemoChanged && Memo1->Lines->Count>0){
                if(Application->MessageBox("文本输入区内容被改变，是否放弃改变？","信息",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
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
                        Caption=Hint+" —"+FileName;
                        MemoChanged=false;
                        Save->Enabled=false;
                        SaveToolButton->Enabled=false;
                    
                }
        }
        else
        {//如果FileName!="nomame.c" &&FileName!="noname.cpp"
             //或 Sender==Compile或Sender==CompileButton，
             //或 Sender==CompileLink或Sender==CompileLinkButton，则是从编译链接按钮来调用，不必出现保存对话框
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
	{              //替换对话框按下"查找下一个"按钮时调用此句
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
        bool down=FindDialog1->Options.Contains(frDown);//先确定查找方向down=true下，false上
        //获取当前光标位置
        int ColNum=(int)Memo1->CaretPos.x;//从0开始计数
        int RowNum=(int)Memo1->CaretPos.y;//从0开始计数
        AnsiString FindRange=Memo1->Lines->Strings[RowNum];//取出第RowNum行
        AnsiString FindText=FindDialog1->FindText;
        if((Sender==FindDialog1||Sender==FindNext||Sender==FindNextPopupItem)&&!FindDialog1->Options.Contains(frMatchCase)||Sender==ReplaceDialog1&&!ReplaceDialog1->Options.Contains(frMatchCase))
        {
                FindRange=FindRange.LowerCase();
                FindText=FindText.LowerCase();
        }

        if(down)//对于查询的首行，如果向下查询，将光标前面的内容去掉
                FindRange=FindRange.SubString(ColNum,FindRange.Length()-ColNum-1);
        else    //对于查询的首行，如果向上查询，将光标后面的内容去掉
                FindRange=FindRange.SubString(0,ColNum+1-Memo1->SelLength);

        while(down?RowNum<Memo1->Lines->Count:RowNum>=0)
        {
                int index;
                if(down)
                {
                        index=FindRange.Pos(FindText); //index的值从1开始
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
                {   //<=0表示未发现
                        down?RowNum++:RowNum--; //换一行查询
                        ColNum=0;
                        FindRange=Memo1->Lines->Strings[RowNum];//不是查询的首行，则不必截取
                        continue;
                }
                if(down)
                        ColNum=ColNum==0?index-1:ColNum+index-2;
                Memo1->CaretPos=TPoint(ColNum,RowNum);
                Memo1->SelLength=FindText.Length();
                break;
        }
        if(down?RowNum>=Memo1->Lines->Count:RowNum<0)
                Application->MessageBox(("找不到"+FindDialog1->FindText).c_str(),"信息",MB_OK|MB_ICONINFORMATION);
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
                Application->MessageBox("未发现。           ","信息",MB_OK|MB_ICONINFORMATION);

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
          Application->MessageBox("编译或链接程序未安装或丢失","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        AnsiString FileExt=ExtractFileExt(FileName);
        FileExt=FileExt.LowerCase();
        if(FileExt!=".c" && FileExt!=".cpp" && FileExt!=".h"){
          Application->MessageBox("源程序后缀错误，后缀必须是c、cpp或h","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        SaveClick(Sender);//先保存源程序文件
        AnsiString MessageFile=HomePath+"tmp.txt";//编译信息文件名tmp.txt
        AnsiString BatFile=HomePath+"tmp.bat"; //批处理文件名tmp.bat

        if (FileExists(BatFile)) DeleteFile(BatFile);//将批命令文件删除
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//先将编译信息文件删除

        //编译命令字符串,将编译链接信息保存在编译信息文件tmp.txt中，命令例子如下：
        //  AnsiString CompileCommand="tcc -ms -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath+" -P -y -ll "+FileName+" graphics.lib > "+MessageFile;
        //  -I指明Iclude路径，-L指明Lib路径，-n指明exe文件保存路经，-P表示使用C++编译，-y表示编译产生行号信息，-ll表示链接选项

        AnsiString CompileCommand="tcc";
        //设置编译模式

        CompileCommand+=" -m"+AnsiString(m);

        //设置Include,Library和 EXE文件 路径
        CompileCommand+=" -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath;

        //设置是否使用C++编译器
        if(p=='p' || FileExt==".cpp")
                CompileCommand+=" -P";        //设置使用C++编译器
        else
                CompileCommand+=" -P-";       //设置不使用C++编译器

        if(Sender==Compile||Sender==CompileToolButton)CompileCommand+=" -c"; //如果是Compile按钮，则只编译，不链接.
        //设置行号等
        CompileCommand+=" -y -ll "+FileName;
        //设置图形库
        if(g=='g')CompileCommand+=" graphics.lib";

        //设置信息文件名
        CompileCommand+=" > "+MessageFile;

        CreateBatFile(BatFile, CompileCommand);//创建批处理文件tmp.bat，在其中保存上述编译命令
        if((int)ShellExecute(this->Handle,"open",BatFile.c_str(),NULL,HomePath.c_str(),SW_HIDE)<=32){//执行批处理文件tmp.bat
          Application->MessageBox("编译或链接程序未安装或丢失","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        Memo2->Lines->Clear();
        if(Sender==Compile||Sender==CompileToolButton){
                Memo2->Text="正在编译，请稍等...";
                Application->MessageBox("编译完成。        ","信息",MB_OK|MB_ICONINFORMATION);
        }
        else{
                Memo2->Text="正在编译链接，请稍等...";
                Application->MessageBox("编译链接完成。        ","信息",MB_OK|MB_ICONINFORMATION);
        }
//        this->Cursor=crHourGlass;
        while(!FileExists(MessageFile)){
                Sleep(2000);//如果信息文件未生成，表示编译链接未完成，则等待1秒。
        }
//        this->Cursor=crDefault;
        Memo2->Lines->Clear();
        if (FileExists(MessageFile)){
                while(1){
                        try{
                                Memo2->Lines->LoadFromFile(MessageFile.c_str());//在Memo2显示编译链接信息文件tmp.txt
                                break;
                        }catch(Exception &ex){Sleep(2000);}
                }
                Memo2->Lines->Delete(0);
                if (Memo2->Text.Pos("Error")!=0 || Memo2->Text.Pos("error")!=0 ||Memo2->Text.Pos("ERROR")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译错误，用鼠标双击下列错误信息行，可跳到源程序错误所在行。":"程序编译链接错误，未产生EXE程序。用鼠标双击下列错误信息行，可跳到源程序错误所在行。");
                        Memo2->SetFocus();
                }
                else if (Memo2->Text.Pos("Warning")!=0 || Memo2->Text.Pos("warning")!=0 ||Memo2->Text.Pos("WARNING")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译正确，但是有警告信息。":"程序编译链接正确，可以运行，但是有警告信息。");
                        Memo2->SetFocus();
                }
                else
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译完全正确":"程序编译链接完全正确，可以运行。");
        }
        if (FileExists(BatFile)) DeleteFile(BatFile);//将批命令文件删除
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//将编译信息文件删除
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RunClick(TObject *Sender)
{
        AnsiString ExeFileName=FileName.SubString(0,FileName.Pos("."))+"exe";
        ExeFileName=ExtractFileName(ExeFileName);
        Memo2->Lines->Clear();
        Memo2->Lines->Add("运行"+ExePath+ExeFileName+"...");
        if((int)ShellExecute(this->Handle,"open",ExeFileName.c_str(),NULL,ExePath.c_str(),SW_SHOW)<=32)
                Application->MessageBox("程序未编译链接","错误",MB_OK|MB_ICONSTOP);
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
        //设置路径选项
        OptionDlg->Edit1->Text=IncludePath;
        OptionDlg->Edit2->Text=LibraryPath;
        OptionDlg->Edit3->Text=CppPath;
        OptionDlg->Edit4->Text=ExePath;
       //设置编译模式选项
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
       //设置是否使用C++编译器选项
       if(p=='p')
                OptionDlg->CppAlwaysRadioButton->Checked=true;
       else
                OptionDlg->CppOnlyRadioButton->Checked=true;
       //设置是否使用图形库选项
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
                        //保存路径选项
                        fprintf(fp,"%s\n",IncludePath.c_str());
                        fprintf(fp,"%s\n",LibraryPath.c_str());
                        fprintf(fp,"%s\n",CppPath.c_str());
                        fprintf(fp,"%s\n",ExePath.c_str());

                        //保存编译模式
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

                        //保存是否使用C++编译器选项
                        if(OptionDlg->CppAlwaysRadioButton->Checked)
                                fputc(p='p',fp);//使用C++编译器
                        else
                                fputc(p='P',fp);//不使用C++编译器

                        //保存是否使用图形库选项
                        if(OptionDlg->GraphicsCheckBox->Checked)
                                fputc(g='g',fp); //使用图形库
                        else
                                fputc(g='G',fp); //不使用图形库

                        fclose(fp);
                }
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CompileClick(TObject *Sender)
{
        if(!DirectoryExists(BinPath)||!DirectoryExists(IncludePath)||!DirectoryExists(LibraryPath)){
          Application->MessageBox("编译或链接程序未安装或丢失","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        AnsiString FileExt=ExtractFileExt(FileName);
        FileExt=FileExt.LowerCase();
        if(FileExt!=".c" && FileExt!=".cpp" && FileExt!=".h"){
          Application->MessageBox("源程序后缀错误，后缀必须是c、cpp或h","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        SaveClick(Sender);//先保存源程序文件
        AnsiString MessageFile=HomePath+"tmp.txt";//编译信息文件名tmp.txt
        AnsiString BatFile=HomePath+"tmp.bat"; //批处理文件名tmp.bat

        if (FileExists(BatFile)) DeleteFile(BatFile);//将批命令文件删除
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//先将编译信息文件删除

        //编译命令字符串,将编译链接信息保存在编译信息文件tmp.txt中，命令例子如下：
        //  AnsiString CompileCommand="tcc -ms -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath+" -P -y -ll "+FileName+" graphics.lib > "+MessageFile;
        //  -I指明Iclude路径，-L指明Lib路径，-n指明exe文件保存路经，-P表示使用C++编译，-y表示编译产生行号信息，-ll表示链接选项

        AnsiString CompileCommand="tcc";
        //设置编译模式

        CompileCommand+=" -m"+AnsiString(m);

        //设置Include,Library和 EXE文件 路径
        CompileCommand+=" -I"+IncludePath+" -L"+LibraryPath+" -n"+ExePath;

        //设置是否使用C++编译器
        if(p=='p' || FileExt==".cpp")
                CompileCommand+=" -P";        //设置使用C++编译器
        else
                CompileCommand+=" -P-";       //设置不使用C++编译器

        if(Sender==Compile||Sender==CompileToolButton)CompileCommand+=" -c"; //如果是Compile按钮，则只编译，不链接.
        //设置行号等
        CompileCommand+=" -y -ll "+FileName;
        //设置图形库
        if(g=='g')CompileCommand+=" graphics.lib";

        //设置信息文件名
        CompileCommand+=" > "+MessageFile;

        CreateBatFile(BatFile, CompileCommand);//创建批处理文件tmp.bat，在其中保存上述编译命令
        if((int)ShellExecute(this->Handle,"open",BatFile.c_str(),NULL,HomePath.c_str(),SW_HIDE)<=32){//执行批处理文件tmp.bat
          Application->MessageBox("编译或链接程序未安装或丢失","错误",MB_OK|MB_ICONSTOP);
          return;
        }
        Memo2->Lines->Clear();
        if(Sender==Compile||Sender==CompileToolButton){
                Memo2->Text="正在编译，请稍等...";
                Application->MessageBox("编译完成。        ","信息",MB_OK|MB_ICONINFORMATION);
        }
        else{
                Memo2->Text="正在编译链接，请稍等...";
                Application->MessageBox("编译链接完成。        ","信息",MB_OK|MB_ICONINFORMATION);
        }
//        this->Cursor=crHourGlass;
        while(!FileExists(MessageFile)){
                Sleep(2000);//如果信息文件未生成，表示编译链接未完成，则等待1秒。
        }
//        this->Cursor=crDefault;
        Memo2->Lines->Clear();
        if (FileExists(MessageFile)){
                while(1){
                        try{
                                Memo2->Lines->LoadFromFile(MessageFile.c_str());//在Memo2显示编译链接信息文件tmp.txt
                                break;
                        }catch(Exception &ex){Sleep(2000);}
                }
                Memo2->Lines->Delete(0);
                if (Memo2->Text.Pos("Error")!=0 || Memo2->Text.Pos("error")!=0 ||Memo2->Text.Pos("ERROR")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译错误，用鼠标双击下列错误信息行，可跳到源程序错误所在行。":"程序编译链接错误，未产生EXE程序。用鼠标双击下列错误信息行，可跳到源程序错误所在行。");
                        Memo2->SetFocus();
                }
                else if (Memo2->Text.Pos("Warning")!=0 || Memo2->Text.Pos("warning")!=0 ||Memo2->Text.Pos("WARNING")!=0){
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译正确，但是有警告信息。":"程序编译链接正确，可以运行，但是有警告信息。");
                        Memo2->SetFocus();
                }
                else
                        Memo2->Lines->Insert(0,Sender==Compile||Sender==CompileToolButton?"程序编译完全正确":"程序编译链接完全正确，可以运行。");
        }
        if (FileExists(BatFile)) DeleteFile(BatFile);//将批命令文件删除
        if (FileExists(MessageFile)) DeleteFile(MessageFile);//将编译信息文件删除        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindRowClick(TObject *Sender)
{
         AnsiString RowNum=InputBox("行号查找","请输入行号:","");
        if(RowNum!="")
                FindRowInMemo1(RowNum.ToInt());
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::FindRowInMemo1(int RowNum)
{
                Memo1->SetFocus();
                if(RowNum>Memo1->Lines->Count){
                        Application->MessageBox("未发现。           ","错误",MB_OK|MB_ICONSTOP);
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
        if((int)ShellExecute(this->Handle,"open","C函数速查.chm",NULL,HomePath.c_str(),SW_SHOW)<=32)
        Application->MessageBox("帮助文件'C函数速查.chm'丢失","错误",MB_OK|MB_ICONSTOP);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo2DblClick(TObject *Sender)
{
        //双击跳到错误所在行
     try{
        int ErrorRow;
        //在编译信息区双击，则跳到错误所在行。
        AnsiString ErrorClicked=Memo2->Lines->Strings[Memo2->CaretPos.y];
        int ErrorRowStartPos=ErrorClicked.Pos(FileName.LowerCase());
        int ErrorRowEndPos=ErrorClicked.Pos(": ");
        if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos)
        {//编译信息中包含行号，则找到行号
                ErrorRowStartPos+=FileName.Length()+1;
                ErrorRow=ErrorClicked.SubString(ErrorRowStartPos,ErrorRowEndPos-ErrorRowStartPos).ToInt()-1;
                FindRowInMemo1(ErrorRow);
        }
        else{//链接信息中不包含行号，则找到关键字，进行搜索。
                if(FindDialog1->Options.Contains(frDown))
                        Memo1->SelStart=0;//光标跳到Memo1开头
                else
                        Memo1->SelStart=Memo1->Text.Length()-1;//光标跳到Memo1结尾处
                ErrorRowStartPos=ErrorClicked.Pos("_");//常规函数未定义错误
                ErrorRowEndPos=ErrorClicked.Pos(" in module");
                if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos){
                        Memo1->SetFocus();
                        FindDialog1->FindText=ErrorClicked.SubString(ErrorRowStartPos+1,ErrorRowEndPos-ErrorRowStartPos-1);
                        FindDialog1Find(NULL);
                }
                else{
                        ErrorRowStartPos=ErrorClicked.Pos("::");//类中函数成员未定义错误
                        ErrorRowEndPos=ErrorClicked.Pos("(");
                        if(ErrorRowStartPos!=0&&ErrorRowEndPos!=0&&ErrorRowStartPos<ErrorRowEndPos){
                                Memo1->SetFocus();
                                FindDialog1->FindText=ErrorClicked.SubString(ErrorRowStartPos+2,ErrorRowEndPos-ErrorRowStartPos-2);
                                FindDialog1Find(NULL);
                        }
                        else{
                                ErrorRowStartPos=ErrorClicked.Pos("::");//类中数据成员未初始化错误
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

