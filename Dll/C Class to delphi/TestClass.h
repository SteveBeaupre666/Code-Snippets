#ifndef _CTEST_CLASS_H_
#define _CTEST_CLASS_H_
#ifdef __cplusplus

#include <Windows.h>

// Create an abstract class of the object to export
class ATestClass {
public:
	virtual void __cdecl TestNoArgs() = 0;
	virtual void __cdecl TestOneArgs(int x) = 0;
	virtual void __cdecl TestTwoArgs(int x, int y) = 0;

	virtual void __cdecl Free() = 0;
};

class CTestClass  : public ATestClass {
public:
	CTestClass();
	~CTestClass();
private:
	UINT BitsCount;
	UINT BufferSize;
public:
	void __cdecl TestNoArgs();
	void __cdecl TestOneArgs(int x);
	void __cdecl TestTwoArgs(int x, int y);
	
	void __cdecl Free(){if(this) delete this;}
};

ATestClass* WINAPI NewTestClass();

#endif
#endif //_CTEST_CLASS_H_/*