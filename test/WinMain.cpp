//Mike Walters
//James Wojewoda
#include <windows.h>
#include <string>
#include "LibDecl.h"
//#include <vector>

using std::string;
//using std:: vector;

HWND InitWindow (HINSTANCE, const string&, int, int, bool);
LRESULT CALLBACK WinProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR szArgs, int nShow)
{
	const string appName ("Thief of the Ancient World: Egypt");
	  const int width = 1024, height = 768;
  const bool windowed = true;
  HWND hWnd = InitWindow (hInst, appName, width, height, windowed);

  if (hWnd == NULL)
  {
    fout << "ERROR: Window creation failed" << endl;
    return 0;
  }

  ShowWindow (hWnd, nShow);
  UpdateWindow (hWnd);

  g_game = new cGame;
  if (g_game == NULL)
  {
    fout << "ERROR: Game object Creation failed" << endl;
    PostMessage (hWnd, WM_DESTROY, 0, 0);
  }
  else if (!g_game->Init (hWnd, width, height, windowed))
  {
    fout << "ERROR: Game object Initialization failed" << endl;
    PostMessage (hWnd, WM_DESTROY, 0, 0);
  }

  MSG msg;
  bool done = false;

  while (!done)
  {
    if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        done = true;
      TranslateMessage (&msg);
      DispatchMessage (&msg);
    }
    else
      g_game->Run ();
  }
  delete g_game;
  fout << "done" << endl;
  return msg.wParam;
}

///////////////////////////////////////////////////////////
HWND InitWindow (HINSTANCE hInst, const string& appName, 
                 int width, int height, bool windowed)
{
	
  WNDCLASSEX wc = {
    sizeof (WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WinProc, 0, 0,
    hInst, NULL, LoadCursor (NULL, IDC_ARROW),
    (HBRUSH) GetStockObject (WHITE_BRUSH), NULL, 
    appName.c_str (), NULL};

  if (!RegisterClassEx (&wc))
    return 0;

  int style = (windowed ? WS_OVERLAPPEDWINDOW : 
    WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);

  return CreateWindow (appName.c_str (), appName.c_str (), style,
    CW_USEDEFAULT, CW_USEDEFAULT, width, height,
    NULL, NULL, hInst, NULL);
}

///////////////////////////////////////////////////////////
LRESULT CALLBACK WinProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_DESTROY:
      PostQuitMessage (0);
      return 0;
  }

  return DefWindowProc (hwnd, msg, wParam, lParam);
}
