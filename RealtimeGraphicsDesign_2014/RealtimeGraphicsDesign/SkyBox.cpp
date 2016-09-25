#include "SkyBox.h"

CSkyBox::CSkyBox()
{
	SetCenter(D3DXVECTOR3(0,0,0));
	SetSize(0);
}

CSkyBox::~CSkyBox()
{
}


bool	CSkyBox::SetSkyBoxTexture( SKYBOX_SIDE side, IDirect3DDevice9* dev, const char* texture )
{
	return D3DXCreateTextureFromFile(dev, texture, &this->m_Texture[side]);
}

void	CSkyBox::Render(IDirect3DDevice9* dev)
{
	D3DXMATRIX tmp;
	D3DXMatrixTranslation( &tmp , m_vecCenter.x , m_vecCenter.y , m_vecCenter.z );
	dev->SetTransform(D3DTS_WORLD, &tmp);

	// disable lights.

	dev->SetRenderState( D3DRS_LIGHTING , false );
	dev->LightEnable( 0 , false );
	dev->LightEnable(1, false);

	// set FVFs.

	dev->SetFVF( SkyboxVertices::fvf );

	dev->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_MODULATE );

	dev->SetTexture( 1 , NULL );

	// render.

	dev->SetTexture( 0 , m_Texture[TOP] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[TOP] , sizeof(SkyboxVertices) );
	dev->SetTexture( 0 , m_Texture[BOTTOM] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[BOTTOM] , sizeof(SkyboxVertices) );
	dev->SetTexture( 0 , m_Texture[LEFT] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[LEFT] , sizeof(SkyboxVertices) );
	dev->SetTexture( 0 , m_Texture[RIGHT] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[RIGHT] , sizeof(SkyboxVertices) );
	dev->SetTexture( 0 , m_Texture[BACK] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[BACK] , sizeof(SkyboxVertices) );
	dev->SetTexture( 0 , m_Texture[FRONT] );
	dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP , 2 , &m_Verts[FRONT] , sizeof(SkyboxVertices) );
}

void	CSkyBox::SetCenter( D3DXVECTOR3 pos )
{
	m_vecCenter = pos;
}

void	CSkyBox::SetSize( float size )
{
	m_fSize = size;
	// top
	m_Verts[TOP][0].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[TOP][0].u = 0.0f;m_Verts[TOP][0].v = 0.0f;
	m_Verts[TOP][1].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[TOP][1].u = 1.0f;m_Verts[TOP][1].v = 0.0f;
	m_Verts[TOP][2].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[TOP][2].u = 0.0f;m_Verts[TOP][2].v = 1.0f;
	m_Verts[TOP][3].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[TOP][3].u = 1.0f;m_Verts[TOP][3].v = 1.0f;

	// bottom
	m_Verts[BOTTOM][0].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[BOTTOM][0].u = 0.0f;m_Verts[BOTTOM][0].v = 0.0f;
	m_Verts[BOTTOM][1].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[BOTTOM][1].u = 1.0f;m_Verts[BOTTOM][1].v = 0.0f;
	m_Verts[BOTTOM][2].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[BOTTOM][2].u = 0.0f;m_Verts[BOTTOM][2].v = 1.0f;
	m_Verts[BOTTOM][3].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[BOTTOM][3].u = 1.0f;m_Verts[BOTTOM][3].v = 1.0f;

	// left
	m_Verts[LEFT][0].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[LEFT][0].u = 0.0f;m_Verts[LEFT][0].v = 0.0f;
	m_Verts[LEFT][1].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[LEFT][1].u = 1.0f;m_Verts[LEFT][1].v = 0.0f;
	m_Verts[LEFT][2].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[LEFT][2].u = 0.0f;m_Verts[LEFT][2].v = 1.0f;
	m_Verts[LEFT][3].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[LEFT][3].u = 1.0f;m_Verts[LEFT][3].v = 1.0f;

	// right
	m_Verts[RIGHT][0].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[RIGHT][0].u = 0.0f;m_Verts[RIGHT][0].v = 0.0f;
	m_Verts[RIGHT][1].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[RIGHT][1].u = 1.0f;m_Verts[RIGHT][1].v = 0.0f;
	m_Verts[RIGHT][2].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[RIGHT][2].u = 0.0f;m_Verts[RIGHT][2].v = 1.0f;
	m_Verts[RIGHT][3].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[RIGHT][3].u = 1.0f;m_Verts[RIGHT][3].v = 1.0f;

	// back
	m_Verts[BACK][0].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[BACK][0].u = 0.0f;m_Verts[BACK][0].v = 0.0f;
	m_Verts[BACK][1].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  -m_fSize/2);m_Verts[BACK][1].u = 1.0f;m_Verts[BACK][1].v = 0.0f;
	m_Verts[BACK][2].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[BACK][2].u = 0.0f;m_Verts[BACK][2].v = 1.0f;
	m_Verts[BACK][3].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  -m_fSize/2);m_Verts[BACK][3].u = 1.0f;m_Verts[BACK][3].v = 1.0f;

	// front
	m_Verts[FRONT][0].pos = D3DXVECTOR3( - m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[FRONT][0].u = 0.0f;m_Verts[FRONT][0].v = 0.0f;
	m_Verts[FRONT][1].pos = D3DXVECTOR3( + m_fSize/2 ,  + m_fSize/2 ,  +m_fSize/2);m_Verts[FRONT][1].u = 1.0f;m_Verts[FRONT][1].v = 0.0f;
	m_Verts[FRONT][2].pos = D3DXVECTOR3( - m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[FRONT][2].u = 0.0f;m_Verts[FRONT][2].v = 1.0f;
	m_Verts[FRONT][3].pos = D3DXVECTOR3( + m_fSize/2 ,  - m_fSize/2 ,  +m_fSize/2);m_Verts[FRONT][3].u = 1.0f;m_Verts[FRONT][3].v = 1.0f;
}
