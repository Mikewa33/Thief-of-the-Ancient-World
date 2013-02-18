//Mike Walters
//James Wojewoda
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <limits>

#include <string>
using std::string;

class cModel
{
private:
	std::vector <D3DMATERIAL9> Mtrls;
	
	IDirect3DTexture9** Textures;
	ID3DXBuffer* adjBuffer;
	ID3DXBuffer* mtrlBuffer;
	LPD3DXMATERIAL d3dxMaterials;
	DWORD	numMtrls;
	D3DXVECTOR3 translate;
	D3DXVECTOR3 rotate;
	D3DXVECTOR3 scale;
	D3DXMATRIX matWorld;
	

protected:
	ID3DXMesh* Mesh;

public:	
	cModel();
	~cModel();
	bool LoadModel(string, LPDIRECT3DDEVICE9,string);
	void DrawModel(LPDIRECT3DDEVICE9);
	bool FindFile(string*);
	bool DoesFileExist(const string& filename);
	void SplitPath(const string&, string*, string*);
	ID3DXMesh* getMesh()
	{return Mesh;};
	D3DXVECTOR3 getTranslate()
	{return translate;};
	

};
struct BoundingBox
	{
		BoundingBox(cModel*);
		bool isPointInside(D3DXVECTOR3& p);
		bool BoundingBoxSetUp();


		D3DXVECTOR3 min;
		D3DXVECTOR3 max;
		cModel* model;

	};