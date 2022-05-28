__aeabi_idiv        = 0x081e32ec|1;
__aeabi_idivmod     = 0x081e32ec|1;
__aeabi_uidiv       = 0x081e32ec|1;
__aeabi_uidivmod    = 0x081e32ec|1;
__divsi3            = 0x081e379c|1;
__udivsi3           = 0x081e3d90|1;
__umodsi3           = 0x081e3e08|1;
__modsi3            = 0x081E3878|1;
memcpy              = 0x081E55FC|1;
memset              = 0x081E565C|1;
strcmp              = 0x081e56b0|1;
strcpy              = 0x081e570c|1;
memmove             = 0x081e55FC|1;
CpuSet              = 0x081E32E8|1;

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
gSpecialVar_LastTalked      = 0x020370d2;
gSpecialVar_Facing          = 0x020370d4;
gSpecialVar_MonBoxId        = 0x020370d6;
gSpecialVar_MonBoxPos       = 0x020370d8;
gSpecialVar_TextColor       = 0x020370da;
gSpecialVar_PrevTextColor   = 0x020370dc;
gSpecialVar_0x8014          = 0x020370de;

gPaletteFade        = 0x02037ab8;
gPlayerPartyCount   = 0x02024029;
gDifferentSaveFile  = 0x02031db0;
gQuestLogState      = 0x0203adfa;
gPlayerParty        = 0x02024284;

/* IWRAM */
gTasks          = 0x03004fe0;
gMain           = 0x03003040;
gSaveBlock1Ptr  = 0x03004F58;
gSaveBlock2Ptr  = 0x03004F5C;
gSaveFileStatus = 0x030052F0;


GPIOPortDirection = 0x080000c6;

gLocalTime      = 0x030074a0;
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
sWindowTemplate = 0x0822fd84;/*idk*/

Task_SetWin0BldRegsNoSaveFileCheck  = 0x0800C670|1;/*static*/
Task_PrintMainMenuText              = 0x0800C70C|1;/*static*/
LoadUserFrameToBg                   = 0x0800CFB4|1;/*static*/
SetStdFrame0OnBg                    = 0x0800D004|1;/*static*/
PrintSaveErrorStatus                = 0x0800C5A0|1;/*static*/
RunTextPrinters                     = 0x08002D54|1;
IsTextPrinterActive                 = 0x08002DD0|1;
ClearWindowTilemap                  = 0x08004024|1;
MainMenu_EraseWindow                = 0x0800D158|1;/*static*/
IsMysteryGiftEnabled                = 0x0806E2F4|1;

/* main.c */
InitRFU             = 0x080f8a40|1;
GetGpuReg           = 0x08000ac0|1;
EnableInterrupts    = 0x08000b64|1;
SoftReset           = 0x081e3308|1;
ScanlineEffect_Stop = 0x08087e9c|1;
m4aSoundVSyncOff    = 0x081dd25c|1;

/* intro.c */
RunCopyrightScreen = 0x080ec938|1;/*static*/

/* title_screen.c */
Task_TitleScreenTimer       = 0x08078c24|1;/*static*/
Task_TitleScreenMain        = 0x08078c5c|1;/*static*/
SetTitleScreenScene         = 0x08078cc8|1;/*static*/
SetGpuRegsForTitleScreenRun = 0x080790d8|1;/*static*/
Task_TitleScreen_BlinkPressStart        = 0x08079454|1;/*static*/
CB2_FadeOutTransitionToSaveClearScreen  = 0x08079704|1;/*static*/
CB2_FadeOutTransitionToBerryFix         = 0x08079720|1;/*static*/
Task_FlameOrLeafSpawner     = 0x08079878|1;/*static*/
CreateSlashSprite           = 0x08079a78|1;/*static*/
ScheduleHideSlashSprite     = 0x08079ac0|1;/*static*/

    /* func */

/* scrcmd.c */
VarGet      = 0x0806e5a0|1;
ScriptReadHalfword = 0x080699BC|1;

/* event_data.c */
VarSet      = 0x0806e5bc|1;
FlagSet     = 0x0806e6b8|1;
FlagClear   = 0x0806e6e0|1;
FlagGet     = 0x0806e708|1;

