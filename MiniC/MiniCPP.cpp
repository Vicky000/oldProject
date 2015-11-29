//---------------------------------------------------------------------------

#include <vcl.h>
#include "TForm2.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("TForm1.cpp", Form1);
USEFORM("TForm2.cpp", Form2);
USEFORM("TOptionDlg.cpp", OptionDlg);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "MiniC/C++集成编程环境";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TOptionDlg), &OptionDlg);
                 Form2->Show();
		 Form2->Update();
		 Sleep(700);
		 Form2->Hide();
		 Form2->BorderStyle=bsSingle;
		 Form2->BorderIcons<< biSystemMenu;
		 Form2->Height+=30;
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
