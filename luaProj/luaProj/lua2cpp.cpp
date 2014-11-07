//
//  lua2cpp.cpp
//  luaProj
//
//  Created by wyq on 14/11/6.
//  Copyright (c) 2014年 cloudayc. All rights reserved.
//

#include "lua2cpp.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif


int getSum(lua_State *L)
{
    int count = lua_gettop(L);
    printf("%d\n", count);
    
    int sum = 0;
    if (count == 0)
    {
        lua_pushstring(L, "no parameters");
        lua_error(L);
    }
    
    for (int i = 1; i <= count; ++i)
    {
        if (!lua_isnumber(L, i))
        {
            lua_pushstring(L, "not an number");
            lua_error(L);
        }
        
        sum += lua_tonumber(L, i);
    }
    
    lua_pushnumber(L, sum);
    return 1;
}

char *rootPath()
{
    return "/Users/yuqiang.wu/Desktop/lua/git_proj/luaProj/luaProj/luaexe";
}


void main_cpp()
{
    
    char path[100] = {0};
    sprintf(path, "%s/lua_cpp.lua", rootPath());
    
    lua_State *L = luaL_newstate();
    
    luaL_openlibs(L);
    
    lua_register(L, "getSum", getSum);
    
    luaL_dofile(L, path);
    
    lua_getglobal(L, "sum");
    
    printf("%td\n", lua_tointeger(L, -1));
    
    lua_pop(L, 1);
    
    lua_close(L);
    
}


