//%rename(operator_new) operator new;
//%rename(operator_delete) operator delete;
//%rename(operator_new_array) operator new[];
//%rename(operator_delete_array) operator delete[];

%rename(btScalarPtr) operator btScalar*;
%rename(btScalarConstPtr) operator const btScalar*;
%rename(operator_btVector3) operator btVector3;

%rename(getPlane_btVector3_btVector3_int) getPlane(btVector3 &,btVector3 &,int) const;

%rename(str) operator std::string;
