#include "stdafx.h"
#include "MainLoop.h"
#define CREATE_CONSOLE


#include "ASP.h"
ASP* asp = nullptr;


bool MainLoop::Initialize()
{
#ifdef CREATE_CONSOLE
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif

				

	DragAcceptFiles(g_processManager->GetWndInfo()->hWnd, true);


	D3DXCreateSprite(DEVICE, &g_sprtie);


	cout.imbue(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_ZENABLE, false);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);



	asp = new ASP;
	D3DXCreateTextureFromFileExW(DEVICE, L"./Resource/test.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, NULL, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &asp->info, nullptr, &asp->tex);
	if (asp->tex)
	{
		std::wfstream fstream;
		fstream.imbue(std::locale("kor"));
		fstream.open(L"./Resource/test.asp", std::ios::in);
		while (!fstream.eof())
		{
			std::wstring temp;
			fstream >> temp;
			if (temp.empty())
				continue;
			wcout << temp << endl;

			ASPP aspp;
			fstream
				>> aspp.minU
				>> aspp.minV
				>> aspp.maxU
				>> aspp.maxV;

			(aspp.minU /= asp->info.Width) += 1.f / (1 << 16);
			(aspp.maxU /= asp->info.Width);
			(aspp.minV /= asp->info.Height) += 1.f / (1 << 16);
			(aspp.maxV /= asp->info.Height);

			asp->asp.insert(std::make_pair(temp, aspp));
		}
	}

	return true;
}

void MainLoop::Update()
{
	g_inputDevice.BeginFrame(g_processManager->GetWndInfo()->hWnd);


	g_inputDevice.EndFrame();
}

bool MainLoop::Render()
{
	if (asp)
	{
		ASPP* aspp = nullptr;
		if (g_inputDevice.IsKeyPressed(VK_F1))	aspp = &asp->asp[L"temp1"];
		if (g_inputDevice.IsKeyPressed(VK_F2))	aspp = &asp->asp[L"temp2"];
		if (g_inputDevice.IsKeyPressed(VK_F3))	aspp = &asp->asp[L"temp3"];
		if (g_inputDevice.IsKeyPressed(VK_F4))	aspp = &asp->asp[L"temp4"];
		
		if (aspp)
		{
			DEVICE->SetTexture(0, asp->tex);
			SingletonInstance(SimpleDrawer)->DrawTexPlane(DEVICE, aspp->minU, aspp->minV, aspp->maxU, aspp->maxV);
		}
	}

	return true;
}

bool MainLoop::Release()
{



#ifdef CREATE_CONSOLE
	FreeConsole();
#endif
	return true;
}


LRESULT MainLoop::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	g_inputDevice.MsgProc(msg, wParam, lParam);
	
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return 0;
}
