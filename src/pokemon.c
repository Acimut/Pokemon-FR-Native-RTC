#define IS_POKEMON_C

#include "global.h"
#include "gflib.h"
#include "random.h"
#include "rtc.h"    // RTC code 
#include "text.h"
#include "data.h"
#include "battle.h"
#include "battle_anim.h"
#include "item.h"
#include "event_data.h"
#include "util.h"
#include "pokemon_storage_system.h"
#include "battle_gfx_sfx_util.h"
#include "battle_controllers.h"
#include "evolution_scene.h"
#include "battle_message.h"
#include "battle_util.h"
#include "link.h"
#include "m4a.h"
#include "pokedex.h"
//#include "strings.h"
#include "overworld.h"
#include "party_menu.h"
#include "field_specials.h"
#include "constants/items.h"
#include "constants/item_effects.h"
#include "constants/hoenn_cries.h"
#include "constants/pokemon.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/item_effects.h"
#include "constants/trainer_classes.h"
#include "constants/facility_trainer_classes.h"
#include "constants/hold_effects.h"
#include "constants/battle_move_effects.h"

#include "constants/maps.h"
#include "constants/weather.h"
#include "field_weather.h"
#include "party_menu.h"
#include "dns.h"
#include "day_div.h"

// Extracts the upper 16 bits of a 32-bit number
#define HIHALF(n) (((n) & 0xFFFF0000) >> 16)

// Extracts the lower 16 bits of a 32-bit number
#define LOHALF(n) ((n) & 0xFFFF)
/*
//#define SPECIES_TO_HOENN(name)      [SPECIES_##name - 1] = HOENN_DEX_##name
//#define SPECIES_TO_NATIONAL(name)   [SPECIES_##name - 1] = NATIONAL_DEX_##name
//#define HOENN_TO_NATIONAL(name)     [HOENN_DEX_##name - 1] = NATIONAL_DEX_##name

static union PokemonSubstruct *GetSubstruct(struct BoxPokemon *boxMon, u32 personality, u8 substructType);
static u16 GetDeoxysStat(struct Pokemon *mon, s32 statId);
static bool8 IsShinyOtIdPersonality(u32 otId, u32 personality);
static u16 ModifyStatByNature(u8 nature, u16 n, u8 statIndex);
static u8 GetNatureFromPersonality(u32 personality);
static bool8 PartyMonHasStatus(struct Pokemon *mon, u32 unused, u32 healMask, u8 battleId);
static bool8 HealStatusConditions(struct Pokemon *mon, u32 unused, u32 healMask, u8 battleId);
static bool8 IsPokemonStorageFull(void);
static u8 SendMonToPC(struct Pokemon* mon);
static void EncryptBoxMon(struct BoxPokemon *boxMon);
static void DeleteFirstMoveAndGiveMoveToBoxMon(struct BoxPokemon *boxMon, u16 move);
static void GiveBoxMonInitialMoveset(struct BoxPokemon *boxMon);
static u16 GiveMoveToBoxMon(struct BoxPokemon *boxMon, u16 move);
static u8 GetLevelFromMonExp(struct Pokemon *mon);
static u16 CalculateBoxMonChecksum(struct BoxPokemon *boxMon);
*/

