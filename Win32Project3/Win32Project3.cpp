#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(255, 0, 255, 0));
   SolidBrush brush(Color(255, 0, 0, 0));
   Region winRegion(Rect(0, 0, 500, 300));

   graphics.FillRegion(&brush, &winRegion);
   int i = 0;
   for (i; i < 501; i += 25) {
	   graphics.DrawLine(&pen, i, 0, i, 300);
   }
   for (i = 0; i < 301; i += 25) {
	   graphics.DrawLine(&pen, 0, i, 500, i);
   }
   
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hButton, hView;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH) COLOR_BACKGROUND;
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
	   TEXT("GettingStarted"),   // window class name
	   TEXT("Test Grid"),		// window caption
	   WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | WS_SYSMENU,     // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      520,						// initial x size
      400,						// initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
	  
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);
   
   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;
   
   switch(message)
   {	
   case WM_CREATE:
	   hButton = CreateWindow(TEXT("BUTTON"),
		   TEXT("Test"),
		   WS_VISIBLE | WS_CHILD,
		   220, 320, 60, 20,
		   hWnd, (HMENU) 1, NULL, NULL);
   case WM_COMMAND:
	   switch (LOWORD(wParam))
	   {
	   case 1:
		   hdc = GetDC(hWnd);

		   OnPaint(hdc);
		   ReleaseDC(hWnd, hdc);
		   break;
	   case 2:
		   break;
	   }
	   return 0;
   case WM_PAINT:

      hdc = BeginPaint(hWnd, &ps);
	 
      //(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc