#ifndef MAIN_H
#define MAIN_H

//------------------------------------------------------------------------------
// Compile/Link flag
//------------------------------------------------------------------------------
//#define DEBUG_MSG_ASTAR
#define TURN_OFF_DAY_AND_NIGHT
//#define TURN_OFF_RESPAWN

//------------------------------------------------------------------------------
// Speed/Delay flag
//------------------------------------------------------------------------------
#ifdef VISUAL_STUDIO
#define BASE_INTERVAL 100
#else
#define BASE_INTERVAL 3
#endif
#define FPS (1000/BASE_INTERVAL)

//------------------------------------------------------------------------------
// Time related
//------------------------------------------------------------------------------
#define SPEED_CAR ((int)(FPS*0.15))
#define SPEED_AUTO_PROPS ((int)(FPS*0.15))
#define SPEED_MONSTER ((int)(FPS*1.0))
#define SPEED_BOSS ((int)(FPS*1.0))
#define SPEED_GHOST ((int)(FPS*1.0))
#define SPEED_MERCHANT ((int)(FPS*1.0))
#define SPEED_ARROW ((int)(FPS*0.15))

//------------------------------------------------------------------------------
// MonsterRespawnEvent related
//------------------------------------------------------------------------------
#define MON_RESPAWN_EVENT_BASE_DURATION_MIN FPS*1
#define MON_RESPAWN_EVENT_BASE_DURATION_MAX FPS*2
#define MON_RESPAWN_EVENT_BASE_DURATION_DIFF (MON_RESPAWN_EVENT_BASE_DURATION_MAX-MON_RESPAWN_EVENT_BASE_DURATION_MIN+1)

//------------------------------------------------------------------------------
// DayAndNightEvent related
//------------------------------------------------------------------------------
#define DAY true
#define NIGHT false

#define DAY_AND_NIGHT_EVENT_INTERVAL FPS*5
#define DAY_AND_NIGHT_EVENT_RANGE_NIGHT 2

#define NIGHT_SHAPE '$'

//------------------------------------------------------------------------------
// Viewport related
//------------------------------------------------------------------------------
#define VIEWPORT_HALF_HEIGHT 10
#define VIEWPORT_HALF_WIDTH 10
//==============================================================================
// Minimap related
//==============================================================================
#define MINIMAP_CELL_ROW_SIZE 10
#define MINIMAP_CELL_COL_SIZE 10



//------------------------------------------------------------------------------
// General
//------------------------------------------------------------------------------
#define ROW_SIZE 15
#define COL_SIZE 15
#define HUGE_ROW_SIZE (ROW_SIZE*5)
#define HUGE_COL_SIZE (COL_SIZE*5)
#define TILE_EMPTY '.'
#define MINIMAP_ROW_SIZE (HUGE_ROW_SIZE/MINIMAP_CELL_ROW_SIZE)
#define MINIMAP_COL_SIZE (HUGE_COL_SIZE/MINIMAP_CELL_COL_SIZE)

#define NUM_DIRS 4

#define DIR_NONE -1

#define DIR_N 0
#define DIR_E 1
#define DIR_S 2
#define DIR_W 3

#define KEY_N 'w'
#define KEY_E 'd'
#define KEY_S 's'
#define KEY_W 'a'

#define KEY_N_BOUNCE 'i'
#define KEY_E_BOUNCE 'l'
#define KEY_S_BOUNCE 'k'
#define KEY_W_BOUNCE 'j'

// fx related
#define SHOCKWAVE_DEFAULT_ID 0

#define DEFAULT_WAVE_RANGE 5
#define DEFAULTWAVE_FRAME_INTERVAL 1
#define DEFAULT_WAVE_SHAPE '*'

// for saving/loading
#define MAX_LEN_BUF 1000
#define MAX_LEN_FILENAME 256
  
