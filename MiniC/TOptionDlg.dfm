object OptionDlg: TOptionDlg
  Left = 519
  Top = 286
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #36873#39033
  ClientHeight = 350
  ClientWidth = 648
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 561
    Height = 161
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 71
    Height = 13
    Caption = 'Include'#36335#24452#65306
  end
  object Label2: TLabel
    Left = 24
    Top = 64
    Width = 67
    Height = 13
    Caption = 'Library'#36335#24452#65306
  end
  object Label3: TLabel
    Left = 24
    Top = 96
    Width = 72
    Height = 13
    Caption = #28304#31243#24207#36335#24452#65306
  end
  object Label4: TLabel
    Left = 24
    Top = 128
    Width = 81
    Height = 13
    Caption = 'EXE'#31243#24207#36335#24452#65306
  end
  object OKBtn: TButton
    Left = 207
    Top = 308
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 311
    Top = 308
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 136
    Top = 24
    Width = 297
    Height = 21
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 136
    Top = 56
    Width = 297
    Height = 21
    TabOrder = 3
  end
  object Edit3: TEdit
    Left = 136
    Top = 96
    Width = 297
    Height = 21
    TabOrder = 4
  end
  object Edit4: TEdit
    Left = 136
    Top = 128
    Width = 297
    Height = 21
    TabOrder = 5
  end
  object BrowseButton1: TButton
    Left = 464
    Top = 24
    Width = 75
    Height = 25
    Caption = #27983#35272
    TabOrder = 6
    OnClick = BrowseButton1Click
  end
  object BrowseButton2: TButton
    Left = 464
    Top = 56
    Width = 75
    Height = 25
    Caption = #27983#35272
    TabOrder = 7
    OnClick = BrowseButton2Click
  end
  object BrowseButton3: TButton
    Left = 464
    Top = 96
    Width = 75
    Height = 25
    Caption = #27983#35272
    TabOrder = 8
    OnClick = BrowseButton3Click
  end
  object BrowseButton4: TButton
    Left = 464
    Top = 128
    Width = 75
    Height = 25
    Caption = #27983#35272
    TabOrder = 9
    OnClick = BrowseButton4Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 192
    Width = 273
    Height = 105
    Caption = #32534#35793#27169#24335
    TabOrder = 10
    object TinyRadioButton: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Tiny'
      TabOrder = 0
    end
    object SmallRadioButton: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Small'
      Checked = True
      TabOrder = 1
      TabStop = True
    end
    object MediumRadioButton: TRadioButton
      Left = 8
      Top = 72
      Width = 113
      Height = 17
      Caption = 'Medium'
      TabOrder = 2
    end
    object CompactRadioButton: TRadioButton
      Left = 152
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Compact'
      TabOrder = 3
    end
    object LargeRadioButton: TRadioButton
      Left = 152
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Large'
      TabOrder = 4
    end
    object HugeRadioButton: TRadioButton
      Left = 152
      Top = 72
      Width = 113
      Height = 17
      Caption = 'Huge'
      TabOrder = 5
    end
  end
  object GroupBox2: TGroupBox
    Left = 312
    Top = 192
    Width = 257
    Height = 105
    Caption = 'C++'#32534#35793#22120#21644#38142#25509#22120
    TabOrder = 11
    object CppAlwaysRadioButton: TRadioButton
      Left = 16
      Top = 24
      Width = 185
      Height = 17
      Caption = #24635#26159#20351#29992'C++'#32534#35793#22120
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object CppOnlyRadioButton: TRadioButton
      Left = 16
      Top = 48
      Width = 201
      Height = 17
      Caption = #21518#32512#26159'CPP'#26102#20351#29992'C++'#32534#35793#22120
      TabOrder = 1
    end
    object GraphicsCheckBox: TCheckBox
      Left = 16
      Top = 72
      Width = 145
      Height = 17
      Caption = #38142#25509'Turbo C'#22270#24418#24211
      TabOrder = 2
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = #24403#21069#25991#20214#22841
    Title = #25351#23450#36335#24452
    Left = 56
    Top = 312
  end
end
