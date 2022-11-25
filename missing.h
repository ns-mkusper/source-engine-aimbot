#define __TRY try{
#define __CATCH }catch(...){OutputDebugStringA( "CRASHED\t\t" __FUNCTION__);}
#define __CATCH2(B) }catch(...){OutputDebugStringA(B);}
