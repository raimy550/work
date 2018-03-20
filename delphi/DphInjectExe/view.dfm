object Form1: TForm1
  Left = 700
  Top = 240
  Width = 674
  Height = 506
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object btn1: TButton
    Left = 32
    Top = 392
    Width = 153
    Height = 49
    Caption = #36828#31243#27880#20837
    TabOrder = 0
    OnClick = btn1Click
  end
  object btn2: TButton
    Left = 472
    Top = 384
    Width = 169
    Height = 49
    Caption = #27880#20876#38057#23376
    TabOrder = 1
    OnClick = btn2Click
  end
  object txt1: TStaticText
    Left = 128
    Top = 264
    Width = 143
    Height = 17
    Caption = #36873#25321'INFO_DMS.EXE'#36335#24452#65306
    TabOrder = 2
  end
  object btn3: TcxButton
    Left = 432
    Top = 264
    Width = 41
    Height = 17
    Caption = '...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = btn3Click
  end
  object btn4: TcxButton
    Left = 240
    Top = 304
    Width = 161
    Height = 49
    Caption = #24320#22987
    TabOrder = 3
    OnClick = btn4Click
  end
  object cxtxtdt1: TcxTextEdit
    Left = 264
    Top = 264
    TabOrder = 5
    Width = 161
  end
  object btn5: TcxButton
    Left = 40
    Top = 32
    Width = 75
    Height = 25
    Caption = #33719#21462#23631#24149#25511#20214
    TabOrder = 6
    OnClick = btn5Click
  end
  object mTmrMonitor: TTimer
    Interval = 6000
    OnTimer = mTmrMonitorTimer
    Left = 56
    Top = 120
  end
end
