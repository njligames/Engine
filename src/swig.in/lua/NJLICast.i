%define %_convert_dispatch(Type)
if (!dcast)
{
    Type *dobj = dynamic_cast<Type *>($1);
    if (dobj)
    {
        //%_convert_dispatch
        dcast = 1;
        SWIG_NewPointerObj(L, dobj, $descriptor(Type *), $owner);
        SWIG_arg++;
    }
}%enddef

%define %convert(Method,Types...)
%typemap(out) Method
{
    int dcast = 0;
    %formacro(%_convert_dispatch, Types)
    if (!dcast)
    {
        //%convert
        
        SWIG_NewPointerObj(L, $1, $descriptor, $owner);
        SWIG_arg++;
    }
}%enddef




//*********************
// Helper function for %downcast, to be called for each target type
%define %_downcast(Type)
if (dcast==0 && $1)
{
    %ptr(Type) out = %dynptrcast(Type,$1);
    if (out)
    {
        dcast=1;
        %set_output(SWIG_NewPointerObj(new %ptr(Type) out),
                    descriptor(%ptr(Type)*), SWIG_POINTER_OWN));
    }
}
%enddef

%define %downcast(typemaptarget, Types...)
%typemap(out) typemaptarget {
    int dcast = 0;
    %formacro(%_downcast, Types)
    if (!dcast)
        SWIG_exception_fail(SWIG_TypeError,"Can't convert type");
        }
%enddef