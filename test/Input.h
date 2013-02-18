//Mike Walters
//James Wojewoda
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#ifndef __DXINPUT_H__
#define __DXINPUT_H__

class cInput
{
private:
  LPDIRECTINPUT8 m_dinput;

  //keyboard input
  LPDIRECTINPUTDEVICE8 m_keyboard;
  char m_keys [256];

  //mouse input
  LPDIRECTINPUTDEVICE8 m_mouse;
  DIMOUSESTATE m_mouseState;

  //error state
  bool m_error;

  bool InitDirectInput ();
  bool InitKeyboard (HWND);
  bool InitMouse (HWND);

  void ReleaseKeyboard ();
  void ReleaseMouse ();

public:
  cInput (HWND);
  ~cInput ();
  bool Error () { return m_error; }

  void PollInput ();

  int MouseButton (int);
  long MouseX ();
  long MouseY ();
  long MouseZ ();

  int KeyDown (int);
};

#endif // __DXINPUT_H__