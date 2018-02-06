#include "Windows.h"
#include "Stdio.h"

#include "resource.h"

HWND hWnd = NULL;

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
    {
	// Initialise the dialog
	case WM_INITDIALOG:
		{

			return TRUE;
		}
		break;
		
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			// Button start server
			/*case IDC_BTN_:
				{
				}
				break;*/

			// Button close app
			case IDCANCEL:
			case IDCLOSE:
				{
					EndDialog(hWnd, IDOK);     
				}
				break;           
			}
		}

        break;

	default: 
		return FALSE;
    }

    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SERVERDLG), hWnd, DlgProc);

	return 0;
}