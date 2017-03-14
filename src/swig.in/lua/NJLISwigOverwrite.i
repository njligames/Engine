%{
#undef SWIG_fail_arg
#define SWIG_fail_arg(func_name,argnum,type) \
{lua_Debug ar;\
lua_getstack(L, 1, &ar);\
lua_getinfo(L, "nSl", &ar);\
lua_pushfstring(L,"Error (%s:%d) in %s (arg %d), expected '%s' got '%s'",\
ar.source,ar.currentline,func_name,argnum,type,SWIG_Lua_typename(L,argnum));\
goto fail;}
    %}


//http://www.lua.org/manual/5.1/manual.html#lua_getinfo
%{
#undef SWIG_check_num_args
#define SWIG_check_num_args(func_name,a,b) \
/*if(LUA_WRAPPER_LOGGING){\
lua_Debug ar;\
lua_getstack(L, 1, &ar);\
lua_getinfo(L, "nSl", &ar);\
printf("(%s:%d) in %s",\
ar.short_src,ar.currentline,ar.name); \
}*/\
if (lua_gettop(L)<a || lua_gettop(L)>b) \
{SWIG_Lua_pushferrstring(L,"Error in %s expected %d..%d args, got %d",func_name,a,b,lua_gettop(L));\
goto fail;}
    %}
