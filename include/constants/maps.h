#ifndef GUARD_CONSTANTS_MAPS_H
#define GUARD_CONSTANTS_MAPS_H

//#include "constants/map_groups.h"
//#include "constants/map_types.h"
#include "map_groups.h"
#include "map_types.h"

#define MAP_NONE (0x7F | (0x7F << 8))
#define MAP_UNDEFINED (0xFF | (0xFF << 8))

#define MAP_GROUP(map) (MAP_##map >> 8)
#define MAP_NUM(map) (MAP_##map & 0xFF)

#define MAP(map) MAP_GROUP(map), MAP_NUM(map)

#define EVO_MAP_GROUP(map) (map >> 8)
#define EVO_MAP_NUM(map) (map & 0xFF)

#endif  // GUARD_CONSTANTS_MAPS_H
