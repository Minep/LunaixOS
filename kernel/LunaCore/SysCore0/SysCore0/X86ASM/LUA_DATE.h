#ifndef LUA_DATE_LIB
#define LUA_DATE_LIB

//---------CONSTANT---------
#define LUNA_DATE_YEAR 0x0
#define LUNA_DATE_MONTH 0x1
#define LUNA_DATE_DAY 0x2
#define LUNA_DATE_HOUR 0x3
#define LUNA_DATE_MINUTE 0x4
#define LUNA_DATE_SECOND 0x5

extern void LUA_GT_DATE();
extern char* LUNA_DATE_GET(unsigned int LUATYPE);
#endif