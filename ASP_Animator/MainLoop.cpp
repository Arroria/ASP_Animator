#include "stdafx.h"
#include "MainLoop.h"
#define CREATE_CONSOLE



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

	return true;
}

void MainLoop::Update()
{
	g_inputDevice.BeginFrame(g_processManager->GetWndInfo()->hWnd);

	g_inputDevice.EndFrame();
}

bool MainLoop::Render()
{
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
