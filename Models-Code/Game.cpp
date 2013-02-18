//Mike Walters
//James Wojewoda
#include "LibDecl.h"

#include <sstream>
using std::stringstream;

extern cGame* g_game = NULL;

float cameraMove = 0.2f;

/////////////////////////////////////////////////
cGame::cGame ()
: m_d3d (NULL), m_dev (NULL), m_backBuffer (NULL), 
  m_font (NULL), m_input (NULL), 
  m_hwnd (0), m_width (0), 
  m_height (0), m_windowed (false)
{for(int i=0;i<49;i++)
	m_BoundingBox[i]=NULL;}

/////////////////////////////////////////////////
bool cGame::Init (HWND hWnd, int w, int h, bool windowed)
{
  m_hwnd = hWnd;
  m_width = w;
  m_height = h;
  m_windowed = windowed;

 

  if (!InitDirect3D ()) return false;

  if (!InitDevice ()) return false;

  if (!InitFont ("Ariel", 24)) return false;

  if (!InitInput ()) return false;
  
  if (!InitBackBuffer ()) return false;

  if (!InitCamera()) return false;

  if (!InitModel()) return false;

  if (!InitLighting()) return false;

  D3DXMATRIX matWorld;   
  D3DXMatrixTranslation(&matWorld,0, -1, 1);
  m_dev->SetTransform(D3DTS_WORLD,&matWorld);
 m_dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
  


  fout <<"ending cGame::Init" << endl;
  return true;
}
///////////////////////////////////////////////////////////////
bool cGame::InitLighting()
{
	//m_dev->SetRenderState(D3DRS_LIGHTING, true);
	m_light = new cLighting;
	D3DXVECTOR3 Position=m_camera->GetPosition();
	D3DXVECTOR3 LookAt=m_camera->GetLookAt();
    D3DXCOLOR a = D3DCOLOR_XRGB(255, 255, 255);
	m_light->InitSpotLight(Position,LookAt,cLighting::WHITE);
  m_dev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
  m_dev->SetRenderState(D3DRS_LIGHTING,false);
  m_dev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50,50,50));
  //m_dev->SetRenderState(D3DRS_CULLMODE,false);
  m_dev->SetRenderState(D3DRS_NORMALIZENORMALS, false);

 // m_dev->SetRenderState(D3DRS_SPECULARENABLE, true);

