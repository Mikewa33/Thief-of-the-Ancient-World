//Mike Walters
//James Wojewoda
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Mmsystem.h>

#include <string>
using std::string;

#ifndef __GAME_H__
#define __GAME_H__

class cGame
{
private:
  HWND m_hwnd;
  bool m_windowed;
  int m_width, m_height;

  LPDIRECT3D9 m_d3d;
  LPDIRECT3DDEVICE9 m_dev;
  LPD3DXFONT m_font;
  LPDIRECT3DSURFACE9 m_backBuffer;
  


  cInput* m_input;
  CXCamera* m_camera;
  cModel* m_model[100];
  BoundingBox* m_BoundingBox[100];
  cLighting* m_light;


  bool InitDirect3D ();
  bool InitDevice ();
  bool InitFont (const string&, int);
  bool InitBackBuffer ();
  bool InitInput ();
  bool InitCamera();
  bool InitModel();
  bool InitLighting();

  
  

public:
  cGame ();
  
  bool Init (HWND, int, int, bool);
  ~cGame ();
  bool Run ();
  
  //LPDIRECT3DTEXTURE9 LoadTexture (const string&, D3DCOLOR);

  LPDIRECT3DDEVICE9 GetGraphicsDevice()
  { return m_dev; }
  HWND GetHWnd ()
  {  return m_hwnd;  }
  int GetWidth ()
  {  return m_width;  }
  int GetHeight ()
  {  return m_height;  }
  LPD3DXFONT GetFont ()
  {  return m_font;  }

  cInput* GetInput ()
  {  return m_input;  }
  cModel* GetModel (int i)
  { return m_model[i];	}
};

extern cGame* g_game;

#endif // __GAME_H__