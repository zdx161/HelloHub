//static int test = 0; //local use    === OK
//extern static int test = 0; //local use    === fail
//int test = 0; //global use  === multiply define(compile failed)
extern int test; //declaration and define in one file === ok
//extern int test = 0; //declaration and define
void setvalue();
