#ifndef _SCREENSHOT_DLL_STUB_H_
#define _SCREENSHOT_DLL_STUB_H_
#ifdef __cplusplus

#include <Windows.h>
#include <stdio.h>

typedef BYTE* (__stdcall * PFNTAKESCREENSHOT)(BOOL bShowCursor, CCompressionHeader *pHeader, int *pCompressedSize);
typedef BYTE* (__stdcall * PFNDECOMPRESSSCREENSHOT)(BYTE *pInput, int BufferSize, CCompressionHeader *pHeader);
typedef void  (__stdcall * PFNRESETSERVER)();
typedef void  (__stdcall * PFNRESETCLIENT)();


class CScreenshotDllStub {
public:
	CScreenshotDllStub();
	~CScreenshotDllStub();
private:
	HINSTANCE hDll;
public:
	PFNTAKESCREENSHOT       TakeScreenshot;
	PFNDECOMPRESSSCREENSHOT DecompressScreenshot;

	PFNRESETSERVER ResetServer;
	PFNRESETCLIENT ResetClient;
public:
	bool IsLoaded();
	bool Load(char *fname);
	bool Free();
};

#endif
#endif //_SCREENSHOT_DLL_STUB_H_
