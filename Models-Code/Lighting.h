//Mike Walters
//James Wojewoda
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#include <string>
using std::string;

#ifndef __LIGHTING_H__
#define __LIGHTING_H__

class cLighting
{
protected:

	D3DLIGHT9 m_spot;
	
	
   

public:
	cLighting();
	~cLighting();


	void  InitSpotLight(const D3DXVECTOR3& position,const D3DXVECTOR3& direction,const D3DXCOLOR& color);
	//D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	
	
	void SetPosition(D3DXVECTOR3 newPos);
	
	void SetDirection(D3DXVECTOR3 newDir)
	{m_spot.Direction= newDir;}
	D3DXVECTOR3 GetPosition()
	{return m_spot.Position;}
	D3DXVECTOR3 GetDirection()
	{return m_spot.Direction;}
	


	static const D3DXCOLOR      BLACK;
	static const D3DXCOLOR        RED;
	static const D3DXCOLOR      GREEN;
	static const D3DXCOLOR       BLUE;
	static const D3DXCOLOR     YELLOW;
	static const D3DXCOLOR       CYAN;
	static const D3DXCOLOR    MAGENTA;
	static const D3DXCOLOR      WHITE;
};

#endif