//------------------------------------------------------------------------------
// MAX_NUM_~~~~
//------------------------------------------------------------------------------
#define MAX_NUM_EXITS 0
#define MAX_NUM_GHOSTS 0
#define MAX_NUM_MONSTERS 0
#define MAX_NUM_BOSS 10
#define MAX_NUM_MERCHANT 0
#define MAX_NUM_TREES 0
#define MAX_NUM_PORTALS 0
#define MAX_NUM_FOUNTAINS 0
#define MAX_NUM_BUSHES 0
#define MAX_NUM_DOORS 0
#define MAX_NUM_CARS 0
#define MAX_NUM_HOLY_STATUES 0
#define MAX_NUM_POTIONS 0
#define MAX_NUM_EXPOTION 0
#define MAX_NUM_BOUNCESHOE 0
#define MAX_NUM_KEY 0
#define MAX_NUM_SHOCKWAVES 100
#define MAX_NUM_ARMORS 0
#define MAX_NUM_WEAPONS 0
//#define MAX_NUM_BOWS 10
#define MAX_NUM_BOMBS 10
#define MAX_NUM_TORCH 0
//------------------------------------------------------------------------------
// class Hero related
//------------------------------------------------------------------------------
#define DEFAULT_HERO_SHAPE 'H'

#define DEFAULT_HERO_MAX_HP 600000
#define DEFAULT_HERO_HP 500000
#define DEFAULT_HERO_MAX_MP 100
#define DEFAULT_HERO_MP 100
#define DEFAULT_HERO_ATK 10
#define DEFAULT_HERO_DEF 10
#define DEFAULT_HERO_GOLD 100000
#define DEFAULT_HERO_EXP 0

#define UNIT_ID_HERO "Hero"
//------------------------------------------------------------------------------
// class Ghost related
//------------------------------------------------------------------------------
#define DEFAULT_GHOST_SHAPE '0'

#define DEFAULT_GHOST_MAX_HP 30
#define DEFAULT_GHOST_HP 30
#define DEFAULT_GHOST_MAX_MP 0
#define DEFAULT_GHOST_MP 0
#define DEFAULT_GHOST_ATK 5
#define DEFAULT_GHOST_DEF 5
#define DEFAULT_GHOST_GOLD 100
#define DEFAULT_GHOST_EXP 100

#define UNIT_ID_GHOST "Ghost"
//------------------------------------------------------------------------------
// class Monster related
//------------------------------------------------------------------------------
#define DEFAULT_MONSTER_SHAPE 'm'

#define DEFAULT_MONSTER_MAX_HP 30
#define DEFAULT_MONSTER_HP 30
#define DEFAULT_MONSTER_MAX_MP 0
#define DEFAULT_MONSTER_MP 0
#define DEFAULT_MONSTER_ATK 5
#define DEFAULT_MONSTER_DEF 5
#define DEFAULT_MONSTER_GOLD 100
#define DEFAULT_MONSTER_EXP 100

#define UNIT_ID_MONSTER "Monster"

//------------------------------------------------------------------------------
// class Boss related
//------------------------------------------------------------------------------
#define DEFAULT_BOSS_SHAPE '&'

#define DEFAULT_BOSS_MAX_HP 200
#define DEFAULT_BOSS_HP 200
#define DEFAULT_BOSS_MAX_MP 0
#define DEFAULT_BOSS_MP 0
#define DEFAULT_BOSS_ATK 30
#define DEFAULT_BOSS_DEF 30
#define DEFAULT_BOSS_GOLD 1000
#define DEFAULT_BOSS_EXP 1000

#define DEFAULT_BOSS_RANGE 15

#define UNIT_ID_BOSS "Boss"

#define BOSS_MAX_LEN_PATH 20

//------------------------------------------------------------------------------
// class Merchant related
//------------------------------------------------------------------------------
#define DEFAULT_MERCHANT_SHAPE 'G'

#define UNIT_ID_MERCHANT "Merchant"

//------------------------------------------------------------------------------
// class Tree related
//------------------------------------------------------------------------------
#define DEFAULT_TREE_SHAPE 'Y'

#define PROP_ID_TREE "Tree"

//------------------------------------------------------------------------------
// class Portal related
//------------------------------------------------------------------------------
#define DEFAULT_PORTAL_SHAPE 'O'

#define PROP_ID_PORTAL "Portal"

//------------------------------------------------------------------------------
// class Exit related
//------------------------------------------------------------------------------
#define DEFAULT_EXIT_SHAPE 'X'

#define PROP_ID_EXIT "Exit"

//------------------------------------------------------------------------------
// class Wall related
//------------------------------------------------------------------------------
#define DEFAULT_WALL_SHAPE_01 '+'
#define DEFAULT_WALL_SHAPE_02 '-'
#define DEFAULT_WALL_SHAPE_03 '|'

#define PROP_ID_WALL "Wall"

