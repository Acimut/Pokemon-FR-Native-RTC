//overworld.c
//insert DoTimeBasedEvents
.org 0x080558a8 //LoadMapFromCameraTransition
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x08055962 //mli0_load_map
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x080559be //sub_80559A8
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x08056952 //CB2_ContinueSavedGame
    bl Overworld_ResetStateOnContinue_Hook
