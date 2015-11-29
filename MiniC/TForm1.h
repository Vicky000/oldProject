//---------------------------------------------------------------------------

#ifndef TForm1H
#define TForm1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TMainMenu *MainMenu;
        TMenuItem *edition;
        TMenuItem *from;
        TMenuItem *Run1;
        TMenuItem *help;
        TToolButton *NewToolButton;
        TToolButton *OpenToolButton;
        TToolButton *SaveToolButton;
        TMenuItem *New;
        TMenuItem *Open;
        TMenuItem *Save;
        TMenuItem *SaveAs;
        TMenuItem *Exit;
        TMenuItem *file;
        TImageList *ImageList1;
        TToolButton *ToolButton4;
        TToolButton *UndoToolButton;
        TToolButton *CutToolButton;
        TToolButton *CopyToolButton;
        TToolButton *PasteToolButton;
        TToolButton *DeleteToolButton;
        TToolButton *FindToolButton;
        TToolButton *ReplaceToolButton;
        TToolButton *ToolButton12;
        TToolButton *FontToolButton;
        TToolButton *ColorToolButton;
        TToolButton *ToolButton15;
        TToolButton *CompileLinkToolButton;
        TToolButton *RunToolButton;
        TToolButton *OptionToolButton;
        TToolButton *ToolButton19;
        TMenuItem *Undo;
        TMenuItem *Cut;
        TMenuItem *Copy;
        TMenuItem *Paste;
        TMenuItem *Delete;
        TMenuItem *Find;
        TMenuItem *FindNext;


        TMenuItem *Replace;
        TMenuItem *SelectAll;
        TMenuItem *Font;
        TMenuItem *Color;
        TMenuItem *CompileLink;
        TMenuItem *Run;
        TMenuItem *Option;
        TMenuItem *HelpTopic;
        TMenuItem *About;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TFontDialog *FontDialog1;
        TColorDialog *ColorDialog1;
        TFindDialog *FindDialog1;
        TReplaceDialog *ReplaceDialog1;
        TStatusBar *StatusBar1;


        TMemo *Memo2;
        TSplitter *Splitter1;
        TMemo *Memo1;
        TPopupMenu *PopupMenu1;
        TMenuItem *UndoPopupItem;
        TMenuItem *CutPopupItem;
        TMenuItem *CopyPopupItem;
        TMenuItem *PastePopupItem;
        TMenuItem *DeletePopupItem;
        TMenuItem *SelectAllPopupItem;
        TMenuItem *FindPopupItem;
        TMenuItem *FindNextPopupItem;
        TMenuItem *ReplacePopupItem;
        TMenuItem *FindRowPopupItem;
        TMenuItem *FindRow;
        TMenuItem *BackgroundColor;
        TToolButton *AboutToolButton;
        TMenuItem *Compile;
        TToolButton *HelpTopicToolButton;
        TToolButton *CompileToolButton;
        TMenuItem *N1;
        void __fastcall StatusBarDisplay(AnsiString mesg);
        void __fastcall ExitClick(TObject *Sender);
        void __fastcall OpenClick(TObject *Sender);
        void __fastcall NewClick(TObject *Sender);
        void __fastcall SaveAsClick(TObject *Sender);
        void __fastcall DisplayCaretPosOnStatusBar1();
        void __fastcall Form1Create(TObject *Sender);
        void __fastcall Form1Close(TObject *Sender, TCloseAction &Action);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall SaveClick(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall UndoClick(TObject *Sender);
        void __fastcall CutClick(TObject *Sender);
        void __fastcall PasteClick(TObject *Sender);
        void __fastcall DeleteClick(TObject *Sender);
        void __fastcall FindClick(TObject *Sender);
        void __fastcall FindDialog1Find(TObject *Sender);
        void __fastcall FindNextClick(TObject *Sender);
        void __fastcall ReplaceDialog1Replace(TObject *Sender);
        void __fastcall ReplaceClick(TObject *Sender);
        void __fastcall SelectAllClick(TObject *Sender);
        void __fastcall FontClick(TObject *Sender);
        void __fastcall ColorClick(TObject *Sender);
        void __fastcall BackgroundColorClick(TObject *Sender);
        void __fastcall CompileLinkClick(TObject *Sender);
        void __fastcall RunClick(TObject *Sender);
        void __fastcall CreateBatFile(AnsiString BatFileName, AnsiString cmd);
        void __fastcall OptionClick(TObject *Sender);
        void __fastcall CompileClick(TObject *Sender);
        void __fastcall FindRowClick(TObject *Sender);
        void __fastcall FindRowInMemo1(int RowNum);
        void __fastcall CopyClick(TObject *Sender);
        void __fastcall AboutClick(TObject *Sender);
        void __fastcall EnableEditSubMenu();
        void __fastcall HelpTopicClick(TObject *Sender);
        void __fastcall Memo2DblClick(TObject *Sender);


private:
        bool MemoChanged,WasRecording;
        AnsiString FileName;//�ı��ļ���
        	// User declarations
public:		// User declarations
        AnsiString HomePath;//����װ��·��
        AnsiString BinPath; //Turbo C++3.0��װ��·��
        AnsiString IncludePath,LibraryPath,CppPath,ExePath;//�ĸ�����ѡ���·��
        char m,p,g;
        //m��ʾ����ģʽ(t-tiny,s-small,c-compact,m-medium,l-large,h-huge)
        //p��ʾ��ʹ��C++������(p�ǣ�P��)
        //g��ʾ�Ƿ�ʹ��ͼ�ο�(g�ǣ�G��)

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
