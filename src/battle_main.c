#include "global.h"
#include "text.h"
#include "palette.h"
#include "battle.h"
#include "task.h"
#include "event_data.h"
#include "dns.h"


//static 
extern void CB2_QuitPokedudeBattle(void);

void BattleMainCB2(void)
{
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
    RunTasks();
    
    DnsApplyFilters();//DNS

    if (JOY_HELD(B_BUTTON) && gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        gSpecialVar_Result = gBattleOutcome = B_OUTCOME_DREW;
        ResetPaletteFadeControl();
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        SetMainCallback2(CB2_QuitPokedudeBattle);
    }
}

