�
 TFRMMAIN 0�  TPF0TfrmMainfrmMainLeft/Top	Caption   COM-COM траффикClientHeightxClientWidth�Color	clBtnFaceFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style OldCreateOrder	PositionpoScreenCenterOnClose	FormCloseOnResize
FormResizeOnShowFormShowPixelsPerInchx
TextHeight TPanel	panClientLeft Top Width�Height$AlignalClient
BevelOuterbvNoneTabOrder  TPageControlpgcMainLeft Top Width�Height$
ActivePagetbsSettingsAlignalClientTabOrder  	TTabSheettbsTerminalCaption   "5@<8=0;Font.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style 
ParentFont TMemomemTerminalLeft Top Width�HeightAlignalClientFont.CharsetRUSSIAN_CHARSET
Font.ColorclGrayFont.Height�	Font.NameLucida Console
Font.Style 
ParentFontReadOnly	
ScrollBars
ssVerticalTabOrder    	TTabSheettbsSettingsCaption	   0AB@>9:8
ImageIndex TLabellblDelayLeft
TopWidthbHeightCaption   Задержка, мс  TLabellblDelayDispersionLeft� TopWidthHeightCaption+Font.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsUnderline 
ParentFont  TLabel
lblPercentLeft:TopWidthHeightCaption%  TEditedtDelayLeft{TopWidth>HeightReadOnly	TabOrder Text0  TUpDownupdDelayLeft� TopWidthHeight	AssociateedtDelayMax'	IncrementTabOrder	Thousands  TEditedtDelayDispersionLeft� TopWidth'HeightReadOnly	TabOrderText0  TUpDownupdDelayDispersionLeftTopWidthHeight	AssociateedtDelayDispersionTabOrder	Thousands  TEditEdit1LeftTopaWidth>HeightReadOnly	TabOrderText0  TUpDownUpDown1LeftYTopaWidthHeight	AssociateEdit1Max�	Increment2TabOrder	Thousands
OnChangingUpDown1Changing     TPanel	panBottomLeft Top$Width�HeightTAlignalBottom
BevelOuterbvNoneTabOrder TLabellblComm1LeftTopWidth5HeightCaption   Порт А  TLabellblComm2LeftTop4Width3HeightCaption   Порт В  	TComboBoxcmbComm1LeftKTop
Width_HeightStylecsDropDownListDropDownCountTabOrder OnChangecmbComm1ChangeItems.StringsCOM1COM2COM3COM4COM5COM6COM7COM8   	TComboBoxcmbBaud1Left� Top
Width_HeightStylecsDropDownListDropDownCountTabOrderOnChangecmbBaud1ChangeItems.Strings1103006001200240048009600192003840057600115200   	TComboBoxcmbComm2LeftKTop0Width_HeightStylecsDropDownListDropDownCountTabOrderOnChangecmbComm2ChangeItems.StringsCOM1COM2COM3COM4COM5COM6COM7COM8   	TComboBoxcmbBaud2Left� Top0Width_HeightStylecsDropDownListDropDownCountTabOrderOnChangecmbBaud2ChangeItems.Strings1103006001200240048009600192003840057600115200   TPanel	panRigth2Left`Top Width� HeightTAlignalRight
BevelOuterbvNoneTabOrder TBitBtnbtbCrealInfoLeftTop0WidthnHeightCaption   G8AB8BLMarginTabOrderOnClickbtbCrealInfoClick  TBitBtnbtbSaveInfoLeftTop
WidthnHeightCaption   В файл  Margin	NumGlyphsTabOrder OnClickbtbSaveInfoClick    TApdComPortComm1	ComNumberBaud�%InSize  	TraceSize0u	TraceName	comm1.trcLogSizeP�  LogName	comm1.logOnTriggerAvailComm1TriggerAvailLeft`Top  TApdComPortComm2	ComNumberBaud�%InSize  	TraceSize0u	TraceName	comm2.trcLogSizeP�  LogName	comm2.logOnTriggerAvailComm2TriggerAvailLeft�Top  TSaveDialogsd_RichToFile
DefaultExtrtfFilter!   файл формата TXT|*.txtOptionsofOverwritePromptofHideReadOnly Title   Записать файлLeft�Top  TTimertmrDelayIntervaldOnTimertmrDelayTimerLeftTop  TTimertmrTimeout1EnabledInterval� OnTimertmrTimeout1TimerLeft\Top�   TTimertmrTimeout2EnabledInterval� OnTimertmrTimeout2TimerLeft�Top�    