//------------------------------------------------------------------------------
// class Fountain related
//------------------------------------------------------------------------------
#define DEFAULT_FOUNTAIN_SHAPE 'V'
#define DEFAULT_FOUNTAIN_HP 10
#define DEFAULT_FOUNTAIN_MP 10

#define PROP_ID_FOUNTAIN "Fountain"

//------------------------------------------------------------------------------
// class Bush related
//------------------------------------------------------------------------------
#define DEFAULT_BUSH_SHAPE '@'

#define PROP_ID_BUSH "Bush"

//------------------------------------------------------------------------------
// class Door related
//------------------------------------------------------------------------------
#define DEFAULT_DOOR_SHAPE '='

#define PROP_ID_DOOR "Door"
//------------------------------------------------------------------------------
// class Car related
//------------------------------------------------------------------------------
#define DEFAULT_CAR_SHAPE 'C'
#define DEFAULT_CAR_DIR DIR_NONE

#define PROP_ID_CAR "Car"

//------------------------------------------------------------------------------
// class HolyStatue related
//------------------------------------------------------------------------------
#define DEFAULT_HOLY_STATUE_SHAPE 'I'
#define DEFAULT_HOLY_STATUE_HP 10
#define DEFAULT_HOLY_STATUE_MP 10

// HolyStatue related
#define SHOCKWAVE_HOLY_STATUE_ID 1

#define HOLY_STATUE_WAVE_RANGE 5
#define HOLY_STATUE_WAVE_FRAME_INTERVAL 1
#define HOLY_STATUE_WAVE_SHAPE 'o'
#define HOLY_STATUE_INTERVAL 10

#define PROP_ID_HOLY_STATUE "HolyStatue"

//------------------------------------------------------------------------------
// class Item related
//------------------------------------------------------------------------------
#define ITEM_SHAPE_NONE '\0'

//------------------------------------------------------------------------------
// class Potion related
//------------------------------------------------------------------------------
#define ITEM_ID_POTION "Potion"

#define DEFAULT_POTION_SHAPE 'b'
#define DEFAULT_POTION_NAME "Potion"
#define DEFAULT_POTION_PRICE 10

#define DEFAULT_POTION_HP 10
#define DEFAULT_POTION_MP 10

//------------------------------------------------------------------------------
// class Arrow related
//------------------------------------------------------------------------------
#define ITEM_ID_ARROW "Arrow"

#define DEFAULT_ARROW_SHAPE_N '^'
#define DEFAULT_ARROW_SHAPE_E '>'
#define DEFAULT_ARROW_SHAPE_S 'v'
#define DEFAULT_ARROW_SHAPE_W '<'

#define DEFAULT_ARROW_NAME "Arrow"
#define DEFAULT_ARROW_PRICE 1

#define DEFAULT_ARROW_ATK 10
#define DEFAULT_ARROW_SPEED 1

//------------------------------------------------------------------------------
// class Expotion related
//------------------------------------------------------------------------------
#define ITEM_ID_EXPOTION "Expotion"

#define DEFAULT_EXPOTION_SHAPE 'e'
#define DEFAULT_EXPOTION_NAME "Expotion"
#define DEFAULT_EXPOTION_PRICE 10

#define DEFAULT_EXPOTION_EXP 10

//------------------------------------------------------------------------------
// class Armor related
//------------------------------------------------------------------------------
#define ITEM_ID_ARMOR "Armor"

#define DEFAULT_ARMOR_SHAPE 'A'
#define DEFAULT_ARMOR_NAME "Armor"
#define DEFAULT_ARMOR_PRICE 0
#define DEFAULT_ARMOR_DURABILITY 0
#define DEFAULT_ARMOR_DEF 0
#define DEFAULT_ARMOR_BODYPARTID -1

// class Paperdoll/Item related
#define BODY_PART_ID_NONE 0
#define BODY_PART_ID_HEAD 1
#define BODY_PART_ID_CHEST 2
#define BODY_PART_ID_BACK 3
#define BODY_PART_ID_HANDS 4
#define BODY_PART_ID_LEGS 5
#define BODY_PART_ID_FEET 6

#define BODY_PART_ID_RIGHT_HAND 7
#define BODY_PART_ID_LEFT_HAND 8

#define ARMOR_SHAPE_HEAD 'A'
#define ARMOR_SHAPE_CHEST 'W'
#define ARMOR_SHAPE_BACK 'Q'
#define ARMOR_SHAPE_HANDS 'U'
#define ARMOR_SHAPE_LEGS 'L'
#define ARMOR_SHAPE_FEET 'F'

