__aeabi_idiv        = 0x081e3b68|1;
__aeabi_idivmod     = 0x081e3b68|1;
__aeabi_uidiv       = 0x081e3b68|1;
__aeabi_uidivmod    = 0x081e3b68|1;
__divsi3            = 0x081e4018|1;
__udivsi3           = 0x081e460c|1;
__umodsi3           = 0x081e4684|1;
__modsi3            = 0x081e40f4|1;
memcpy              = 0x081e5e78|1;
memset              = 0x081e5ed8|1;
strcmp              = 0x081e5f2c|1;
strcpy              = 0x081e5f88|1;
memmove             = 0x081e8e60|1;
CpuSet              = 0x081e3b64|1;

/* EWRAM */
gHeap = 0x02000000;
gSpecialVar_0x8000 = 0x020370b8;
gSpecialVar_0x8001 = 0x020370ba;
gSpecialVar_0x8002 = 0x020370bc;
gSpecialVar_0x8003 = 0x020370be;
gSpecialVar_0x8004 = 0x020370c0;
gSpecialVar_0x8005 = 0x020370c2;
gSpecialVar_0x8006 = 0x020370c4;
gSpecialVar_0x8007 = 0x020370c6;
gSpecialVar_0x8008 = 0x020370c8;
gSpecialVar_0x8009 = 0x020370ca;
gSpecialVar_0x800A = 0x020370cc;
gSpecialVar_0x800B = 0x020370ce;
gSpecialVar_Result = 0x020370d0;
gSpecialVar_LastTalked = 0x020370d2;
gSpecialVar_Facing = 0x020370d4;
gSpecialVar_MonBoxId = 0x020370d6;
gSpecialVar_MonBoxPos = 0x020370d8;
gSpecialVar_TextColor = 0x020370da;
gSpecialVar_PrevTextColor = 0x020370dc;
gSpecialVar_0x8014 = 0x020370de;

gPaletteFade = 0x02037ab8;
gPlayerPartyCount = 0x02024029;
gDifferentSaveFile = 0x02031db0;
gQuestLogState = 0x0203adfa;
gPlayerParty = 0x02024284;

/* IWRAM */
gTasks = 0x03005090;
gMain = 0x030030f0;
gSaveBlock1Ptr = 0x03005008;
gSaveBlock2Ptr = 0x0300500c;
gSaveFileStatus = 0x030053a0;


GPIOPortDirection = 0x080000c6;

gLocalTime      = 0x030074d0;
gLocalTime_copy = 0x030074d8;
/* siirtc.c */
sDummy          = 0x030074e0;
sLocked         = 0x030074e2;
/* rtc.c */
sErrorStatus    = 0x030074e8;
sRtc            = 0x030074f0;
sProbeResult    = 0x030074fc;
sSavedIme       = 0x030074fe;
sDnsPaletteDmaBuffer    = 0x03007500;


/* main_menu.c */
sWindowTemplate = 0x08234618;

Task_SetWin0BldRegsNoSaveFileCheck = 0x0800c704|1;
Task_PrintMainMenuText = 0x0800c7a0|1;
LoadUserFrameToBg = 0x0800d044|1;
SetStdFrame0OnBg = 0x0800d094|1;
PrintSaveErrorStatus = 0x0800c634|1;
RunTextPrinters = 0x08002de8|1;
IsTextPrinterActive = 0x08002e64|1;
ClearWindowTilemap = 0x080040b8|1;
MainMenu_EraseWindow = 0x0800d1e8|1;
IsMysteryGiftEnabled = 0x0806e2bc|1;

/* main.c */
InitRFU = 0x080f86c4|1;
GetGpuReg = 0x08000ac4|1;
EnableInterrupts = 0x08000b68|1;
SoftReset = 0x081e3b84|1;
ScanlineEffect_Stop = 0x08087e64|1;
m4aSoundVSyncOff = 0x081dd728|1;

/* intro.c */
RunCopyrightScreen = 0x080ec62c|1;

