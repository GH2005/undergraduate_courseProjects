#ifndef _Skybox_H_
#define	_Skybox_H_

#include <d3dx9.h>

struct SkyboxVertices{
	enum{
		fvf		= D3DFVF_XYZ | D3DFVF_TEX1,
	};
	D3DVECTOR	pos;
	float		u;
	float		v;
};

class CSkyBox
{
public:
	CSkyBox();
	~CSkyBox();

	enum SKYBOX_SIDE
	{
		TOP	= 0 ,
		BOTTOM	,
		LEFT	,
		RIGHT	,
		BACK	,
		FRONT	,
		NUMBER	,
	};

private:

	D3DXVECTOR3		m_vecCenter;
	float			m_fSize;
	SkyboxVertices	m_Verts[6][4];
	IDirect3DTexture9*		m_Texture[NUMBER];

public:

	bool	SetSkyBoxTexture(SKYBOX_SIDE side, IDirect3DDevice9* dev, const char* texture);

	void	Render(IDirect3DDevice9* dev);

	void	SetCenter( D3DXVECTOR3 pos );

	void	SetSize( float size );

};

#endif