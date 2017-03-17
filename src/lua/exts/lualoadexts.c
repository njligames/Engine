
#include "lualoadexts.h"
 
// luasocket
#include "luasocket.h"
#include "mime.h"
//#include "luasocketscripts.h"

static luaL_Reg luax_exts[] = {
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {NULL, NULL}
};

void luax_loadexts(lua_State *L)
{
    luaL_Reg* lib = luax_exts;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}