//08042ec4 g 000002f0 GetEvolutionTargetSpecies
u16 GetEvolutionTargetSpecies_new(struct Pokemon *mon, u8 type, u16 evolutionItem)  // RTC code /repuntear esta función.
{
    int i, j;
    u16 targetSpecies = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u16 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    u8 level;
    u16 friendship;
    u8 beauty = GetMonData(mon, MON_DATA_BEAUTY, NULL);
    u16 upperPersonality = personality >> 16;
    u8 holdEffect;
    u8 gender = GetMonGender(mon);
    u8 mapGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 mapNum = gSaveBlock1Ptr->location.mapNum;

    if (heldItem == ITEM_ENIGMA_BERRY)
        holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(heldItem);

    if (holdEffect == HOLD_EFFECT_PREVENT_EVOLVE && type != EVO_MODE_ITEM_CHECK)
        return 0;

    switch (type)
    {
    case EVO_MODE_NORMAL:
        level = GetMonData(mon, MON_DATA_LEVEL, NULL);
        friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);

        for (i = 0; i < EVOS_PER_MON; i++)
        {
            switch (gEvolutionTable[species][i].method)
            {
            case EVO_FRIENDSHIP:
                if (friendship >= 220)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            // FR/LG removed the time of day evolutions due to having no RTC.
            case EVO_FRIENDSHIP_DAY:
                RtcCalcLocalTime(); // RTC code 
                if (!IsLightActive() && friendship >= 220)// RTC code 
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;      // RTC code 
                break;
            case EVO_FRIENDSHIP_NIGHT:
                RtcCalcLocalTime();// RTC code 
                if (IsLightActive() && friendship >= 220)// RTC code 
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;  // RTC code 
                break;
            case EVO_LEVEL:
                if (gEvolutionTable[species][i].param <= level)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_ATK_GT_DEF:
                if (gEvolutionTable[species][i].param <= level)
                    if (GetMonData(mon, MON_DATA_ATK, NULL) > GetMonData(mon, MON_DATA_DEF, NULL))
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_ATK_EQ_DEF:
                if (gEvolutionTable[species][i].param <= level)
                    if (GetMonData(mon, MON_DATA_ATK, NULL) == GetMonData(mon, MON_DATA_DEF, NULL))
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_ATK_LT_DEF:
                if (gEvolutionTable[species][i].param <= level)
                    if (GetMonData(mon, MON_DATA_ATK, NULL) < GetMonData(mon, MON_DATA_DEF, NULL))
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_SILCOON:
                if (gEvolutionTable[species][i].param <= level && (upperPersonality % 10) <= 4)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_CASCOON:
                if (gEvolutionTable[species][i].param <= level && (upperPersonality % 10) > 4)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_NINJASK:
                if (gEvolutionTable[species][i].param <= level)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_BEAUTY:
                if (gEvolutionTable[species][i].param <= beauty)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            //---
            case EVO_LEVEL_MALE:
                if (gEvolutionTable[species][i].param <= level && gender == MON_MALE)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_FEMALE:
                if (gEvolutionTable[species][i].param <= level && gender == MON_FEMALE)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_MOVE:
                if (MonKnowsMove(&gPlayerParty[i], gEvolutionTable[species][i].param) == TRUE)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_MAPNUM:
                if (EVO_MAP_GROUP(gEvolutionTable[species][i].param) == mapGroup && EVO_MAP_NUM(gEvolutionTable[species][i].param) == mapNum)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_DAY:
                RtcCalcLocalTime();
                if (!IsLightActive() && gEvolutionTable[species][i].param <= level)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_NIGHT:
                RtcCalcLocalTime();
                if (IsLightActive() && gEvolutionTable[species][i].param <= level)
                {
                    heldItem = 0;
                    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                }
                break;
            case EVO_ITEM_DAY:
                RtcCalcLocalTime();
                if (!IsLightActive() && gEvolutionTable[species][i].param == heldItem)
                {
                    heldItem = 0;
                    SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                }
                break;
            case EVO_ITEM_NIGHT:
                RtcCalcLocalTime();
                if (IsLightActive() && gEvolutionTable[species][i].param == heldItem)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_LEVEL_MON:
                for (j = 0; j < PARTY_SIZE; j++)
                {
                    u16 checkSpecies = GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL);
                    if (checkSpecies == gEvolutionTable[species][i].param)
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                }
                break;
            case EVO_LEVEL_DARK:
                for (j = 0; j < PARTY_SIZE; j++)
                {
                    u16 checkType1 = gBaseStatsPtr[GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL)].type1;
                    u16 checkType2 = gBaseStatsPtr[GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL)].type2;
                    if ((checkType1 == TYPE_DARK || checkType2 == TYPE_DARK) && gEvolutionTable[species][i].param <= level  && i != j) // i != j because pancham can't evolve itself
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                }
                break;
            case EVO_LEVEL_RAIN:
                if ((GetCurrentWeather() == WEATHER_RAIN//WEATHER_RAIN_LIGHT
                    //|| GetCurrentWeather() == WEATHER_RAIN_MED
                    || GetCurrentWeather() == WEATHER_RAIN_THUNDERSTORM)//WEATHER_RAIN_HEAVY)
                    && gEvolutionTable[species][i].param <= level)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            }
        }
        break;
    case EVO_MODE_TRADE:
        for (i = 0; i < EVOS_PER_MON; i++)
        {
            switch (gEvolutionTable[species][i].method)
            {
            case EVO_TRADE:
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            case EVO_TRADE_ITEM:
                if (gEvolutionTable[species][i].param == heldItem)
                {
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                    if (IsNationalPokedexEnabled() || targetSpecies <= 151)
                    {
                        heldItem = 0;
                        SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
                        targetSpecies = gEvolutionTable[species][i].targetSpecies;
                    }
                }
                break;
            }
        }
        break;
    case EVO_MODE_ITEM_USE:
    case EVO_MODE_ITEM_CHECK:
        RtcCalcLocalTime();
        for (i = 0; i < EVOS_PER_MON; i++)
        {
            //if (gEvolutionTable[species][i].method == EVO_ITEM
            // && gEvolutionTable[species][i].param == evolutionItem)
            if ((gEvolutionTable[species][i].method == EVO_ITEM 
             &&  gEvolutionTable[species][i].param == evolutionItem)

             || (gEvolutionTable[species][i].method == EVO_ITEM_MALE 
             &&  gEvolutionTable[species][i].param == evolutionItem 
             &&  gender == MON_MALE)

             || (gEvolutionTable[species][i].method == EVO_ITEM_FEMALE 
             &&  gEvolutionTable[species][i].param == evolutionItem 
             &&  gender == MON_FEMALE))
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            }
        }
        break;
    }

    return targetSpecies;
}

