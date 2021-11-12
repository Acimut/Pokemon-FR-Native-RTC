#define IS_POKEMON_C

#include "include/global.h"
#include "include/gflib.h"
#include "include/random.h"
#include "include/rtc.h"    // RTC code 
#include "include/text.h"
#include "include/data.h"
#include "include/battle.h"
#include "include/battle_anim.h"
#include "include/item.h"
#include "include/event_data.h"
#include "include/util.h"
#include "include/pokemon_storage_system.h"
#include "include/battle_gfx_sfx_util.h"
#include "include/battle_controllers.h"
#include "include/evolution_scene.h"
#include "include/battle_message.h"
#include "include/battle_util.h"
#include "include/link.h"
#include "include/m4a.h"
#include "include/pokedex.h"
//#include "include/strings.h"
#include "include/overworld.h"
#include "include/party_menu.h"
#include "include/field_specials.h"
#include "include/constants/items.h"
#include "include/constants/item_effects.h"
#include "include/constants/hoenn_cries.h"
#include "include/constants/pokemon.h"
#include "include/constants/abilities.h"
#include "include/constants/moves.h"
#include "include/constants/songs.h"
#include "include/constants/item_effects.h"
#include "include/constants/trainer_classes.h"
#include "include/constants/facility_trainer_classes.h"
#include "include/constants/hold_effects.h"
#include "include/constants/battle_move_effects.h"

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
    int i;
    u16 targetSpecies = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u16 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    u8 level;
    u16 friendship;
    u8 beauty = GetMonData(mon, MON_DATA_BEAUTY, NULL);
    u16 upperPersonality = personality >> 16;
    u8 holdEffect;

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

        for (i = 0; i < 5; i++)
        {
            switch (gEvolutionTable[species][i].method)
            {
            case EVO_FRIENDSHIP:
                if (friendship >= 220)
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                break;
            // FR/LG removed the time of day evolutions due to having no RTC.
            case EVO_FRIENDSHIP_DAY:
#ifndef RTC_DEBUG
                RtcCalcLocalTime(); // RTC code 
                if (gLocalTime.hours >= 12 && gLocalTime.hours < 24 && friendship >= 220)// RTC code 
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;      // RTC code 
#endif
                break;
            case EVO_FRIENDSHIP_NIGHT:
#ifndef RTC_DEBUG
                RtcCalcLocalTime();// RTC code 
                if (gLocalTime.hours >= 0 && gLocalTime.hours < 12 && friendship >= 220)// RTC code 
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;  // RTC code 
#endif
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
            }
        }
        break;
    case EVO_MODE_TRADE:
        for (i = 0; i < 5; i++)
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
        for (i = 0; i < 5; i++)
        {
            if (gEvolutionTable[species][i].method == EVO_ITEM
             && gEvolutionTable[species][i].param == evolutionItem)
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
