// vminstall.cpp : main source file for vminstall.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainDlg.h"
#include "install.h"

#include <BazisLib/bzshlp/Win32/wow64.h>

#if BAZISLIB_VERSION < 0x230
#error Please use BazisLib 2.3.0 or higher
#endif

CAppModule _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
#ifndef _WIN64
    if (BazisLib::WOW64APIProvider::sIsWow64Process())
    {
        MessageBoxW(NULL, L"WOW64 is not supported. Please use the 64-bit version of vminstall", L"Incorrect Architecture", MB_OK);
        return 1;
    }
#endif

	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;
	// BLOCK: Run application
	{
		CMainDlg dlgMain;
		nRet = (int)dlgMain.DoModal();
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
