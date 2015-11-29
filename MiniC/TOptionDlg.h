//----------------------------------------------------------------------------
#ifndef TOptionDlgH
#define TOptionDlgH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Dialogs.hpp>
//----------------------------------------------------------------------------
class TOptionDlg : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TButton *BrowseButton1;
        TButton *BrowseButton2;
        TButton *BrowseButton3;
        TButton *BrowseButton4;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TRadioButton *TinyRadioButton;
        TRadioButton *SmallRadioButton;
        TRadioButton *MediumRadioButton;
        TRadioButton *CompactRadioButton;
        TRadioButton *LargeRadioButton;
        TRadioButton *HugeRadioButton;
        TRadioButton *CppAlwaysRadioButton;
        TRadioButton *CppOnlyRadioButton;
        TCheckBox *GraphicsCheckBox;
        TOpenDialog *OpenDialog1;
        void __fastcall BrowseButton1Click(TObject *Sender);
        void __fastcall BrowseButton2Click(TObject *Sender);
        void __fastcall BrowseButton3Click(TObject *Sender);
        void __fastcall BrowseButton4Click(TObject *Sender);
private:
public:
	virtual __fastcall TOptionDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOptionDlg *OptionDlg;
//----------------------------------------------------------------------------
#endif    
