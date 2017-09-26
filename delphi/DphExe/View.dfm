object Form1: TForm1
  Left = 210
  Top = 193
  Width = 1144
  Height = 603
  Caption = 'Form5'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object cxGrid1: TcxGrid
    Left = 24
    Top = 16
    Width = 529
    Height = 457
    TabOrder = 0
    object cxGrid1DBTableView1: TcxGridDBTableView
      NavigatorButtons.ConfirmDelete = False
      DataController.DataSource = ds1
      DataController.Summary.DefaultGroupSummaryItems = <>
      DataController.Summary.FooterSummaryItems = <>
      DataController.Summary.SummaryGroups = <>
      object cxgrdbclmnGrid1DBTableView1SpeciesNo: TcxGridDBColumn
        DataBinding.FieldName = 'Species No'
      end
      object cxgrdbclmnGrid1DBTableView1Category: TcxGridDBColumn
        DataBinding.FieldName = 'Category'
      end
      object cxgrdbclmnGrid1DBTableView1Common_Name: TcxGridDBColumn
        DataBinding.FieldName = 'Common_Name'
      end
      object cxgrdbclmnGrid1DBTableView1SpeciesName: TcxGridDBColumn
        DataBinding.FieldName = 'Species Name'
      end
      object cxgrdbclmnGrid1DBTableView1Lengthcm: TcxGridDBColumn
        DataBinding.FieldName = 'Length (cm)'
      end
      object cxgrdbclmnGrid1DBTableView1Length_In: TcxGridDBColumn
        DataBinding.FieldName = 'Length_In'
      end
    end
    object cxGrid1Level1: TcxGridLevel
      GridView = cxGrid1DBTableView1
    end
  end
  object btn2: TcxButton
    Left = 24
    Top = 488
    Width = 75
    Height = 25
    Caption = 'btn2'
    TabOrder = 1
    OnClick = btn2Click
  end
  object cxgrpbx1: TcxGroupBox
    Left = 576
    Top = 56
    Caption = #23458#25143#39044#32422
    TabOrder = 2
    Height = 401
    Width = 553
    object cxgrpbx2: TcxGroupBox
      Left = 32
      Top = 40
      Caption = #23458#25143'/'#36710#36742#20449#24687
      TabOrder = 1
      Height = 225
      Width = 249
      object cxlbl1: TcxLabel
        Tag = 1
        Left = 56
        Top = 40
        Caption = #27979#35797#25968#25454
      end
      object cxlbl2: TcxLabel
        Left = 72
        Top = 104
        Caption = #27979#35797#25968#25454'2'
      end
    end
    object cxgrpbx3: TcxGroupBox
      Left = 304
      Top = 48
      Caption = #39044#32422#21333#22522#26412#20449#24687
      TabOrder = 0
      Height = 225
      Width = 233
      object txt1: TStaticText
        Left = 56
        Top = 56
        Width = 58
        Height = 17
        Caption = #27979#35797#25968#25454'1'
        TabOrder = 0
      end
    end
  end
  object btn1: TcxButton
    Left = 208
    Top = 496
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 3
  end
  object ds1: TDataSource
    DataSet = tbl1
    Left = 152
    Top = 256
  end
  object tbl1: TTable
    Active = True
    DatabaseName = 'DBDEMOS'
    TableName = 'biolife.db'
    Left = 152
    Top = 152
  end
end
