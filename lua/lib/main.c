#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

int c_swap(lua_State *L)
{
    //check and fetch the arguments
    double arg1 = luaL_checknumber(L, 1);
    double arg2 = luaL_checknumber(L, 2);

    //push the results
    lua_pushnumber(L, arg2);
    lua_pushnumber(L, arg1);

    //return number of results
    return 2;
}

int my_sin(lua_State *L)
{
    //check and fetch the arguments
    double arg = luaL_checknumber(L, 1);

    //push the results
    lua_pushnumber(L, sin(arg));

    //return number of results
    return 1;
}

//library to be registered
struct luaL_Reg mylib[]  = {
    {"c_swap", c_swap},
    {"mysin", my_sin}, /* names can be different */
    {NULL, NULL}  /* sentinel */
};

//name of this function is not flexible
int luaopen_mylib(lua_State *L)
{
    luaL_newlib(L, mylib);
    return 1;
}
