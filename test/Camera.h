//Mike Walters
//James Wojewoda
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>
using std::string;


#ifndef __CAMERA_H__
#define __CAMERA_H__


class CXCamera
{
private:
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_LookAt;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	
	/*float m_fRotAboutUp;
    float m_fRotAboutRight;
    float m_fRotAboutFacing;*/

	D3DXMATRIX m_ViewTransform;

	//LPDIRECT3DDEVICE9 m_pDevice;
	//bool m_UpdateRequired;

	HRESULT UpdateCameraMatrices();
public:
	void LookAtPos(D3DXVECTOR3 *Position, D3DXVECTOR3 *LookAt, D3DXVECTOR3 *Up,float x,float y);
	//void SetPosition(FLOAT X, FLOAT Y, FLOAT Z);
	void		SetPosition(D3DXVECTOR3 a) { a = m_Position;}
	void SetLookAt(D3DXVECTOR3 a) {a = m_LookAt;}
	D3DXVECTOR3 GetPosition() {return m_Position;}
	D3DXVECTOR3 GetLookAt() {return m_LookAt;}
	D3DXVECTOR3 GetRight() {return m_Right;}
	D3DXVECTOR3 GetUp() {return m_Up;}
	D3DXMATRIX* GetViewMatrix() {return &m_ViewTransform;}
	CXCamera(int,int);
	HRESULT Update();

	//void RotateDown(float fAngle);
	void RotateRight(float fAngle,BoundingBox*[]);
	//void Roll(float fAngle);
	void MoveForward(float fDist,BoundingBox*[]);
	void MoveRight(float fDist,BoundingBox*[]);
	void MoveUp(float fDist);
	void MoveInDirection(float fDist, D3DXVECTOR3* Dir);
	void MoveLeft(float fDist,BoundingBox*[]);
	void MoveBack(float fDist,BoundingBox*[]);
	void MoveBackward(float fDist);
	
	
};

#endif