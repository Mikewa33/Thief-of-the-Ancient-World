//Mike Walters
//James Wojewoda
#include "Input.h"

//////////////////////////////////////////////////////////////////////////
cInput::cInput (HWND hwnd)
: m_dinput (NULL), m_keyboard (NULL), m_mouse (NULL), m_error (false)
{
  //initialize DirectInput object
  if (!InitDirectInput ()) return;

  //initialize the keyboard
  if (!InitKeyboard (hwnd)) return;
  
  //initialize the mouse
  if (!InitMouse (hwnd)) return;
}

//////////////////////////////////////////////////////////////////////////
bool cInput::InitDirectInput ()
{
  HRESULT hr = DirectInput8Create (
    GetModuleHandle (NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, 
    (void**)&m_dinput, NULL);   

  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////
bool cInput::InitKeyboard (HWND hwnd)
{
  //initialize the keyboard
  HRESULT hr;

  hr = m_dinput->CreateDevice (GUID_SysKeyboard, &m_keyboard, NULL);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }

  //set the data format for keyboard input
  hr = m_keyboard->SetDataFormat (&c_dfDIKeyboard);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }

  //set the cooperative level
  hr = m_keyboard->SetCooperativeLevel (
    hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }

  //acquire the keyboard
  hr = m_keyboard->Acquire ();
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////
bool  cInput::InitMouse (HWND hwnd)
{
  //initialize the mouse
  HRESULT hr;
  hr = m_dinput->CreateDevice (GUID_SysMouse, &m_mouse, NULL);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }
  
  //set the data format for mouse input
  hr = m_mouse->SetDataFormat (&c_dfDIMouse);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }

  //set the cooperative level
  hr = m_mouse->SetCooperativeLevel (hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }

  //acquire the mouse 
  hr = m_mouse->Acquire ();
  if (hr != DI_OK)
  {
    m_error = true;
    return false;
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////
cInput::~cInput ()
{
  ReleaseKeyboard ();
  ReleaseMouse ();
}

//////////////////////////////////////////////////////////////////////////
void cInput::ReleaseKeyboard ()
{
  if (m_keyboard != NULL)
  {
    m_keyboard->Unacquire ();
    m_keyboard->Release ();
    m_keyboard = NULL;
  }
}

//////////////////////////////////////////////////////////////////////////
void cInput::ReleaseMouse ()
{
  if (m_mouse != NULL)
  {
    m_mouse->Unacquire ();
    m_mouse->Release ();
    m_mouse = NULL;
  }
}
  
//////////////////////////////////////////////////////////////////////////
long cInput::MouseX ()
{
  return m_mouseState.lX;
}

//////////////////////////////////////////////////////////////////////////
long cInput::MouseY ()
{
  return m_mouseState.lY;
}

//////////////////////////////////////////////////////////////////////////
long cInput::MouseZ ()
{
  return m_mouseState.lZ;
}

//////////////////////////////////////////////////////////////////////////
int cInput::MouseButton (int button)
{
  return (m_mouseState.rgbButtons[button] & 0x80);
}

//////////////////////////////////////////////////////////////////////////
void cInput::PollInput ()
{
  if (m_keyboard != NULL)
    m_keyboard->GetDeviceState (sizeof (m_keys), (LPVOID) &m_keys);

  if (m_mouse != NULL)
    m_mouse->GetDeviceState (sizeof (m_mouseState), (LPVOID) &m_mouseState);
}

//////////////////////////////////////////////////////////////////////////
int cInput::KeyDown (int key)
{
  return (m_keys[key] & 0x80);
}