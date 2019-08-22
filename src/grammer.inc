#define callp(x) call call_previous_page \ .dw x
#define calln(x) call call_next_page \ .dw x
_FindAlphaDn    = 4A47h
_FindAlphaUp    = 4A44h
_RclAns         = 4AD7h
_ChkFindSym     = 42F1h
_DispHL         = 4507h
_CreateTempStr  = 4324h
_SetParserHook  = 5026h
_CreateVar      = 4E70h
_CreateAppVar   = 4E6Ah
_CreatePict     = 4333h
_EnoughMem      = 42FDh
_InsertMem      = 42F7h
_Get_Tok_Strng  = 4594h
_DelMem         = 4357h
_JForceCmdNoChar= 4027h
_JError         = 44D7h
_DelVarArc      = 4FC6h
_CreateStrng    = 4327h
_CreateReal     = 430Fh
_SetXXXXOP2     = 4792h
_Arc_Unarc      = 4FD8h
_ConvKeyToTok   = 4A02h
_GetKeyRetOff   = 500Bh
_RunIndicOff    = 4570h
_DeleteTempPrograms = 5041h
_MemChk         = 42E5h
_clrTxtShd      = 454Ch
_saveCmdShadow  = 4573h
_PutS           = 450Ah
_OP5ToOP1       = 413Bh
_OP1ToOP5       = 4153h
appErr1         = 984Dh
appErr2         = 985Ah
cxErrorEP       = 8595h
curRow          = 844Bh
curCol          = 844Ch
kbdScanCode     = 843Fh
basic_prog      = 9652h
progStart       = 965Bh
parsePtr        = 965Dh
progEnd         = 965Fh
parserHookPtr   = 9BACh
OP5             = 84A4h
OP4             = 8499h
OP3             = 848Eh
OP2             = 8483h
intmask         = %00001011
invlogic        = 2
gflags          = 33
flags           = 89F0h
OP1             = 8478h
saveSScreen     = 86ECh
textShadow      = 8508h
plotSScreen     = 9340h
gbuf            = plotSScreen
progPtr         = 9830h
FPS             = 9824h
OPS             = 9828h
#define rMov9ToOP1    20h
#define rFindSym    10h
moduleExec      = 86ECh
tok_NegRelPtr   = $EE


;===============================================================
;RAM used by Grammer:
;     108 bytes for pointer vars stored in smallEditRAM
;      10 bytes for TempWords stored in OP6 and 1 byte of OP5
;       2 bytes for text position stored in OP6
;      10 bytes for Status stored in iMathPtr1
;===============================================================
smallEditRAM        = 90D3h  ;108 bytes
pvars               = smallEditRAM
iMathPtr1           = 84D3h  ;10 bytes
iMathPtr2           = 84D5h
iMathPtr3           = 84D7h
iMathPtr4           = 84D9h
iMathPtr5           = 84DBh
VATPtr     = iMathPtr1
VATPtr_next= iMathPtr2
OP6                 = 84AFh  ;11 bytes
cmdShadow           = 966Eh  ;128 bytes
;984Dh appErr1-26 bytes
;nameBuff-12 bytes
;userMenuSA-13 bytes

pTemp         = 982Eh ;bottom of named vars VAT
ThetaPrimeVar = 913Dh ;

TempWord1   = OP6-1       ;2       2
TempWord2   = TempWord1+2 ;2       4
TempWord3   = TempWord2+2 ;2       6
TempWord4   = TempWord3+2 ;2       8
TempWord5   = TempWord4+2 ;2      10
textRow     = TempWord5+2 ;1      11
textCol     = textRow+1   ;1      12

TextPauseTime=appErr2         ;1
GrayBufPtr  = TextPauseTime+1 ;2
Ans         = GrayBufPtr+2    ;2
StackCount  = Ans+2           ;2
StackLoc    = StackCount+2    ;2
OutputLogic = StackLoc+2      ;1
ErrorLoc    = OutputLogic+1   ;2
SPSave      = ErrorLoc+2      ;2

BufPtr              = 84E7h

parseError  = 84EBh           ;2
FontPointer = parseError+2    ;2
PBufPtr     = 9311h           ;2