return true;
}
//////////////////////////////////////////////////////////////
bool cGame::InitModel(){
	m_model[0]=new cModel();
	m_model[0]->LoadModel("Floor.x",m_dev,"Color3.jpg");
	m_BoundingBox[0]= new BoundingBox(m_model[0]);
	m_BoundingBox[0]->BoundingBoxSetUp();



	m_model[1]=new cModel();
	m_model[1]->LoadModel("Left1.x",m_dev,"color3.jpg");
	m_BoundingBox[1]= new BoundingBox(m_model[1]);
	m_BoundingBox[1]->BoundingBoxSetUp();


	m_model[2]=new cModel();
    m_model[2]->LoadModel("Right1.x", m_dev,"color3.jpg");
    m_BoundingBox[2]= new BoundingBox(m_model[2]);
	m_BoundingBox[2]->BoundingBoxSetUp();
	

	m_model[3]=new cModel();
	m_model[3]->LoadModel("Back1.x", m_dev,"Color3.jpg");
	m_BoundingBox[3]= new BoundingBox(m_model[3]);
	m_BoundingBox[3]->BoundingBoxSetUp();


	m_model[4]=new cModel();
	m_model[4]->LoadModel("UpperTomb.x",m_dev,"BoxColored.jpg");
	m_BoundingBox[4]= new BoundingBox(m_model[4]);
	m_BoundingBox[4]->BoundingBoxSetUp();
	


	m_model[5]=new cModel();
	m_model[5]->LoadModel("Left2.x",m_dev,"Color3.jpg");
	m_BoundingBox[5]= new BoundingBox(m_model[5]);
	m_BoundingBox[5]->BoundingBoxSetUp();
	
	

	m_model[6]=new cModel();
    m_model[6]->LoadModel("Right2.x", m_dev,"Color3.jpg");
    m_BoundingBox[6]= new BoundingBox(m_model[6]);
	m_BoundingBox[6]->BoundingBoxSetUp();
	



	m_model[7]=new cModel();
	m_model[7]->LoadModel("Back3.x", m_dev,"Color3.jpg");
	m_BoundingBox[7]= new BoundingBox(m_model[7]);
	m_BoundingBox[7]->BoundingBoxSetUp();


	m_model[8]=new cModel();
	m_model[8]->LoadModel("LowerTomb.x",m_dev,"LoweBoxColor.jpg");
	m_BoundingBox[8]= new BoundingBox(m_model[8]);
	m_BoundingBox[8]->BoundingBoxSetUp();
	


	m_model[9]=new cModel();
	m_model[9]->LoadModel("Left3.x",m_dev,"Color3.jpg");
	m_BoundingBox[9]= new BoundingBox(m_model[9]);
	m_BoundingBox[9]->BoundingBoxSetUp();

	

	m_model[10]=new cModel();
    m_model[10]->LoadModel("Right3.x", m_dev,"Color3.jpg");
    m_BoundingBox[10]= new BoundingBox(m_model[10]);
	m_BoundingBox[10]->BoundingBoxSetUp();
	



	m_model[11]=new cModel();
	m_model[11]->LoadModel("Back4.x", m_dev,"Color3.jpg");
	m_BoundingBox[11]= new BoundingBox(m_model[11]);
	m_BoundingBox[11]->BoundingBoxSetUp();
    

	m_model[12]=new cModel();
	m_model[12]->LoadModel("Pillars.x",m_dev,"Pillar.jpg");
	//m_BoundingBox[12]= new BoundingBox(m_model[12]);
	//m_BoundingBox[12]->BoundingBoxSetUp();



	m_model[13]=new cModel();
	m_model[13]->LoadModel("Left4.x",m_dev,"Color3.jpg");
	m_BoundingBox[13]= new BoundingBox(m_model[13]);
	m_BoundingBox[13]->BoundingBoxSetUp();
	

	m_model[14]=new cModel();
    m_model[14]->LoadModel("Right4.x", m_dev,"Color3.jpg");
    m_BoundingBox[14]= new BoundingBox(m_model[14]);
	m_BoundingBox[14]->BoundingBoxSetUp();

		m_model[15]=new cModel();
    m_model[15]->LoadModel("Wall4.x", m_dev,"Color3.jpg");
    m_BoundingBox[15]= new BoundingBox(m_model[15]);
	m_BoundingBox[15]->BoundingBoxSetUp();
	
	m_model[16]=new cModel();
    m_model[16]->LoadModel("Segment1.x", m_dev,"Color3.jpg");
    m_BoundingBox[16]= new BoundingBox(m_model[16]);
	m_BoundingBox[16]->BoundingBoxSetUp();
fout<<"gets here"<<endl;
	m_model[17]=new cModel();
	m_model[17]->LoadModel("Segment2.x",m_dev,"Color3.jpg");
	m_BoundingBox[17]=new BoundingBox(m_model[17]);
	m_BoundingBox[17]->BoundingBoxSetUp();

	m_model[18]=new cModel();
	m_model[18]->LoadModel("Segment3.x",m_dev,"Color3.jpg");
	m_BoundingBox[18]=new BoundingBox(m_model[18]);
	m_BoundingBox[18]->BoundingBoxSetUp();

	m_model[19]=new cModel();
	m_model[19]->LoadModel("Segment4.x",m_dev,"Color3.jpg");
	m_BoundingBox[19]=new BoundingBox(m_model[19]);
	m_BoundingBox[19]->BoundingBoxSetUp();

	m_model[20]=new cModel();
	m_model[20]->LoadModel("Segment5.x",m_dev,"Color3.jpg");
	m_BoundingBox[20]=new BoundingBox(m_model[20]);
	m_BoundingBox[20]->BoundingBoxSetUp();

	m_model[21]=new cModel();
	m_model[21]->LoadModel("Segment6.x",m_dev,"Color3.jpg");
	m_BoundingBox[21]=new BoundingBox(m_model[21]);
	m_BoundingBox[21]->BoundingBoxSetUp();

	m_model[22]=new cModel();
	m_model[22]->LoadModel("Roof.x",m_dev,"Roof.jpg");
	m_BoundingBox[22]=new BoundingBox(m_model[22]);
	m_BoundingBox[22]->BoundingBoxSetUp();

	m_model[23]=new cModel();
	m_model[23]->LoadModel("Left1Spike.x",m_dev,"stonespike.jpg");
	m_BoundingBox[23]=new BoundingBox(m_model[23]);
	m_BoundingBox[23]->BoundingBoxSetUp();
fout<<"1st"<<endl;
		m_model[24]=new cModel();
	m_model[24]->LoadModel("Left2Spike.x",m_dev,"stonespike.jpg");
	m_BoundingBox[24]=new BoundingBox(m_model[24]);
	m_BoundingBox[24]->BoundingBoxSetUp();

	m_model[25]=new cModel();
	m_model[25]->LoadModel("Left3Spike.x",m_dev,"stonespike.jpg");
	m_BoundingBox[25]=new BoundingBox(m_model[25]);
	m_BoundingBox[25]->BoundingBoxSetUp();

	m_model[26]=new cModel();
	m_model[26]->LoadModel("Right3Spike.x",m_dev,"stonespike.jpg");
	m_BoundingBox[26]=new BoundingBox(m_model[26]);
	m_BoundingBox[26]->BoundingBoxSetUp();

	
	m_model[27]=new cModel();
	m_model[27]->LoadModel("CoveringStoneLevel1.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[27]=new BoundingBox(m_model[27]);
	m_BoundingBox[27]->BoundingBoxSetUp();

	m_model[28]=new cModel();
	m_model[28]->LoadModel("Right1Spike.x",m_dev,"stonespike.jpg");
	m_BoundingBox[28]=new BoundingBox(m_model[28]);
	m_BoundingBox[28]->BoundingBoxSetUp();

		m_model[29]=new cModel();
	m_model[29]->LoadModel("RightWall2.x",m_dev,"stonewall.jpg");
	m_BoundingBox[29]=new BoundingBox(m_model[29]);
	m_BoundingBox[29]->BoundingBoxSetUp();

	m_model[30]=new cModel();
	m_model[30]->LoadModel("Right3Wall.x",m_dev,"stonewall.jpg");
	m_BoundingBox[30]=new BoundingBox(m_model[30]);
	m_BoundingBox[30]->BoundingBoxSetUp();

	m_model[31]=new cModel();
	m_model[31]->LoadModel("Right2Wall.x",m_dev,"stonewall.jpg");
	m_BoundingBox[31]=new BoundingBox(m_model[31]);
	m_BoundingBox[31]->BoundingBoxSetUp();

	m_model[32]=new cModel();
	m_model[32]->LoadModel("StoneLeft1.x",m_dev,"stonewall.jpg");
	m_BoundingBox[32]=new BoundingBox(m_model[32]);
	m_BoundingBox[32]->BoundingBoxSetUp();

	m_model[33]=new cModel();
	m_model[33]->LoadModel("Left3Wall.x",m_dev,"stonewall.jpg");
	m_BoundingBox[33]=new BoundingBox(m_model[33]);
	m_BoundingBox[33]->BoundingBoxSetUp();

	m_model[34]=new cModel();
	m_model[34]->LoadModel("Left2Wall.x",m_dev,"stonewall.jpg");
	m_BoundingBox[34]=new BoundingBox(m_model[34]);
	m_BoundingBox[34]->BoundingBoxSetUp();

	m_model[35]=new cModel();
	m_model[35]->LoadModel("Left1Wall.x",m_dev,"stonewall.jpg");
	m_BoundingBox[35]=new BoundingBox(m_model[35]);
	m_BoundingBox[35]->BoundingBoxSetUp();

	m_model[36]=new cModel();
	m_model[36]->LoadModel("Mummie.x",m_dev,"mummie.jpg");
	m_BoundingBox[36]=new BoundingBox(m_model[36]);
	m_BoundingBox[36]->BoundingBoxSetUp();

	m_model[37]=new cModel();
	m_model[37]->LoadModel("Anubis1.x",m_dev,"anubis.jpg");
	m_BoundingBox[37]=new BoundingBox(m_model[37]);
	m_BoundingBox[37]->BoundingBoxSetUp();

	m_model[38]=new cModel();
	m_model[38]->LoadModel("Anubis2.x",m_dev,"anubis.jpg");
	m_BoundingBox[38]=new BoundingBox(m_model[38]);
	m_BoundingBox[38]->BoundingBoxSetUp();

	m_model[39]=new cModel();
	m_model[39]->LoadModel("Anubis3.x",m_dev,"anubis.jpg");
	m_BoundingBox[39]=new BoundingBox(m_model[39]);
	m_BoundingBox[39]->BoundingBoxSetUp();

	m_model[40]=new cModel();
	m_model[40]->LoadModel("Anubis4.x",m_dev,"anubis.jpg");
	m_BoundingBox[40]=new BoundingBox(m_model[40]);
	m_BoundingBox[40]->BoundingBoxSetUp();

	m_model[41]=new cModel();
	m_model[41]->LoadModel("Anubis5.x",m_dev,"anubis.jpg");
	m_BoundingBox[41]=new BoundingBox(m_model[41]);
	m_BoundingBox[41]->BoundingBoxSetUp();

	m_model[42]=new cModel();
	m_model[42]->LoadModel("Spikes.x",m_dev,"stonespike.jpg");
	m_BoundingBox[42]=new BoundingBox(m_model[42]);
	m_BoundingBox[42]->BoundingBoxSetUp();


	m_model[43]=new cModel();
	m_model[43]->LoadModel("Spikes2.x",m_dev,"stonespike.jpg");
	m_BoundingBox[43]=new BoundingBox(m_model[43]);
	m_BoundingBox[43]->BoundingBoxSetUp();


	m_model[44]=new cModel();
	m_model[44]->LoadModel("Spikes3.x",m_dev,"stonespike.jpg");
	m_BoundingBox[44]=new BoundingBox(m_model[44]);
	m_BoundingBox[44]->BoundingBoxSetUp();


	m_model[45]=new cModel();
	m_model[45]->LoadModel("Spikes4.x",m_dev,"stonespike.jpg");
	m_BoundingBox[45]=new BoundingBox(m_model[45]);
	m_BoundingBox[45]->BoundingBoxSetUp();

	m_model[46]=new cModel();
	m_model[46]->LoadModel("Spikes5.x",m_dev,"stonespike.jpg");
	m_BoundingBox[46]=new BoundingBox(m_model[46]);
	m_BoundingBox[46]->BoundingBoxSetUp();

	m_model[47]=new cModel();
	m_model[47]->LoadModel("Spikes6.x",m_dev,"stonespike.jpg");
	m_BoundingBox[47]=new BoundingBox(m_model[47]);
	m_BoundingBox[47]->BoundingBoxSetUp();

	m_model[48]=new cModel();
	m_model[48]->LoadModel("AnubisStone1.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[48]=new BoundingBox(m_model[48]);
	m_BoundingBox[48]->BoundingBoxSetUp();

	m_model[49]=new cModel();
	m_model[49]->LoadModel("AnubisStone2.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[49]=new BoundingBox(m_model[49]);
	m_BoundingBox[49]->BoundingBoxSetUp();

	m_model[50]=new cModel();
	m_model[50]->LoadModel("AnubisStone3.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[50]=new BoundingBox(m_model[50]);
	m_BoundingBox[50]->BoundingBoxSetUp();

	m_model[51]=new cModel();
	m_model[51]->LoadModel("AnubisStone4.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[51]=new BoundingBox(m_model[51]);
	m_BoundingBox[51]->BoundingBoxSetUp();

	m_model[52]=new cModel();
	m_model[52]->LoadModel("AnubisStone5.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[52]=new BoundingBox(m_model[52]);
	m_BoundingBox[52]->BoundingBoxSetUp();

	m_model[53]=new cModel();
	m_model[53]->LoadModel("Gate.x",m_dev,"vasecolor1.jpg");
	m_BoundingBox[53]=new BoundingBox(m_model[53]);
	m_BoundingBox[53]->BoundingBoxSetUp();

	m_model[54] = new cModel();
	m_model[54]->LoadModel("DroppingStoneLevel1.x", m_dev, "vasecolor1.jpg");
	m_BoundingBox[54] = new BoundingBox(m_model[54]);
	m_BoundingBox[54]->BoundingBoxSetUp();

	m_model[55] = new cModel();
	m_model[55]->LoadModel("VaseLevel3.x", m_dev, "vasecolor1.jpg");
	m_BoundingBox[55] = new BoundingBox(m_model[55]);
	m_BoundingBox[55]->BoundingBoxSetUp();

	m_model[56] = new cModel();
	m_model[56]->LoadModel("VaseLevel3Number2.x", m_dev, "vasecolor1.jpg");
	m_BoundingBox[56] = new BoundingBox(m_model[56]);
	m_BoundingBox[56]->BoundingBoxSetUp();

	m_model[57] = new cModel();
	m_model[57]->LoadModel("WholeCover.x", m_dev, "vasecolor1.jpg");
	m_BoundingBox[57] = new BoundingBox(m_model[57]);
	m_BoundingBox[57]->BoundingBoxSetUp();






	//for(int g=0;g<21;g++){
	//	fout<<g<<":"<<"min:"<<*m_BoundingBox[g]->min<<"          max:  "<<*m_BoundingBox[g]->max<<"             "<<endl;
	//}
	
	if(m_model[0]==NULL)
	{
		fout<<"Error InitModel"<<endl;
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////
bool cGame::InitCamera(){
	m_camera=new CXCamera(m_width,m_height);
	if(m_camera==NULL){
		fout<<"Error in Init Camera Not Loading"<<endl;
		return false;
	}

	//m_camera->SetPosition(27.56f,53.0f,6.60f);
	return true;
}/**/
////////////////////////////////////////////////////////////////////
bool cGame::InitDirect3D ()
{
  m_d3d = Direct3DCreate9 (D3D_SDK_VERSION);
  if (m_d3d == NULL)
  {
    fout << "ERROR: Direct3D Initialization failed!" << endl;
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////
bool cGame::InitDevice ()
{
  D3DPRESENT_PARAMETERS pp;
  ZeroMemory (&pp, sizeof (pp));
  pp.Windowed = m_windowed;
  pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  pp.EnableAutoDepthStencil = true;
    pp.AutoDepthStencilFormat = D3DFMT_D16;
  if (m_windowed == true)
    pp.BackBufferFormat = D3DFMT_UNKNOWN;
  else
  {
    pp.BackBufferFormat = D3DFMT_A8R8G8B8;
    pp.BackBufferCount = 1;
    pp.BackBufferWidth = m_width;
    pp.BackBufferHeight = m_height;
    pp.hDeviceWindow = m_hwnd;
	
  }

  HRESULT hr = m_d3d->CreateDevice (
    D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd, 
    D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &m_dev);

  if (hr != D3D_OK)
  {
    fout << "ERROR: Graphics Initialization failed!" << endl;
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////
bool cGame::InitFont (const string& face, int size)
{
  D3DXFONT_DESC desc;
  ZeroMemory (&desc, sizeof (desc));
  desc.Height = size;
  strcpy_s (desc.FaceName, face.c_str ());

  if (D3DXCreateFontIndirect (m_dev, &desc, &m_font) != D3D_OK)
  {
    fout << "ERROR: Font Initialization failed!" << endl;
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////
bool cGame::InitInput ()
{
  m_input = new cInput (m_hwnd);
  if (m_input == NULL)
  {
    fout << "ERROR: Input Initialization failed!" << endl;
    return false;
  }
  else if (m_input->Error ())
  {
    fout << "ERROR: Input Initialization failed!" << endl;
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////
bool cGame::InitBackBuffer ()
{
  HRESULT hr = m_dev->GetBackBuffer (
    0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);
  if (hr != D3D_OK)
  {
    fout << "Back Buffer Initialization failed!" << endl;
    return false;
  }
  return true;
}
/////////////////////////////////////////////////
/*LPDIRECT3DTEXTURE9 cGame::LoadTexture (
  const string& filename, D3DCOLOR transColor)
{
  LPDIRECT3DTEXTURE9 image = NULL;
  D3DXIMAGE_INFO info;

  HRESULT hr = D3DXGetImageInfoFromFile (
    filename.c_str (), &info);

  if (hr != D3D_OK) return NULL;

  hr = D3DXCreateTextureFromFileEx (m_dev, 
    filename.c_str (), info.Width, info.Height, 
    1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, 
    D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
    transColor, &info, NULL, &image);

  if (hr != D3D_OK) return NULL;

  return image;
}
*/
/////////////////////////////////////////////////
bool cGame::Run ()
{
  static stringstream ss;
  static RECT rc = {0,0,m_width,m_height};
  m_input->PollInput ();
  
  long lx=m_input->MouseX();
  long ly=m_input->MouseY();
  long lz=m_input->MouseZ();
  if (m_input->KeyDown (DIK_ESCAPE))
    PostMessage (m_hwnd, WM_DESTROY, 0, 0);
  
float x=(float)lx;
float y=(float)ly;
float z=(float)lz;


  
m_dev->Clear (0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
   D3DCOLOR_XRGB (50, 50, 50), 1.0f, 0);

  //InitLighting();
D3DXVECTOR3 mouse_place(x,y,z);
D3DXVECTOR3 Pos=m_camera->GetPosition();
D3DXVECTOR3 Up=m_camera->GetUp();

float Posx=Pos.x;
float finalX=Posx-x;
float Posy=Pos.y;
float finalY=Posy-y;
//m_camera->LookAtPos(&Pos,&mouse_place,&Up,finalX,finalY);


//m_camera->SetLookAt(mouse_place);
//m_camera->MoveInDirection(cameraMove,&mouse_place);
int i=0;
  if (m_dev->BeginScene () == D3D_OK)
  {

    //InitModel(GetModel());
	if (m_input->KeyDown(DIK_LEFT)){
	  m_camera->MoveLeft(cameraMove,m_BoundingBox);
	 // m_camera->LookAtPos(&Pos,&mouse_place,&Up,finalX,finalY);
	  
	  
	 
  }
	if (m_input->KeyDown(DIK_RIGHT)){
		m_camera->MoveRight(cameraMove,m_BoundingBox);
		
	}
	if(m_input->KeyDown(DIK_UP)){
	m_camera->MoveForward(cameraMove,m_BoundingBox);
		
	}
	if(m_input->KeyDown(DIK_DOWN)){
		m_camera->MoveForward(-cameraMove,m_BoundingBox);
		
	}
	if(m_input->KeyDown(DIK_W)){
		m_camera->MoveForward(cameraMove,m_BoundingBox);
		
	}
	if(m_input->KeyDown(DIK_S)){
		m_camera->MoveForward(-cameraMove,m_BoundingBox);
		
	}
	if(m_input->KeyDown(DIK_D)){
		m_camera->RotateRight(0.1f,m_BoundingBox);
	}
	if(m_input->KeyDown(DIK_A)){
		m_camera->RotateRight(-.1f,m_BoundingBox);
		
		
	}

	D3DXVECTOR3 pos= m_camera->GetPosition();
	D3DXVECTOR3 look=m_camera->GetLookAt();
	D3DXVECTOR3 right=m_camera->GetRight();

	/*ss << "Camera\n Position:" << pos.x << "," << pos.y << " , " << pos.z 
		<< "\n Direction: " << look.x << ", " << look.y << ", " <<look.z
		<< "\n Right: "<< right.x << " ," <<right.y << ". " <<right.z;*/

	m_light->SetPosition(pos);
	m_light->SetDirection(look);


	pos = m_light->GetPosition();
	look = m_light->GetDirection();
	
	/*ss << "\nLight\n Position: " << pos.x << "," << pos.y << ", " << pos.z
		<< "\n Direction: " << look.x << ", " <<look.y << " , " << look.z;
	m_font->DrawText ( NULL,ss.str().c_str(),-1, &rc, 0, D3DCOLOR_XRGB(255,255,255));
	ss.str ("");*/

	
	
		m_model[0]->DrawModel(m_dev);
	   m_model[1]->DrawModel(m_dev);
		m_model[2]->DrawModel(m_dev);
		m_model[3]->DrawModel(m_dev);
			m_model[4]->DrawModel(m_dev);
			m_model[5]->DrawModel(m_dev);
			m_model[6]->DrawModel(m_dev);
			m_model[7]->DrawModel(m_dev);
			m_model[8]->DrawModel(m_dev);
			m_model[9]->DrawModel(m_dev);
			m_model[10]->DrawModel(m_dev);
			m_model[11]->DrawModel(m_dev);
			m_model[12]->DrawModel(m_dev);
			m_model[13]->DrawModel(m_dev);
			m_model[14]->DrawModel(m_dev);
			m_model[15]->DrawModel(m_dev);
			m_model[16]->DrawModel(m_dev);
			m_model[17]->DrawModel(m_dev);
			m_model[18]->DrawModel(m_dev);
			m_model[19]->DrawModel(m_dev);
			m_model[20]->DrawModel(m_dev);
		m_model[21]->DrawModel(m_dev);
			m_model[22]->DrawModel(m_dev);
			m_model[23]->DrawModel(m_dev);
			m_model[24]->DrawModel(m_dev);
			m_model[25]->DrawModel(m_dev);
			m_model[26]->DrawModel(m_dev);
			m_model[27]->DrawModel(m_dev);
			m_model[28]->DrawModel(m_dev);
			m_model[29]->DrawModel(m_dev);
			m_model[30]->DrawModel(m_dev);
			m_model[31]->DrawModel(m_dev);
			m_model[32]->DrawModel(m_dev);
			m_model[33]->DrawModel(m_dev);
			m_model[34]->DrawModel(m_dev);
			m_model[35]->DrawModel(m_dev);
			m_model[36]->DrawModel(m_dev);
			m_model[37]->DrawModel(m_dev);
			m_model[38]->DrawModel(m_dev);
			m_model[39]->DrawModel(m_dev);
			/*	m_model[40]->DrawModel(m_dev);
			m_model[41]->DrawModel(m_dev);
			m_model[42]->DrawModel(m_dev);
			m_model[43]->DrawModel(m_dev);
			m_model[44]->DrawModel(m_dev);
			m_model[45]->DrawModel(m_dev);
			m_model[46]->DrawModel(m_dev);
			m_model[47]->DrawModel(m_dev);
			m_model[48]->DrawModel(m_dev);
			m_model[49]->DrawModel(m_dev);
			m_model[50]->DrawModel(m_dev);
			m_model[51]->DrawModel(m_dev);
			m_model[52]->DrawModel(m_dev);
			m_model[53]->DrawModel(m_dev);
			m_model[54]->DrawModel(m_dev);
			m_model[55]->DrawModel(m_dev);
			m_model[56]->DrawModel(m_dev);
			m_model[57]->DrawModel(m_dev);*/


		
	
   /* bool Check=false;
	Check = m_BoundingBox[2]->isPointInside(m_camera->GetPosition());
	fout<<Check<<endl;
	if(Check == true){
		if(i==2){
			m_camera->MoveLeft(cameraMove+1.0f,m_BoundingBox*[]);
		
		}
		if(i==1){
			m_camera->MoveRight(cameraMove+1.0f,m_BoundingBox*[]);
		Check = false;
	}
	}
	//Check = ;
	/*while (m_BoundingBox[0]->isPointInside(m_camera->GetPosition())){
		m_camera->MoveUp(cameraMove+0.01f);
		
	}*/
	
/*Check = m_BoundingBox[1]->isPointInside(m_camera->GetPosition());
	
	if(Check == true){
		/*D3DXVECTOR3 a;
		
		a = m_camera->GetPosition();
		fout<< "Vector A" << a.x<< "         "<< a.y << "               " << a.z;
		a.x=a.x-0.05f;
		a.y=a.y-0.05f;
		a.z=a.z-0.05f;
		if(i==1){
		m_camera->MoveRight(cameraMove+1.0f,m_BoundingBox*[]);
		}
		if(i==2){
			m_camera->MoveLeft(cameraMove+1.0f,m_BoundingBox*[]);
		}
	Check = false;
	}*/

    m_dev->EndScene ();
    m_dev->Present (NULL, NULL, NULL, NULL);
    
  return true;

  }

  return false;
}

/////////////////////////////////////////////////
cGame::~cGame ()
{
  if (m_input != NULL)
    delete m_input;
  m_input = NULL;

  if (m_dev != NULL)
    m_dev->Release ();
  m_dev = NULL;

  if (m_d3d != NULL)
    m_d3d->Release ();
  m_d3d = NULL;

  for(int i=0;i<21;i++){
  if(m_model[i]!= NULL){
	  delete m_model[i];
  m_model[i] = NULL;
   }
  }

  if(m_camera != NULL)
	  delete m_camera;
  m_camera=NULL;

    for(int i=0;i<21;i++){
  if(m_BoundingBox[i]!= NULL){
	  delete m_BoundingBox[i];
  m_BoundingBox[i] = NULL;
   }
  }
 

}