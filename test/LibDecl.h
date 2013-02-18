//Mike Walters
//James Wojewoda
#ifndef __LIBDECL_H__
#define __LIBDECL_H__

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")

class cGame;
class cInput;
class CXCamera;
class cModel;
class cLighting;
struct BoundingBox;

#include "Lighting.h"
#include "Game.h"
#include "Input.h"
#include "Debug.h"
#include "Camera.h"
#include "ModelTest.h"

#endif