/* title_screen.c */
Task_TitleScreenTimer = 0x08078bec|1;
Task_TitleScreenMain = 0x08078c24|1;
SetTitleScreenScene = 0x08078c90|1;
SetGpuRegsForTitleScreenRun = 0x080790a0|1;
Task_TitleScreen_BlinkPressStart = 0x0807941c|1;
CB2_FadeOutTransitionToSaveClearScreen = 0x080796cc|1;
CB2_FadeOutTransitionToBerryFix = 0x080796e8|1;
Task_FlameOrLeafSpawner = 0x08079840|1;
CreateSlashSprite = 0x08079a40|1;
ScheduleHideSlashSprite = 0x08079a88|1;

    /* func */

/* scrcmd.c */
VarGet = 0x0806e568|1;
ScriptReadHalfword = 0x080698f8|1;

/* event_data.c */
VarSet      = 0x0806e584|1;
FlagSet     = 0x0806e680|1;
FlagClear   = 0x0806e6a8|1;
FlagGet     = 0x0806e6d0|1;

/* new_game.c */
StringCopy            = 0x08008d84|1;
ZeroPlayerPartyMons   = 0x0803da14|1;
ZeroEnemyPartyMons    = 0x0803da34|1;
ClearBattleTower      = 0x080549d4|1;/*static*/
ClearSav1             = 0x0804c034|1;
ClearMailData         = 0x08097c84|1;
InitPlayerTrainerId   = 0x08054928|1;/*static*/
PlayTimeCounter_Reset = 0x08054814|1;
ClearPokedexFlags     = 0x080549ac|1;/*static*/
InitEventData         = 0x0806e0d0|1;
ResetFameChecker      = 0x0812d304|1;
SetMoney              = 0x0809fd70|1;
ResetGameStats        = 0x08054e68|1;
ClearPlayerLinkBattleRecords = 0x080cd8dc|1;
InitHeracrossSizeRecord      = 0x080a0904|1;
InitMagikarpSizeRecord       = 0x080a0958|1;
sub_806E190                  = 0x0806e190|1;
ResetPokemonStorageSystem    = 0x0808c7e0|1;
ClearRoamerData     = 0x08141c54|1;
ClearBag            = 0x0809a2dc|1;
NewGameInitPCItems  = 0x080eb658|1;
ClearEnigmaBerries  = 0x0809c794|1;
InitEasyChatPhrases = 0x080bdd34|1;
ResetTrainerFanClub = 0x08113044|1;
UnionRoomChat_InitializeRegisteredTexts = 0x08129820|1;
ResetMiniGamesResults       = 0x08054b70|1;/*static*/
InitMEventData              = 0x08143d24|1;
SetAllRenewableItemFlags    = 0x0815d838|1;
WarpToPlayersRoom           = 0x080549f8|1;/*static*/
ScriptContext2_RunNewScript = 0x08069b48|1;
ResetTrainerTowerResults    = 0x0815ee0c|1;
GetGeneratedTrainerIdLower  = 0x0800058c|1;
SetTrainerId                = 0x080548fc|1;
SetWarpDestination          = 0x0805538c|1;
WarpIntoMap                 = 0x08055378|1;
SetBerryPowder              = 0x0815ee54|1;
ResetPokeJumpResults        = 0x0814b47c|1;

NewGameInitData = 0x08054a60|1;

/* intro.c */
SeedRngAndSetTrainerId = 0x08000564|1;
SetSaveBlocksPointers = 0x0804c058|1;
ResetMenuAndMonGlobals = 0x08054a28|1;
Save_ResetSaveCounters = 0x080d9750|1;
Save_LoadGameData = 0x080da4fc|1;
Sav2_ClearSetDefault = 0x08054a18|1;
SetPokemonCryStereo = 0x081de7d4|1;
InitHeap = 0x08002b80|1;

/* title_screen.c */
UpdatePaletteFade = 0x080704d0|1;
SetMainCallback2 = 0x08000544|1;
CreateTask = 0x0807741c|1;
DestroyTask = 0x08077508|1;
FuncIsActiveTask = 0x08077650|1;
FindTaskIdByFunc = 0x08077688|1;
SetHelpContext = 0x0812b1f0|1;
HelpSystem_Enable = 0x0812b484|1;
m4aMPlayAllStop = 0x081dd228|1;
CB2_InitMainMenu = 0x0800c300|1;

/* field_specials.c */
ScriptContext2_Enable = 0x08069940|1;
CB2_ReturnToField = 0x080567dc|1;

/* field_task.c */
ScriptContext2_IsEnabled = 0x08069958|1;
UpdateAmbientCry = 0x08056078|1;

/* overworld.c */
SetSav1WeatherFromCurrMapHeader = 0x0807b140|1;
Overworld_ResetStateOnContinue = 0x08054e40|1;

/* pokemon.c */

GetMonData = 0x0803fbe8|1;
SetMonData = 0x0804037c|1;
ItemId_GetHoldEffect = 0x0809a924|1;
IsNationalPokedexEnabled = 0x0806e25c|1;
Random = 0x08044ec8|1;
CheckPartyHasHadPokerus = 0x08043ad8|1;

/* const */
EventScript_ResetAllMapFlags = 0x081a6481;
/*gEvolutionTable = 0x08259754;*/
gBitTable = 0x0825e45c;
gDummySpriteAffineAnimTable = 0x08231cfc;
gMenuText_Confirm = 0x084169d5;


/* others */
CB2_ReturnToFieldContinueScriptPlayMapMusic = 0x080568e0|1;
GetVarPointer = 0x0806e454|1;
ConvertIntToHexStringN = 0x08008f18|1;
ClearStdWindowAndFrameToTransparent = 0x0810f4d8|1;
RemoveWindow = 0x08003e3c|1;
ScheduleBgCopyTilemapToVram = 0x080f67a4|1;
FreeSpritePaletteByTag = 0x08008a30|1;
AddTextPrinterParameterized = 0x08002c48|1;
CopyWindowToVram = 0x08003f20|1;
AddWindow = 0x08003ce4|1;
DrawStdFrameWithCustomTileAndPalette = 0x0810f2e8|1;
LoadSpritePalette = 0x08008928|1;
CreateSpriteAtEnd = 0x08006fe0|1;
DestroySprite = 0x08007280|1;
DrawDialogFrameWithCustomTileAndPalette = 0x0810edc4|1;
TrySavingData = 0x080da364|1;
DoScheduledBgTilemapCopiesToVram = 0x080f67b8|1;
ResetOamRange = 0x080072e8|1;
ScanlineEffect_Clear = 0x08087ea4|1;
ClearScheduledBgCopiesToVram = 0x080f6790|1;
LoadStdWindowFrameGfx = 0x080f6e9c|1;

/* wallclock.c */
LZ77UnCompVram = 0x081e3b6c|1;
CreateSprite = 0x08006f8c|1;
LoadSpritePalettes = 0x08008974|1;
LoadCompressedSpriteSheet = 0x0800ebcc|1;
LoadUserWindowBorderGfx = 0x0814fe40|1;
Menu_ProcessInputNoWrapClearOnChoose = 0x081100c8|1;
CreateYesNoMenu = 0x0810ff60|1;
SetOamMatrix = 0x080073bc|1;
Sin2 = 0x08044e6c|1;
Cos2 = 0x08044eb0|1;

/* evolution.c */
GetCurrentWeather = 0x0807af98|1;
MonKnowsMove      = 0x08125ac0|1;
gBaseStatsPtr     = 0x080001BC;/* puntero a gBaseStats*/
GetMonGender      = 0x0803f720|1;


/*  DNS */
gMapHeader                  = 0x02036dfc;
CB2_Overworld               = 0x080565b4|1;
CB2_OverworldBasic          = 0x080565a8|1;
GetSpritePaletteTagByPaletteNum = 0x08008a20|1;
BattleMainCB2               = 0x08011100|1;
    /*battle_main.c*/
