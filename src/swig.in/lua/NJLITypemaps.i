%define SWIG_USERDATA_TYPEMAP(TYPE)
%typemap(in,checkfn="lua_isuserdata")     TYPE *INPUT($*1_ltype temp), TYPE &INPUT($*1_ltype temp)
%{ temp = *(($*1_ltype*)((swig_lua_userdata*)lua_touserdata(L,$input))->ptr);
    $1 = &temp; %}
%typemap(in, numinputs=0) TYPE **OUTPUT ($*1_ltype temp)
%{ $1 = &temp; %}
%typemap(argout) TYPE **OUTPUT
%{  SWIG_NewPointerObj(L,(void *) new $*1_ltype(*$1),$1_descriptor,0); SWIG_arg++;%}
%typemap(in) TYPE *INOUT = TYPE *INPUT;
%typemap(argout) TYPE *INOUT = TYPE **OUTPUT;
%typemap(in) TYPE &OUTPUT = TYPE **OUTPUT;
%typemap(argout) TYPE &OUTPUT = TYPE **OUTPUT;
%typemap(in) TYPE &INOUT = TYPE *INPUT;
%typemap(argout) TYPE &INOUT = TYPE **OUTPUT;
// const version (the $*1_ltype is the basic number without ptr or const's)
%typemap(in,checkfn="lua_isuserdata")     const TYPE *INPUT($*1_ltype temp)
%{ temp = *(($*1_ltype*)((swig_lua_userdata*)lua_touserdata(L,$input))->ptr);
    $1 = &temp; %}
%enddef








%define SWIG_USERDATA_ARRAY_TYPEMAP(TYPE, numarguments)
%typemap(in, numinputs=0) TYPE OUTPUT ($*1_ltype *temp)
%{ $1 = new $*1_ltype[numarguments](); %}
%typemap(argout) TYPE OUTPUT
%{ SWIG_NewPointerObj(L,(void *) $1,$1_descriptor,0); SWIG_arg++; %}
%enddef
