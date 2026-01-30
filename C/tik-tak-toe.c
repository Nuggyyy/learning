#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

static bool quit = false;

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
  static WNDCLASS window_class = { 0 };
  static const wchar_t window_class_name[] = L"My Window Class";
  window_class.lpszClassName = (PCSTR)window_class_name;
  window_class.lpfnWndProc = WindowProcessMessage;
  window_class.hInstance = hInstance;

  RegisterClass(&window_class);

  HWND window_handle = CreateWindow((PCSTR)window_class_name, "Tik Tak Toe", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  if(window_handle == NULL) { return -1; }

  ShowWindow(window_handle, nCmdShow);
  
  while(!quit) {
    static MSG message = { 0 };
    while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
    
    // do game stuff here 

  }

  return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    case WM_QUIT:
    case WM_DESTROY: {
      quit = true;
    } break;

    default: {
      return DefWindowProc(window_handle, message, wParam, lParam);
    } break;
  }
  return 0;
}