gBattleTypeFlags            = 0x02022b4c;
gBattleOutcome              = 0x02023e8a;
ResetPaletteFadeControl     = 0x08070a84|1;
CB2_QuitPokedudeBattle      = 0x080111bc|1;
    /*overworld.c*/
ScriptContext2_RunScript    = 0x08069aa8|1;
CameraUpdate                = 0x0805abb0|1;
sub_8115798                 = 0x08115798|1;
UpdateCameraPanning         = 0x0805ae28|1;
UpdateTilesetAnimations     = 0x0806ffbc|1;
    /*palette.c*/
UpdateBlendRegisters        = 0x0807141c|1;
gPlttBufferUnfaded          = 0x020371f8;
gPlttBufferFaded            = 0x020375f8;
sPlttBufferTransferPending  = 0x02037ac8;
    /*play_time.c*/
sPlayTimeCounterState       = 0x03000e7c;
PlayTimeCounter_SetToMax    = 0x080548d4|1;


/*  EV-IV old*/

DestroySpriteAndFreeResources = 0x08007804|1;
stdpal_get = 0x08150408|1;

PlaySE = 0x080722cc|1;
GetNature = 0x08042e9c|1;

GetSpeciesName = 0x08040fd0|1;
GetMonNickname = 0x081202e0|1;

QuestLog_CutRecording = 0x08112364|1;


AllocZeroed = 0x08002bb0|1;
Free = 0x08002bc4|1;

RunTasks = 0x08077578|1;
AnimateSprites = 0x08006b5c|1;
BuildOamBuffer = 0x08006ba8|1;


ResetSpriteData = 0x08006b10|1;
ResetPaletteFade = 0x08070528|1;
FreeAllSpritePalettes = 0x080088f0|1;
ResetTasks = 0x080773bc|1;


SetVBlankCallback = 0x080006f4|1;
CopyToBgTilemapBuffer = 0x08002040|1;
SetGpuReg = 0x08000a38|1;
CopyBgTilemapBufferToVram = 0x080020bc|1;
BeginNormalPaletteFade = 0x08070588|1;


ResetBgsAndClearDma3BusyFlags = 0x08001618|1;
InitBgsFromTemplates = 0x08001658|1;
ChangeBgX = 0x08001b90|1;
ChangeBgY = 0x08001d08|1;
InitWindows = 0x08003b24|1;
DeactivateAllTextPrinters = 0x08002c28|1;
SetBgTilemapBuffer = 0x08001fa0|1;
ShowBg = 0x080019bc|1;
FillBgTilemapBufferRect_Palette0 = 0x08002454|1;

ResetTempTileDataBuffers = 0x080f6808|1;
DecompressAndCopyTileDataToVram = 0x080f6878|1;
FreeTempTileDataBuffersIfPossible = 0x080f682c|1;
LoadPalette = 0x080703ec|1;

FillWindowPixelBuffer = 0x0800445c|1;
AddTextPrinterParameterized3 = 0x0812e51c|1;
PutWindowTilemap = 0x08003fa0|1;

LoadOam = 0x08007320|1;
ProcessSpriteCopyRequests = 0x08007610|1;
TransferPlttBuffer = 0x08070474|1;


FreeAllWindowBuffers = 0x08003ecc|1;
CB2_ReturnToFieldFromDiploma = 0x080568fc|1;

ConvertIntToDecimalStringN = 0x08008e78|1;
StringAppend = 0x08008da4|1;

gStringVar1 = 0x02021cd0;
gStringVar2 = 0x02021cf0;
gStringVar3 = 0x02021d04;
gStringVar4 = 0x02021d18;

PlayCry7 = 0x08071f24|1;
IsCryPlaying = 0x08072214|1;
CreateMonSprite_FieldMove = 0x080839d4|1;
FreeResourcesAndDestroySprite = 0x08083a5c|1;
SpriteCallbackDummy = 0x0800760c|1;
gSprites = 0x0202063c;
