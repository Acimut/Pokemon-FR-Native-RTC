#include "global.h"
#include "gflib.h"
#include "random.h"
#include "overworld.h"
#include "constants/maps.h"
#include "load_save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail_data.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mevent.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"
#include "save.h"   // RTC code
#include "rtc.h"    // RTC code
#include "new_game.h"


// this file's functions
//static void ResetMiniGamesResults(void);
extern void ResetMiniGamesResults(void);

// EWRAM vars
extern bool8 gDifferentSaveFile;


extern void InitPlayerTrainerId(void);
extern void ClearPokedexFlags(void);
extern void ClearBattleTower(void);
extern void WarpToPlayersRoom(void);


void NewGameInitData_new(void);

//static void InitPlayerTrainerId(void)
//{
//    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
//    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
//}


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



void NewGame_RTC(void)
{
    NewGameInitData_new();
    SetDefaultOptions_new();
}

void WarpToPlayersRoom_new(void)
{
    SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}


//08054a60 g 00000110 NewGameInitData

void NewGameInitData_new(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID) // RTC code hook
        RtcReset(); // RTC code

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
    //WarpToPlayersRoom_new();
    WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();
}
