#include "global.h"
#include "clock.h"      // RTC code

#include "overworld.h"
/*
#include "gflib.h"
#include "bg_regs.h"
#include "cable_club.h"
#include "clock.h"      // RTC code
#include "credits.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_fadetransition.h"
#include "field_message_box.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "heal_location.h"
#include "help_system.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "m4a.h"
#include "map_name_popup.h"
#include "map_preview_screen.h"
#include "metatile_behavior.h"
#include "money.h"
#include "new_game.h"
#include "new_menu_helpers.h"
#include "overworld.h"
#include "play_time.h"
#include "quest_log.h"
#include "quest_log_objects.h"
#include "random.h"
#include "renewable_hidden_items.h"
#include "roamer.h"
#include "safari_zone.h"
#include "save_location.h"
#include "scanline_effect.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "start_menu.h"
#include "tileset_anims.h"
#include "trainer_pokemon_sprites.h"
#include "vs_seeker.h"
#include "wild_encounter.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"

extern void Overworld_ResetStateOnContinue(void);

// Map loaders
//08055864 g 000000bc LoadMapFromCameraTransition
void LoadMapFromCameraTransition(u8 mapGroup, u8 mapNum)    //repuntear esta función. eso o cambiar un bl a otro offset.
{
    int paletteIndex;

    SetWarpDestination(mapGroup, mapNum, -1, -1, -1);
    Overworld_TryMapConnectionMusicTransition();
    ApplyCurrentWarp();
    LoadCurrentMapData();
    LoadObjEventTemplatesFromHeader();
    TrySetMapSaveWarpStatus();
    ClearTempFieldEventData();
    ResetCyclingRoadChallengeData();
    RestartWildEncounterImmunitySteps();
    MapResetTrainerRematches(mapGroup, mapNum);     //0810c578 g 0000001c MapResetTrainerRematches
    DoTimeBasedEvents();                            // RTC code [mejor cambiar el bl a una función que lleve a esta y la siguiente.]
    SetSav1WeatherFromCurrMapHeader();              //0807b140 g 00000034 SetSav1WeatherFromCurrMapHeader
    ChooseAmbientCrySpecies();
    SetDefaultFlashLevel();
    Overworld_ClearSavedMusic();
    RunOnTransitionMapScript();
    TryRegenerateRenewableHiddenItems();
    InitMap();
    copy_map_tileset2_to_vram_2(gMapHeader.mapLayout);
    apply_map_tileset2_palette(gMapHeader.mapLayout);
    for (paletteIndex = 7; paletteIndex < 13; paletteIndex++)
        ApplyWeatherGammaShiftToPal(paletteIndex);
    InitSecondaryTilesetAnimation();
    UpdateLocationHistoryForRoamer();
    RoamerMove();
    sub_8110920();
    DoCurrentWeather();
    ResetFieldTasksArgs();
    RunOnResumeMapScript();
    if (GetLastUsedWarpMapSectionId() != gMapHeader.regionMapSectionId)
        ShowMapNamePopup(TRUE);
}
//08055920 l 00000088 mli0_load_map
static void mli0_load_map(bool32 a1)    //repuntear esta función.
{
    bool8 isOutdoors;

    LoadCurrentMapData();
    LoadObjEventTemplatesFromHeader();
    isOutdoors = IsMapTypeOutdoors(gMapHeader.mapType);

    TrySetMapSaveWarpStatus();
    ClearTempFieldEventData();
    ResetCyclingRoadChallengeData();
    RestartWildEncounterImmunitySteps();
    MapResetTrainerRematches(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);//0810c578 g 0000001c MapResetTrainerRematches
    DoTimeBasedEvents();            // RTC code
    SetSav1WeatherFromCurrMapHeader();  //0807b140 g 00000034 SetSav1WeatherFromCurrMapHeader
    ChooseAmbientCrySpecies();
    if (isOutdoors)
        FlagClear(FLAG_SYS_FLASH_ACTIVE);
    SetDefaultFlashLevel();
    Overworld_ClearSavedMusic();
    RunOnTransitionMapScript();
    TryRegenerateRenewableHiddenItems();
    UpdateLocationHistoryForRoamer();
    RoamerMoveToOtherLocationSet();
    sub_8110920();
    InitMap();
}

//080559a8 l 0000003c sub_80559A8
static void sub_80559A8(void)   //repuntear esta función. Repunteable.  
{
    bool8 isOutdoors;

    LoadCurrentMapData();
    LoadObjEventTemplatesFromHeader();
    isOutdoors = IsMapTypeOutdoors(gMapHeader.mapType);
    TrySetMapSaveWarpStatus();          //0810b7fc g 00000012 TrySetMapSaveWarpStatus
    DoTimeBasedEvents();                // RTC code     
    SetSav1WeatherFromCurrMapHeader();  //0807b140 g 00000034 SetSav1WeatherFromCurrMapHeader
    ChooseAmbientCrySpecies();
    SetDefaultFlashLevel();
    sub_8110920();
    sub_8111708();
    LoadSaveblockMapHeader();
    InitMap();
}

(...)

static void FieldCB_ShowMapNameOnContinue(void)
{
    if (SHOW_MAP_NAME_ENABLED)
        ShowMapNamePopup(FALSE);
    FieldCB_WarpExitFadeFromBlack();
}
static void FieldCB_ShowMapNameOnContinue(void);
//08056938 g 00000084 CB2_ContinueSavedGame
void CB2_ContinueSavedGame(void)    //repuntear esta función. eso o cambiar un bl a otro offset.
{
    FieldClearVBlankHBlankCallbacks();
    StopMapMusic();
    ResetSafariZoneFlag_();
    LoadSaveblockMapHeader();
    LoadSaveblockObjEventScripts();
    UnfreezeObjectEvents();             //08068a5c g 00000030 UnfreezeObjectEvents
    DoTimeBasedEvents();                // RTC code
    Overworld_ResetStateOnContinue();   //08054e40 l 00000028 Overworld_ResetStateOnContinue
    InitMapFromSavedGame();
    PlayTimeCounter_Start();
    ScriptContext1_Init();
    ScriptContext2_Disable();
    gFieldCallback2 = NULL;
    gUnknown_2031DE0 = TRUE;
    if (UseContinueGameWarp() == TRUE)
    {
        ClearContinueGameWarpStatus();
        SetWarpDestinationToContinueGameWarp();
        WarpIntoMap();
        SetMainCallback2(CB2_LoadMap);
    }
    else
    {
        gFieldCallback = FieldCB_ShowMapNameOnContinue;
        SetMainCallback1(CB1_Overworld);
        CB2_ReturnToField();
    }
}
*/
//--------------------------------------    hooks   ---------------------------------------//
extern void SetSav1WeatherFromCurrMapHeader(void);
extern void Overworld_ResetStateOnContinue(void);

void SetSav1WeatherFromCurrMapHeader_new(void)
{
    DoTimeBasedEvents();                            // RTC code [mejor cambiar el bl a una función que lleve a esta y la siguiente.]
    SetSav1WeatherFromCurrMapHeader();              //0807b140 g 00000034 SetSav1WeatherFromCurrMapHeader
}

void Overworld_ResetStateOnContinue_new(void)
{
    DoTimeBasedEvents();                // RTC code [mejor cambiar el bl a una función que lleve a esta y la siguiente.]
    Overworld_ResetStateOnContinue();   //08054e40 l 00000028 Overworld_ResetStateOnContinue
}

//--------------------------------------    hooks   ---------------------------------------//