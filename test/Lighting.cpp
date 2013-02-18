//Mike Walters
//James Wojewoda
#include "LibDecl.h"

const D3DXCOLOR cLighting::WHITE = D3DCOLOR_XRGB(255, 255, 255);
   const D3DXCOLOR cLighting::BLACK = D3DCOLOR_XRGB(  0,   0,   0) ;
   const D3DXCOLOR cLighting::RED = D3DCOLOR_XRGB(255,   0,   0) ;
   const D3DXCOLOR cLighting::GREEN = D3DCOLOR_XRGB(  0, 255,   0) ;
   const D3DXCOLOR cLighting::BLUE = D3DCOLOR_XRGB(  0,   0, 255) ;
   const D3DXCOLOR cLighting::YELLOW = D3DCOLOR_XRGB(255, 255,   0) ;
   const D3DXCOLOR cLighting::CYAN = D3DCOLOR_XRGB(  0, 255, 255);
   const D3DXCOLOR cLighting::MAGENTA = D3DCOLOR_XRGB(255,   0, 255) ; 
cLighting::cLighting()
{
	
	ZeroMemory(&m_spot, sizeof(D3DLIGHT9));
}


void cLighting::InitSpotLight(const D3DXVECTOR3& position,const D3DXVECTOR3& direction,const D3DXCOLOR& color)
{
	

	m_spot.Type      = D3DLIGHT_SPOT;
	m_spot.Ambient   = color;
	m_spot.Diffuse   = color;
	m_spot.Specular  = color;
	m_spot.Position  = position;
	m_spot.Direction = direction;
	m_spot.Range        = 100.0f;
	m_spot.Falloff      = 0.0f;
	m_spot.Attenuation0 = 0.0f;
	m_spot.Attenuation1 = 0.0f;
	m_spot.Attenuation2 = 0.0f;
	m_spot.Theta        = D3DXToRadian ( 25.0f);
	m_spot.Phi          = D3DXToRadian (1000.0f);

	
	g_game->GetGraphicsDevice()->SetLight(0, &m_spot);
	g_game->GetGraphicsDevice()->LightEnable(0,true);

 //return spot;
}
void cLighting::SetPosition(D3DXVECTOR3 newPos)
{
    m_spot.Position = newPos;
    g_game->GetGraphicsDevice()->SetLight(0, &m_spot);
	g_game->GetGraphicsDevice()->LightEnable(0,true);
}