/* new_game.c */
StringCopy            = 0x08008cf0|1;
ZeroPlayerPartyMons   = 0x0803d900|1;
ZeroEnemyPartyMons    = 0x0803d920|1;
ClearBattleTower      = 0x08054ac8|1;/*static*/
ClearSav1             = 0x0804c128|1;
ClearMailData         = 0x08097e70|1;
InitPlayerTrainerId   = 0x08054a1c|1;/*static*/
PlayTimeCounter_Reset = 0x08054908|1;
ClearPokedexFlags     = 0x08054aa0|1;/*static*/
InitEventData         = 0x0806e108|1;
ResetFameChecker      = 0x0812d480|1;
SetMoney              = 0x0809ff2c|1;
ResetGameStats        = 0x08054f5c|1;
ClearPlayerLinkBattleRecords = 0x080cdb44|1;
InitHeracrossSizeRecord      = 0x080a0ab8|1;
InitMagikarpSizeRecord       = 0x080a0b0c|1;
sub_806E190                  = 0x0806e1c8|1;
ResetPokemonStorageSystem    = 0x0808c9cc|1;
ClearRoamerData     = 0x08141e30|1;
ClearBag            = 0x0809a494|1;
NewGameInitPCItems  = 0x080eb964|1;
ClearEnigmaBerries  = 0x0809c94c|1;
InitEasyChatPhrases = 0x080bdfcc|1;
ResetTrainerFanClub = 0x08113234|1;
UnionRoomChat_InitializeRegisteredTexts = 0x0812999c|1;
ResetMiniGamesResults       = 0x08054c64|1;/*static*/
InitMEventData              = 0x08143f00|1;
SetAllRenewableItemFlags    = 0x0815d604|1;
WarpToPlayersRoom           = 0x08054aec|1;/*static*/
ScriptContext2_RunNewScript = 0x08069c0c|1;
ResetTrainerTowerResults    = 0x0815eb94|1;
GetGeneratedTrainerIdLower  = 0x08000588|1;
SetTrainerId                = 0x080549F0|1;
SetWarpDestination          = 0x08055480|1;
WarpIntoMap                 = 0x0805546C|1;
SetBerryPowder              = 0x0815ebdc|1;
ResetPokeJumpResults        = 0x0814b26c|1;

NewGameInitData = 0x08054b54|1;

/* intro.c */
SeedRngAndSetTrainerId  = 0x08000560|1;
SetSaveBlocksPointers   = 0x0804C14C|1;
ResetMenuAndMonGlobals  = 0x08054B1C|1;
Save_ResetSaveCounters  = 0x080D9A5C|1;
Save_LoadGameData = 0x080DA808|1;
Sav2_ClearSetDefault = 0x08054B0C|1;
SetPokemonCryStereo = 0x081de308|1;
InitHeap = 0x08002AEC|1;

/* title_screen.c */
UpdatePaletteFade   = 0x08070508|1;
SetMainCallback2    = 0x08000540|1;
CreateTask          = 0x08077454|1;
DestroyTask         = 0x08077540|1;
FuncIsActiveTask    = 0x08077688|1;
FindTaskIdByFunc    = 0x080776C0|1;
SetHelpContext      = 0x0812b36c|1;
HelpSystem_Enable   = 0x0812B600|1;
m4aMPlayAllStop     = 0x081dcd5c|1;
CB2_InitMainMenu    = 0x0800C26C|1;

/* field_specials.c */
ScriptContext2_Enable   = 0x08069a04|1;
CB2_ReturnToField       = 0x080568D0|1;

/* field_task.c */
ScriptContext2_IsEnabled = 0x08069A1C|1;
UpdateAmbientCry         = 0x0805616C|1;

/* overworld.c */
SetSav1WeatherFromCurrMapHeader = 0x0807B178|1;
Overworld_ResetStateOnContinue  = 0x08054f34|1;

/* pokemon.c */

GetMonData               = 0x0803fad4|1;
SetMonData               = 0x08040268|1;
ItemId_GetHoldEffect     = 0x0809aadc|1;
IsNationalPokedexEnabled = 0x0806E294|1;
Random                   = 0x08044ea0|1;
CheckPartyHasHadPokerus  = 0x080439C4|1;

/* const */
EventScript_ResetAllMapFlags = 0x081a603a;
/*gEvolutionTable = 0x08254F1C;*/
gBitTable = 0x08259c24;
gDummySpriteAffineAnimTable = 0x0822d468;
gMenuText_Confirm = 0x08411172;


