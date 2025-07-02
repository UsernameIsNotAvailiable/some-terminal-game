#ifndef _EXTEN_FUNC_DEF
#define _EXTEN_FUNC_DEF
#include <stdio.h>
#include <stdlib.h>
#include "../game/resources.h"
#include "../game/struct.h"
#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"
#include "../external/lua/lua.h"
#include "../external/lua/lualib.h"
#include "../external/lua/lauxlib.h"
#include "../external/lua/luaconf.h"

#pragma message("===> Building file "__FILE__)

//functions must have "lua" in the name to denote it's for
//the extension api


int luaApiTest(lua_State *state){
    _stack_;
    _check_bp;
    int num = lua_tonumber(state,1);
    printf("You said, %d!\n",num);
    return 0;
}
//lua: test(2) ==> "You said, 2!"

int doInitLua(void){
    _stack_;
    _check_bp;
    HANDLE_debugmsg("Executing test: .\\hi.lua\n");
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L,"test",luaApiTest);
    if(luaL_loadfile(L,"hi.lua") || lua_pcall(L,0,0,0)){
        printf("Lua error: %s\n",lua_tostring(L, -1));
    }
    printf("\n");
    return 0;
}


#endif