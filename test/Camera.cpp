
//Mike Walters
//James Wojewoda
#include "LibDecl.h"

CXCamera::CXCamera(int Width,int Height)
{
	
	m_Position = D3DXVECTOR3(248.3480f,-1.4f,-49.9867f);
	m_LookAt = D3DXVECTOR3(-1.0f,0.0f,.0f);
	m_Right = D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_Up = D3DXVECTOR3(0.0f,1.0f,0.0f);

	D3DXMatrixIdentity(&m_ViewTransform);
	UpdateCameraMatrices();

	D3DXMATRIX p;
  D3DXMatrixPerspectiveFovLH (&p, D3DX_PI*0.5f, float((Width)/Height), 1.0f, 
	  1000.0f);
 
  g_game->GetGraphicsDevice()->SetTransform(D3DTS_PROJECTION, &p);

}
//////////////////////////////////////////////////////////////////////////

HRESULT CXCamera::UpdateCameraMatrices()
{
	

	D3DXVec3Normalize(&m_LookAt,&m_LookAt);
	D3DXVec3Cross(&m_Up,&m_LookAt, &m_Right);
    D3DXVec3Normalize(&m_Up,&m_Up);
	D3DXVec3Cross(&m_Right,&m_Up, &m_LookAt);
	D3DXVec3Normalize(&m_Right,&m_Right);
	
	float x = -D3DXVec3Dot(&m_Right,&m_Position);
	float y = -D3DXVec3Dot(&m_Up,&m_Position);
	float z = -D3DXVec3Dot(&m_LookAt,&m_Position);

	

	    m_ViewTransform (0,0) = m_Right.x;
		m_ViewTransform (0,1) = m_Up.x;
		m_ViewTransform (0,2) = m_LookAt.x;
		m_ViewTransform (0,3) = 0.0f;

		m_ViewTransform (1,0) = m_Right.y;
		m_ViewTransform (1,1) = m_Up.y;
		m_ViewTransform (1,2) = m_LookAt.y;
		m_ViewTransform (1,3) = 0.0f;

		m_ViewTransform (2,0) = m_Right.z;
		m_ViewTransform (2,1) = m_Up.z;
		m_ViewTransform (2,2) = m_LookAt.z;
		m_ViewTransform (2,3) = 0.0f;

		m_ViewTransform (3,0) = x;
		m_ViewTransform (3,1) = y;
        m_ViewTransform (3,2) = z;
		m_ViewTransform (3,3) = 1.0f;

		return g_game->GetGraphicsDevice ()->SetTransform (D3DTS_VIEW, &m_ViewTransform);
}
void CXCamera::LookAtPos(D3DXVECTOR3 *Position,D3DXVECTOR3*LookAt,D3DXVECTOR3* Up,float x,float y)
{

	D3DXMATRIX F;
	D3DXMATRIX T;

	D3DXMatrixRotationY (&T,y);
	D3DXMatrixRotationX (&F,x);
	D3DXVec3TransformCoord (&m_Right, &m_Right,&T);
	D3DXVec3TransformCoord (&m_LookAt, &m_LookAt,&T);
	D3DXVec3TransformCoord (&m_Up,&m_Up,&T);
	D3DXVec3TransformCoord (&m_Position, &m_Position,&F);
	D3DXVec3TransformCoord (&m_LookAt, &m_LookAt,&F);
	D3DXVec3TransformCoord (&m_Up,&m_Up,&F);
	UpdateCameraMatrices();
	
}


///////////////////////////////////////////////
/*void CXCamera::RotateDown(float fAngle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis (&T, &m_Right, fAngle);
	D3DXVec3TransformCoord (&m_Up, &m_Up,&T);
	D3DXVec3TransformCoord (&m_LookAt, &m_LookAt,&T);
	UpdateCameraMatrices();
}
*/
void CXCamera::RotateRight(float fAngle,BoundingBox*box[])
{
	
	
	/*bool check=false;
	for(int i=0;i<15;i++){
		if(box[i]!=NULL){
			if(box[i]->isPointInside(GetPosition()))
			{
				if(i==1||i==2){
					check=true;
				}
			}
		}
	}
	if(check==true){*/
	D3DXMATRIX T;
	D3DXMatrixRotationY (&T, fAngle);
	D3DXVec3TransformCoord (&m_Right, &m_Right,&T);
	D3DXVec3TransformCoord (&m_LookAt, &m_LookAt,&T);
	UpdateCameraMatrices();
	//}
	
}

void CXCamera::MoveForward(float fDist,BoundingBox*box[])
{
	
	D3DXVECTOR3 temp=m_Position + fDist * m_LookAt;
	bool check=false;
	for(int i=1;i<15;i++){
		if(box[i]!=NULL){
			if(box[i]->isPointInside(temp))
			{
				if(i!=3){
					check=true;
			}
			}
		}
	}
		if(check==false){
			m_Position=temp;
	UpdateCameraMatrices();
		}
}

void CXCamera::MoveRight(float fDist,BoundingBox*box[])
{
	D3DXVECTOR3 temp=m_Position + fDist* m_Right;
	
	bool check=false;
	for(int i=1;i<21;i++){
		if(box[i]!=NULL){
	if(box[i]->isPointInside(temp))
	{
		if(i!=3){
			fout<<"Boundbox number"<<i<<endl;
		check=true;
		}
	}
		
		}
	}
		if(check==false){
		m_Position=temp;
		UpdateCameraMatrices();
	
		}
}

void CXCamera::MoveUp(float fDist)
{
	m_Position += fDist * m_Up;
	UpdateCameraMatrices();
}

void CXCamera::MoveInDirection(float fDist, D3DXVECTOR3* Dir)
{
	D3DXVECTOR3 DirToMove(0,0,0);
	D3DXVec3Normalize(&DirToMove, Dir);
	m_Position += fDist*DirToMove;
	UpdateCameraMatrices();
}
void CXCamera::MoveLeft(float fDist,BoundingBox*box[])
{
	D3DXVECTOR3 temp=m_Position - fDist* m_Right;
	
	bool check=false;
	for(int i=1;i<15;i++){
		if(box[i]!=NULL){
	if(box[i]->isPointInside(temp))
	{
		if(i!=3){
		check=true;
		}
	}
		
		}
	}
		if(check==false){
		m_Position=temp;
		UpdateCameraMatrices();
	
		}
	

	
	
}
void CXCamera::MoveBack(float fDist,BoundingBox*box[])
{
	D3DXVECTOR3 temp=m_Position - fDist * m_Up;
	bool check=false;
	for(int i=0;i<15;i++){
		if(box[i]!=NULL){
	if(box[i]->isPointInside(temp))
	{
		if(i!=3){
		check=true;
		}
	}
		
		}
	}
		if(check==false){
		m_Position=temp;
		UpdateCameraMatrices();
	
		}
	
}
