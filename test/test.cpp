struct HEIGHTMAP
{
	HEIGHTMAP(INTPOINT _size);
	~HEIGHTMAP();
	void Release();

	HRESULT CreateRandomHeightMap(int seed, float noiseSize,
								float persistance, int octaves);

	INTPOINT m_size;
	float m_maxheight;
	float *m_pHeightMap;
};

float Noise(int x)
{
	x = (x<<13) ^ x;
	return (1.0f - ((x * (x*x * 15731 + 789221)
		+ 1376312589) &
		0x7fffffff) / 1073741824.0f);
}

float CosInterpolate(float v1, float v2, float a)
{
	float angle = a * D3DX_PI;
	float prc = (1.0f - cos(angle)) * 0.5f;
	return v1*(1.0f - prc) + v2*prc;
}

EIGHTMAP::HEIGHTMAP(IDirect3DDevice9* Dev, INTPOINT _size)
{
	try
	{
		m_pDevice = Dev;
		m_size = _size;

		// Init m_pSprite
		D3DXCreateSprite(m_pDevice,&m_pSprite);

		//Reset the heightMap to 0
		m_maxHeight = 15.0f;
		m_pHeightMap = new float[m_size.x * m_size.y];
		memset(m_pHeightMap, 0, sizeof(float)*m_size.x*m_size.y);

		m_selRect.top = m_selRect.left = m_size.x / 2 - 5;
		m_selRect.bottom = m_selRect.right = m_size.x / 2 + 5;

		//Set particle vertex buffer and texture to NULL
		m_pVb = NULL;
		m_pHeightMapTexture = NULL;
	}
	catch(...)
	{
		debug.Print("Error in HEIGHTMAP::HEIGHTMAP()");
	}
}

HEIGHTMAP::~HEIGHTMAP()
{
	Release();
}

void HEIGHTMAP::Release()
{
	if(m_pHeightMap != NULL)delete [] m_pHeightMap;
	if(m_pVb != NULL)m_pVb->Release();
	if(m_pSprite != NULL)m_pSprite->Release();
	if(m_pHeightMapTexture != NULL)m_pHeightMapTexture->Release();
}

HRESULT HEIGHTMAP::CreateRandomHeightMap(int seed, float noiseSize, float persistence, int octaves)
{
	if(m_pHeightMapTexture != NULL){m_pHeightMapTexture->Release(); m_pHeightMapTexture = NULL;}
	m_pDevice->CreateTexture(m_size.x, m_size.y, 1, D3DUSAGE_DYNAMIC, D3DFMT_L8, D3DPOOL_DEFAULT, &m_pHeightMapTexture, NULL);

	D3DLOCKED_RECT lock;
	m_pHeightMapTexture->LockRect(0, &lock, NULL, NULL);

	//For each map node
	for(int y=0;y<m_size.y;y++)
		for(int x=0;x<m_size.x;x++)
		{
			//Scale x & y to the range of 0.0 - m_size
			float xf = ((float)x / (float)m_size.x) * noiseSize;
			float yf = ((float)y / (float)m_size.y) * noiseSize;

			float total = 0;			

			// For each octave
			for(int i=0;i<octaves;i++)
			{
				//Calculate frequency and amplitude (different for each octave)
				float freq = pow(2.0f, i);
				float amp = pow(persistence, i);

				//Calculate the x,y noise coordinates
				float tx = xf * freq;
				float ty = yf * freq;
				int tx_int = (int)tx;
				int ty_int = (int)ty;

				//Calculate the fractions of x & y
			    float fracX = tx - tx_int;
			    float fracY = ty - ty_int;

				//Get the noise of this octave for each of these 4 points
				float v1 = Noise(tx_int + ty_int * 57 + seed);
				float v2 = Noise(tx_int+ 1 + ty_int * 57 + seed);
				float v3 = Noise(tx_int + (ty_int+1) * 57 + seed);
				float v4 = Noise(tx_int + 1 + (ty_int+1) * 57 + seed);

				//Smooth in the X-axis
				float i1 = CosInterpolate(v1 , v2 , fracX);
				float i2 = CosInterpolate(v3 , v4 , fracX);

				//Smooth in the Y-axis
				total += CosInterpolate(i1 , i2 , fracY) * amp;
			}

			int b = (int)(128 + total * 128.0f);
			if(b < 0)b = 0;
			if(b > 255)b = 255;

			BYTE *bDest = (BYTE*)lock.pBits;
			bDest += y * lock.Pitch + x;
			*bDest = b;

			//Save to heightMap
			m_pHeightMap[x + y * m_size.x] = ((float)b / 255.0f) * m_maxHeight;
		}

	m_pHeightMapTexture->UnlockRect(0);

	return S_OK;
}