//08043a68 g 00000006 RandomlyGivePartyPokerus
void RandomlyGivePartyPokerus(struct Pokemon *party)    // RTC code /hook | repoint
{
    u16 rnd = Random();
    if (rnd == 0x4000 || rnd == 0x8000 || rnd == 0xC000)
    {
        struct Pokemon *mon;

        do
        {
            do
            {
                rnd = Random() % PARTY_SIZE;
                mon = &party[rnd];
            }
            while (!GetMonData(mon, MON_DATA_SPECIES, 0));
        }
        while (GetMonData(mon, MON_DATA_IS_EGG, 0));

        if (!(CheckPartyHasHadPokerus(party, gBitTable[rnd])))
        {
            u8 rnd2;

            do
            {
                rnd2 = Random();
            }
            while ((rnd2 & 0x7) == 0);

            if (rnd2 & 0xF0)
                rnd2 &= 0x7;

            rnd2 |= (rnd2 << 4);
            rnd2 &= 0xF3;
            rnd2++;

            SetMonData(&party[rnd], MON_DATA_POKERUS, &rnd2);
        }
    }
}


// These two functions are stubbed from RS, but they're stubbed badly.
// See note on RandomlyGivePartyPokerus above.
//08043b38 l 00000006 UpdatePartyPokerusTime    -> 39 3b 04 08
void UpdatePartyPokerusTime(u16 days)   // RTC code /hook | repoint
{
    int i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, 0))
        {
            u8 pokerus = GetMonData(&gPlayerParty[i], MON_DATA_POKERUS, 0);
            if (pokerus & 0xF)
            {
                if ((pokerus & 0xF) < days || days > 4)
                    pokerus &= 0xF0;
                else
                    pokerus -= days;

                if (pokerus == 0)
                    pokerus = 0x10;

                SetMonData(&gPlayerParty[i], MON_DATA_POKERUS, &pokerus);
            }
        }
    }
}

//08043b40 g 00000006 PartySpreadPokerus
void PartySpreadPokerus(struct Pokemon *party)  // RTC code /hook | repoint
{
    if ((Random() % 3) == 0)
    {
        int i;
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES, 0))
            {
                u8 pokerus = GetMonData(&party[i], MON_DATA_POKERUS, 0);
                u8 curPokerus = pokerus;
                if (pokerus)
                {
                    if (pokerus & 0xF)
                    {
                        // Spread to adjacent party members.
                        if (i != 0 && !(GetMonData(&party[i - 1], MON_DATA_POKERUS, 0) & 0xF0))
                            SetMonData(&party[i - 1], MON_DATA_POKERUS, &curPokerus);
                        if (i != (PARTY_SIZE - 1) && !(GetMonData(&party[i + 1], MON_DATA_POKERUS, 0) & 0xF0))
                        {
                            SetMonData(&party[i + 1], MON_DATA_POKERUS, &curPokerus);
                            i++;
                        }
                    }
                }
            }
        }
    }
}
