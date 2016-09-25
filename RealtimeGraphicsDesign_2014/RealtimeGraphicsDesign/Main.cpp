#include <vector>
#include "DxBase.h"
#include "Cam.h"
#include "SkyBox.h"

// Globals

IDirect3DDevice9* Device = 0;

const int Width = 1366;
const int Height = 768;

ID3DXMesh*									Mesh = 0;
std::vector<D3DMATERIAL9>		Mtrls(0);
std::vector<IDirect3DTexture9*>	Textures(0);

Cam g_cam;
CSkyBox box;

// Framework functions

bool Setup()
{
	HRESULT hr = 0;

	// Load the XFile data.

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		"model.X",
		D3DXMESH_MANAGED,
		Device,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&Mesh);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}

	// Extract the materials, and load textures.

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			// save the ith material
			Mtrls.push_back(mtrls[i].MatD3D);

			// check if the ith material has an associative texture
			if (mtrls[i].pTextureFilename != 0)
			{
				// yes, load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					Device,
					mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back(tex);
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back(0);
			}
		}
	}
	DxBase::Release<ID3DXBuffer*>(mtrlBuffer); // done w/ buffer

	// Optimize the mesh.

	hr = Mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);

	DxBase::Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer

	if (FAILED(hr))
	{
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
		return false;
	}

	// Set Lights.

	D3DXCOLOR col1(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 lightDir1(1.0f, 1.0f, 0.0f);
	D3DLIGHT9 light1 = DxBase::InitDirectionalLight(&lightDir1, &col1);

	D3DXCOLOR col2(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 lightDir2(1.0f, -1.0f, 0.0f);
	D3DLIGHT9 light2 = DxBase::InitDirectionalLight(&lightDir2, &col2);

	D3DXCOLOR col3(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 lightDir3(-1.0f, -1.0f, -1.0f);
	D3DLIGHT9 light3 = DxBase::InitDirectionalLight(&lightDir3, &col3);

	D3DXCOLOR col4(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 lightDir4(1.0f, 1.0f, -1.0f);
	D3DLIGHT9 light4 = DxBase::InitDirectionalLight(&lightDir4, &col4);

	Device->SetLight(0, &light1);
	Device->SetLight(1, &light2);
	Device->SetLight(2, &light3);
	Device->SetLight(3, &light4);
	Device->LightEnable(3, true);
	Device->LightEnable(2, true);
	Device->LightEnable(1, true);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	// Set projection matrix.

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)Width / (float)Height,
		1.0f,
		10000000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// Set SkyBox.

	box.SetCenter(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	box.SetSize(10000000.0f);
	box.SetSkyBoxTexture(CSkyBox::TOP, Device, "006sky (5).jpg");
	box.SetSkyBoxTexture(CSkyBox::BOTTOM, Device, "006sky (5).jpg");
	box.SetSkyBoxTexture(CSkyBox::LEFT, Device, "006sky (3).jpg");
	box.SetSkyBoxTexture(CSkyBox::RIGHT, Device, "006sky (4).jpg");
	box.SetSkyBoxTexture(CSkyBox::BACK, Device, "006sky (2).jpg");
	box.SetSkyBoxTexture(CSkyBox::FRONT, Device, "006sky (1).jpg");

	return true;
}

void Cleanup()
{
	DxBase::Release<ID3DXMesh*>(Mesh);

	for (int i = 0; i < Textures.size(); i++)
		DxBase::Release<IDirect3DTexture9*>(Textures[i]);
}

bool Display(float timeDelta)
{
	if (Device)
	{
		//	Cam
		::Sleep(10);

		if (::GetAsyncKeyState('W') & 0x8000f)
			g_cam.walk(100000.0f * timeDelta);

		if (::GetAsyncKeyState('S') & 0x8000f)
			g_cam.walk(-100000.0f * timeDelta);

		if (::GetAsyncKeyState('A') & 0x8000f)
			g_cam.strafe(-100000.0f * timeDelta);

		if (::GetAsyncKeyState('D') & 0x8000f)
			g_cam.strafe(100000.0f * timeDelta);

		if (::GetAsyncKeyState('R') & 0x8000f)
			g_cam.fly(100000.0f * timeDelta);

		if (::GetAsyncKeyState('F') & 0x8000f)
			g_cam.fly(-100000.0f * timeDelta);

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			g_cam.pitch(1.0f * timeDelta);

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			g_cam.pitch(-1.0f * timeDelta);

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			g_cam.yaw(-1.0f * timeDelta);

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			g_cam.yaw(1.0f * timeDelta);

		if (::GetAsyncKeyState('N') & 0x8000f)
			g_cam.roll(1.0f * timeDelta);

		if (::GetAsyncKeyState('M') & 0x8000f)
			g_cam.roll(-1.0f * timeDelta);

		D3DXMATRIX V;
		g_cam.getViewMatrix(&V);
		Device->SetTransform(D3DTS_VIEW, &V);

		// Render

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000FFFF, 1.0f, 0);
		Device->BeginScene();
		
		for (int i = 0; i < Mtrls.size(); i++)
		{
			Device->SetMaterial(&Mtrls[i]);
			Device->SetTexture(0, Textures[i]);
			Mesh->DrawSubset(i);
		}

		box.Render(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

// WndProc

LRESULT CALLBACK DxBase::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

// WinMain

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	if (!DxBase::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	DxBase::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}