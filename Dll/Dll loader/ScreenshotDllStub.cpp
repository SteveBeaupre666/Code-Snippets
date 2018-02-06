#include "ScreenshotDllStub.h"

CScreenshotDllStub::CScreenshotDllStub()
{
	hDll = NULL;
	Free();
}

CScreenshotDllStub::~CScreenshotDllStub()
{
	Free();
}

bool CScreenshotDllStub::IsLoaded()
{
	return hDll != NULL;
}

bool CScreenshotDllStub::Load(char *fname)
{
	if(IsLoaded())
		Free();

	hDll = LoadLibrary(fname);

	if(hDll){
		TakeScreenshot       = (PFNTAKESCREENSHOT)      GetProcAddress(hDll, "_TakeScreenshot");
		DecompressScreenshot = (PFNDECOMPRESSSCREENSHOT)GetProcAddress(hDll, "_DecompressScreenshot");
		ResetServer          = (PFNRESETSERVER)         GetProcAddress(hDll, "_ResetServer");
		ResetClient          = (PFNRESETCLIENT)         GetProcAddress(hDll, "_ResetClient");

		if(!TakeScreenshot)
			return false;
		if(!DecompressScreenshot)
			return false;
		if(!ResetServer)
			return false;
		if(!ResetClient)
			return false;

		return true;
	}

	return false;
}

void CScreenshotDllStub::Free()
{
	if(IsLoaded())
		FreeLibrary(hDll);

	hDll = NULL;

	TakeScreenshot       = NULL;
	DecompressScreenshot = NULL
	ResetServer          = NULL;
	ResetClient          = NULL;
}



