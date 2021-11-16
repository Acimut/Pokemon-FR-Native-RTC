//overworld.c
//insert DoTimeBasedEvents
.org 0x0805599C //FR 08055864 g 000000bc LoadMapFromCameraTransition
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x08055A56 //FR 08055920 l 00000088 mli0_load_map
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x08055AB2 //FR sub_80559A8
    bl SetSav1WeatherFromCurrMapHeader_Hook

.org 0x08056A46 //FR 08056938 g 00000084 CB2_ContinueSavedGame
    bl Overworld_ResetStateOnContinue_Hook