/* others */
CB2_ReturnToFieldContinueScriptPlayMapMusic = 0x080569D4|1;
GetVarPointer = 0x0806E48C|1;
ConvertIntToHexStringN = 0x08008E84|1;
ClearStdWindowAndFrameToTransparent = 0x0810f688|1;
RemoveWindow = 0x08003DA8|1;
ScheduleBgCopyTilemapToVram = 0x080F6B20|1;
FreeSpritePaletteByTag = 0x0800899C|1;
AddTextPrinterParameterized = 0x08002bb4|1;
CopyWindowToVram = 0x08003e8c|1;
AddWindow = 0x08003c50|1;
DrawStdFrameWithCustomTileAndPalette = 0x0810f498|1;
LoadSpritePalette = 0x08008894|1;
CreateSpriteAtEnd = 0x08006f4c|1;
DestroySprite = 0x080071EC|1;
DrawDialogFrameWithCustomTileAndPalette = 0x0810EF74|1;
TrySavingData = 0x080DA670|1;
DoScheduledBgTilemapCopiesToVram = 0x080F6B34|1;
ResetOamRange = 0x08007254|1;
ScanlineEffect_Clear = 0x08087EDC|1;
ClearScheduledBgCopiesToVram = 0x080F6B0C|1;
LoadStdWindowFrameGfx = 0x080F7218|1;

/* wallclock.c */
LZ77UnCompVram = 0x081e32f0|1;
CreateSprite = 0x08006ef8|1;
LoadSpritePalettes = 0x080088E0|1;
LoadCompressedSpriteSheet = 0x0800eb3c|1;
LoadUserWindowBorderGfx = 0x0814fc30|1;
Menu_ProcessInputNoWrapClearOnChoose = 0x081102A4|1;
CreateYesNoMenu = 0x0811013c|1;
SetOamMatrix = 0x08007328|1;
Sin2 = 0x08044e44|1;
Cos2 = 0x08044e88|1;

/* evolution.c */
GetCurrentWeather = 0x0807AFD0|1;
MonKnowsMove      = 0x08125C3C|1;
gBaseStatsPtr     = 0x080001BC;/* puntero a gBaseStats*/
GetMonGender      = 0x0803F60C|1;


/*  DNS*/
    CB2_Overworld = 0x080565b4|1;


/*  EV-IV old*/

DestroySpriteAndFreeResources = 0x08007770|1;
stdpal_get = 0x081501f8|1;

PlaySE = 0x08072304|1;
GetNature = 0x08042D88|1;

GetSpeciesName = 0x08040EBC|1;
GetMonNickname = 0x08120440|1;

QuestLog_CutRecording = 0x08112554|1;


AllocZeroed = 0x08002b1c|1;
Free = 0x08002b30|1;

RunTasks = 0x080775b0|1;
AnimateSprites = 0x08006ac8|1;
BuildOamBuffer = 0x08006b14|1;


ResetSpriteData = 0x08006a7c|1;
ResetPaletteFade = 0x08070560|1;
FreeAllSpritePalettes = 0x0800885c|1;
ResetTasks = 0x080773f4|1;


SetVBlankCallback = 0x080006F0|1;
CopyToBgTilemapBuffer = 0x0800203c|1;
SetGpuReg = 0x08000a34|1;
CopyBgTilemapBufferToVram = 0x080020b8|1;
BeginNormalPaletteFade = 0x080705c0|1;


ResetBgsAndClearDma3BusyFlags = 0x08001614|1;
InitBgsFromTemplates = 0x08001654|1;
ChangeBgX = 0x08001b8c|1;
ChangeBgY = 0x08001d04|1;
InitWindows = 0x08003a90|1;
DeactivateAllTextPrinters = 0x08002b94|1;
SetBgTilemapBuffer = 0x08001f9c|1;
ShowBg = 0x080019b8|1;
FillBgTilemapBufferRect_Palette0 = 0x08002450|1;

ResetTempTileDataBuffers = 0x080f6b84|1;
DecompressAndCopyTileDataToVram = 0x080f6bf4|1;
FreeTempTileDataBuffersIfPossible = 0x080f6ba8|1;
LoadPalette = 0x08070424|1;

FillWindowPixelBuffer = 0x080043c8|1;
AddTextPrinterParameterized3 = 0x0812e698|1;
PutWindowTilemap = 0x08003f0c|1;

LoadOam = 0x0800728C|1;
ProcessSpriteCopyRequests = 0x0800757C|1;
TransferPlttBuffer = 0x080704AC|1;


FreeAllWindowBuffers = 0x08003e38|1;
CB2_ReturnToFieldFromDiploma = 0x080569f0|1;

ConvertIntToDecimalStringN = 0x08008de4|1;
StringAppend = 0x08008d10|1;

gStringVar1 = 0x02021cd0;
gStringVar2 = 0x02021cf0;
gStringVar3 = 0x02021d04;
gStringVar4 = 0x02021d18;

PlayCry7 = 0x08071F5C|1;
IsCryPlaying = 0x0807224C|1;
CreateMonSprite_FieldMove = 0x08083A0C|1;
FreeResourcesAndDestroySprite = 0x08083A94|1;
SpriteCallbackDummy = 0x08007578|1;
gSprites = 0x0202063c;