#define WEAPON_ONE_HAND 1
#define WEAPON_TWO_HAND 2

#define WEAPON_SHAPE_ONE_HAND '!'
#define WEAPON_SHAPE_TWO_HAND '?'
#define WEAPON_SHAPE_TWO_HANDED_BOW 'D'

//------------------------------------------------------------------------------
// class Weapon related
//------------------------------------------------------------------------------
#define ITEM_ID_WEAPON "Weapon"

#define DEFAULT_WEAPON_SHAPE '!'
#define DEFAULT_WEAPON_NAME "Weapon"
#define DEFAULT_WEAPON_PRICE 0
#define DEFAULT_WEAPON_DURABILITY 0
#define DEFAULT_WEAPON_ATK 0
#define DEFAULT_WEAPON_NUM_HANDS 1

//------------------------------------------------------------------------------
// class Bow related
//------------------------------------------------------------------------------
/*
#define ITEM_ID_BOW "Bow"

#define DEFAULT_BOW_SHAPE 'D'
#define DEFAULT_BOW_NAME "Bow"
#define DEFAULT_BOW_PRICE 0
#define DEFAULT_BOW_DURABILITY 0
#define DEFAULT_BOW_ATK 0
#define DEFAULT_BOW_NUM_HANDS 2
*/
//------------------------------------------------------------------------------
// class Bounceshoe related
//------------------------------------------------------------------------------
#define ITEM_ID_BOUNCESHOE "Bounceshoe"

#define DEFAULT_BOUNCESHOE_SHAPE 'S'
#define DEFAULT_BOUNCESHOE_NAME "Hermis\' Shoes"
#define DEFAULT_BOUNCESHOE_PRICE 100
#define DEFAULT_BOUNCESHOE_DURABILITY 100
#define DEFAULT_BOUNCESHOE_DEF 1
#define DEFAULT_BOUNCESHOE_BODYPARTID BODY_PART_ID_FEET

#define MAX_BOUNCESHOE_RANGE 3

//------------------------------------------------------------------------------
// class Key related
//------------------------------------------------------------------------------
#define ITEM_ID_KEY "Key"

#define DEFAULT_KEY_SHAPE 'K'
#define DEFAULT_KEY_NAME "Key"
#define DEFAULT_KEY_PRICE 100
#define DEFAULT_KEY_DURABILITY 100
#define DEFAULT_KEY_DEF 1
#define DEFAULT_KEY_BODYPARTID BODY_PART_ID_FEET


//------------------------------------------------------------------------------
// class Bomb related
//------------------------------------------------------------------------------
#define ITEM_ID_BOMB "Bomb"

#define DEFAULT_BOMB_SHAPE '*'
#define DEFAULT_BOMB_NAME "Bomb"
#define DEFAULT_BOMB_PRICE 100
#define DEFAULT_BOMB_DISPOSABLE true

#define DEFAULT_BOMB_RANGE 7
#define DEFAULT_BOMB_ATK 100

#define BOMB_WAVE_FRAME_INTERVAL 3
#define BOMB_WAVE_SHAPE '@'
//------------------------------------------------------------------------------
// class Torch related
//------------------------------------------------------------------------------
#define ITEM_ID_TORCH "Torch"

#define DEFAULT_TORCH_SHAPE 'i'
#define DEFAULT_TORCH_NAME "Torch"
#define DEFAULT_TORCH_PRICE 100
#define DEFAULT_TORCHDURABILITY 100
#define DEFAULT_TORCH_DEF 1
#define DEFAULT_TORCH_BODYPARTID BODY_PART_ID_FEET
//------------------------------------------------------------------------------
// class Inventory related
//------------------------------------------------------------------------------
#define INVENTORY_MAX_NUM_ITEM 5

#define TOMB_STONE_EMPTY "EMPTY"
#define TOMB_STONE_NON_EMPTY "NON-EMPTY"


//------------------------------------------------------------------------------
// class AntiCross(Shockwave) related
//------------------------------------------------------------------------------
#define SHOCKWAVE_ANTICROSS_ID 2

#define DEFAULT_ANTICROSS_RANGE 5
#define DEFAULT_ANTICROSS_FRAME_INTERVAL 1
#define DEFAULT_ANTICROSS_SHAPE '+'

//------------------------------------------------------------------------------
// class AStar related
//------------------------------------------------------------------------------
#define INF 2147483647

#endif
