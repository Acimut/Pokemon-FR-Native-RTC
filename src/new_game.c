#include "include/global.h"
#include "include/gflib.h"
#include "include/random.h"
#include "include/overworld.h"
#include "include/constants/maps.h"
#include "include/load_save.h"
#include "include/item_menu.h"
#include "include/tm_case.h"
#include "include/berry_pouch.h"
#include "include/quest_log.h"
#include "include/wild_encounter.h"
#include "include/event_data.h"
#include "include/mail_data.h"
#include "include/play_time.h"
#include "include/money.h"
#include "include/battle_records.h"
#include "include/pokemon_size_record.h"
#include "include/pokemon_storage_system.h"
#include "include/roamer.h"
#include "include/item.h"
#include "include/player_pc.h"
#include "include/berry.h"
#include "include/easy_chat.h"
#include "include/union_room_chat.h"
#include "include/mevent.h"
#include "include/renewable_hidden_items.h"
#include "include/trainer_tower.h"
#include "include/script.h"
#include "include/berry_powder.h"
#include "include/pokemon_jump.h"
#include "include/event_scripts.h"
#include "include/save.h"   // RTC code
#include "include/rtc.h"    // RTC code
#include "include/new_game.h"

//0= usa NewGameInitData(); por defecto.
//1= usa NewGameInitData_new();
#define NEW_GAME_VER    0

// this file's functions
//static void ResetMiniGamesResults(void);
extern void ResetMiniGamesResults(void);

// EWRAM vars
extern bool8 gDifferentSaveFile;


extern void InitPlayerTrainerId(void);
extern void ClearPokedexFlags(void);
extern void ClearBattleTower(void);
//extern void WarpToPlayersRoom(void);

#if NEW_GAME_VER

static void NewGameInitData_new(void);

//static void InitPlayerTrainerId(void)
//{
//    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
//    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
//}

//hacer hook a esta función xd
//static 
void SetDefaultOptions_new(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;//OPTIONS_TEXT_SPEED_MID;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SET;//OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_HELP;
}

#endif

//static void ClearPokedexFlags(void)
//{
//    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
//    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
//}

//static void ClearBattleTower(void)
//{
//    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
//}


void NewGame_RTC(void)
{
#ifndef RTC_DEBUG
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID) // RTC code hook
        RtcReset(); // RTC code
#endif
#if NEW_GAME_VER
    NewGameInitData_new();
    SetDefaultOptions_new();
#else
    NewGameInitData();
#endif
}

#if NEW_GAME_VER
static void WarpToPlayersRoom_new(void)
{
    SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}


//08054a60 g 00000110 NewGameInitData

static void NewGameInitData_new(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

//condición puesta en NewGame_hook_random
//#ifndef RTC_DEBUG
//    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID) // RTC code hook
//        RtcReset(); // RTC code
//#endif

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ClearBattleTower();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->field_AC = 1;
    gSaveBlock2Ptr->field_AD = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ResetFameChecker();
    SetMoney(&gSaveBlock1Ptr->money, 10000);
    ResetGameStats();
    ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    sub_806E190();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearEnigmaBerries();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags();
    WarpToPlayersRoom_new();
    //WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();
}
#endif
//static void ResetMiniGamesResults(void)
//{
//    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
//    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
//    ResetPokeJumpResults();
//    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
//}
