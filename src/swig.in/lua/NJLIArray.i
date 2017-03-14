/* -----------------------------------------------------------------------------
 * NJLIArray.i
 *
 * SWIG library file containing macros that can be used to manipulate simple
 * pointers as arrays.
 * ----------------------------------------------------------------------------- */


/* -----------------------------------------------------------------------------
 * %njli_array_functions(TYPE,NAME)
 *
 * Generates a class wrapper around a C array.  The class has the following
 * interface:
 *
 *          struct NAME {
 *              NAME(int nelements);
 *             ~NAME();
 *              TYPE getitem(int index);
 *              void setitem(int index, TYPE value);
 *              TYPE * cast();
 *              static NAME *frompointer(TYPE *t);
 *         }
 *
 * ----------------------------------------------------------------------------- */

%define %njli_array_functions(TYPE,NAME)
%{
    static TYPE **new_##NAME(int nelements) { %}
    
    %{
        return TYPE::createArray(nelements);
        %}
    
    %{}
    
    static void delete_##NAME(TYPE **ary) { %}
    
    %{
        TYPE::destroyArray(ary);
        %}
    
    %{}
    
    static TYPE *NAME##_getitem(TYPE **ary, int index) {
        DEBUG_ASSERT_WRITE(index > 0, "index must be greater than zero.");
        return ary[index-1];
    }
    static void NAME##_setitem(TYPE **ary, int index, TYPE *value) {
        DEBUG_ASSERT_WRITE(index > 0, "index must be greater than zero.");
        ary[index-1] = value;
    }
    %}

TYPE **new_##NAME(int nelements);
void delete_##NAME(TYPE **ary);
TYPE *NAME##_getitem(TYPE **ary, int index);
void NAME##_setitem(TYPE **ary, int index, TYPE *value);

%enddef

%rename(__getitem) *::getitem; // the v=X[i] (get operator)
%rename(__setitem) *::setitem; // the X[i]=v (set operator)
