#include <windows.h>
#include <winuser.h>
#include <cstring>
#include <atlstr.h>

int main() {
	/*HWND hWnd = FindWindowA("命令提示符",NULL);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE or SWP_NOSIZE);
	SetParent(hWnd, GetDesktopWindow());
	while (true);*/
	HWND hWnd = ::FindWindow(CString("命令提示符"), NULL);
	if (NULL == hWnd)
	{
		return 0;
	}
	hWnd = ::FindWindowEx(hWnd, NULL, CString("SHELLDLL_DefView"), NULL);
	if (NULL == hWnd)
	{
		return 0;
	}
	hWnd = ::FindWindowEx(hWnd, NULL, CString("SysListView32"), NULL);
	if (NULL == hWnd)
	{
		return 0;
	}
	::SetParent(GetDesktopWindow(), hWnd);
	return 0;
}