IntLoc      = 8020h        ;2
IntCount    = IntLoc+2     ;2  Counts down from IntMax, at zero, executes code at IntLoc, and resets to IntMax
IntMax      = IntCount+2   ;2
PBufType    = IntMax+2     ;1
PBufRule    = PBufType+1   ;2
GrayMask    = PBufRule+2   ;2
GrayRotate  = GrayMask+2   ;1 upper 5 bits are for text modes
ForBackUp   = GrayRotate+1 ;2
gbuf_temp    = ForBackUp+2  ;2
seed1       = gbuf_temp+2   ;2
seed2       = seed1+2      ;2
main_menu_cursor    = seed2+2
main_menu_cursor_max= main_menu_cursor+1
main_menu_index     = main_menu_cursor_max+1
k_save      = main_menu_index+2
k_count     = k_save+1
k_delay     = k_count+1
qmarkVar    = k_delay+1
ddd         =qmarkVar+2   ;looks like it stores a ptr when executing the "call" command
module_count= ddd+2
module0     = module_count+1
module1     = module0+2
module2     = module1+2
module3     = module2+2
module4     = module3+2
vars        = module4+2           ;used while compiling
vars_count  = vars+2              ;
size_of_buffer = vars_count+2     ;
start_of_prog = size_of_buffer+2  ;
end_of_src  = start_of_prog+2     ;
data_top    = end_of_src+2        ;
end_of_buffer = data_top+2        ;
buffer_top  = end_of_buffer+2     ;
in_head     = buffer_top+2        ;
out_head    = in_head+2           ;

floatstack_ptr    = vars
floatstack_bottom = vars+2
floatstack_top    = vars+2+32     ;Give room for 8 floats. I am a generous god.
seedsingle0 = floatstack_top
seedsingle1 = seedsingle0+4

stack_base  = seedsingle1+4
stack_top   = stack_base+2
stack_ptr   = stack_top+2

input_base  = stack_ptr+2
input_head  = input_base+2
input_top   = input_head+2
input_size  = input_top+2


PBuf          = 9872h
ramCode       = 8100h
SetLinePix    = ramCode
interruptLoc  = 8A8Ah
tempSwapArea  = 82A5h
TSA           = 82A5h

RectData   = 8481h
;==============================
;Flags
;==============================
InternalFlag    = 33
SlowTextFlag    =   0
IntActiveFlag   =   1
FactorialFlag   =   2
errorChecking   =   3
grayFlag        =   4   ;this determines the checker pattern for the next gray object drawn
bit32           =   5   ;This determines if the output was 32-bit or not
Mod2nd          =   6
grayMode        =   7   ;This determines the checker pattern for grayscale mode

CursorFlags     = 12
CursorActive    =   3

UserFlags       = 34
InvertTextFlag  =   0
InvertLCDFlag   =   1
OnBlockFlag     =   2
baseInput       =   3
pxlBoundsRes    =   4
SignedText      =   5
;    =   6
;    =   7

ParticleFlag    = 35
InternalFlag2   = 35
Xis0            = 0
inputflag       = 0
Xis95           = 1
Yis0            = 2
Yis63           = 3
OffScrn         = 4
usingfloat      = 5


onFlags         = 9        ;on key flags
onInterrupt     =   4      ;1=on key interrupt request

curFlags        = 12       ;Cursor
fmtEdit         =   0      ;1=format number for editing
curAble         =   2      ;1=cursor flash is enabled
curOn           =   3      ;1=cursor is showing
curLock         =   4      ;1=cursor is locked off
cmdVirgin       =   5      ;1=nothing has been typed in cmd bfr
;----------------------------------------------------------------------
indicFlags        = 18         ;Indicator flags
indicRun          =   0        ;1=run indicator ON
shiftFlags        = 18         ;[2nd] and [ALPHA] flags
shift2nd          =   3        ;1=[2nd] has been pressed
shiftAlpha        =   4        ;1=[ALPHA] has been pressed
shiftLwrAlph      =   5        ;1=lower case, 0=upper case
shiftALock        =   6        ;1=alpha lock has been pressed
shiftKeepAlph     =   7        ;1=cannot cancel alpha shift
