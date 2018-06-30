#include "stdafx.h"
#include "MainLoop.h"
#define CREATE_CONSOLE


#include "ASP.h"
#include "ASP_Animator.h"

ASP_AnimeSample* animeSample;
ASP_Animation* anima;

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


	SingletonInstance(ASP_Reader)->RegistASP(L"Test", L"./Resource/test.png", L"./Resource/test.asp");
	ASP_Texture* asp = SingletonInstance(ASP_Reader)->FindASP(L"Test");
	if (asp)
	{
		ASP_Sprite* aspp = nullptr;
		animeSample = new ASP_AnimeSample;
		animeSample->resize(4);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"temp1"), 120);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"temp2"), 120);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"temp3"), 120);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"temp4"), 120);

		anima = new ASP_Animation(animeSample);
	}
	return true;
}

void MainLoop::Update()
{
	g_inputDevice.BeginFrame(g_processManager->GetWndInfo()->hWnd);

	++(*anima);

	g_inputDevice.EndFrame();
}

bool MainLoop::Render()
{
	ASP_Texture* asp = SingletonInstance(ASP_Reader)->FindASP(L"Test");
	if (asp)
	{
		///ASP_Sprite* aspp = nullptr;
		///if (g_inputDevice.IsKeyPressed(VK_F1))	aspp = (*asp)(L"temp1");
		///if (g_inputDevice.IsKeyPressed(VK_F2))	aspp = (*asp)(L"temp2");
		///if (g_inputDevice.IsKeyPressed(VK_F3))	aspp = (*asp)(L"temp3");
		///if (g_inputDevice.IsKeyPressed(VK_F4))	aspp = (*asp)(L"temp4");
		
		const ASP_Sprite* aspp = (*anima)();

		if (aspp)
		{
			const ASP_UV& uv = aspp->UVData();

			DEVICE->SetTexture(0, *asp);
			SingletonInstance(SimpleDrawer)->DrawTexPlane(DEVICE, uv.minU, uv.minV, uv.maxU, uv.maxV);
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
