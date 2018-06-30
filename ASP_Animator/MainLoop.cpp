#include "stdafx.h"
#include "MainLoop.h"
#define CREATE_CONSOLE


#include "ASP.h"
#include "ASP_Animator.h"

ASP_AnimeSample* animeSamples[5];
ASP_Animation anima;

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


	SingletonInstance(ASP_Reader)->RegistASP(L"Reisen", L"./Resource/pl03.png", L"./Resource/pl03.asp");
	ASP_Texture* asp = SingletonInstance(ASP_Reader)->FindASP(L"Reisen");
	if (asp)
	{
		ASP_Sprite* aspp = nullptr;

		animeSamples[0] = new ASP_AnimeSample;
		ASP_AnimeSample* animeSample = animeSamples[0];
		animeSample->resize(8);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"p00"), 20);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"p01"), 20);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"p02"), 20);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"p03"), 20);
		(*animeSample)[4] = ASP_AnimeNode((*asp)(L"p04"), 20);
		(*animeSample)[5] = ASP_AnimeNode((*asp)(L"p05"), 20);
		(*animeSample)[6] = ASP_AnimeNode((*asp)(L"p06"), 20);
		(*animeSample)[7] = ASP_AnimeNode((*asp)(L"p07"), 20);

		animeSamples[1] = new ASP_AnimeSample;
		animeSample = animeSamples[1];
		animeSample->resize(4);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"p10"), 20);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"p11"), 20);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"p12"), 20);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"p13"), 20);

		animeSamples[2] = new ASP_AnimeSample;
		animeSample = animeSamples[2];
		animeSample->resize(4);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"p14"), 20);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"p15"), 20);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"p16"), 20);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"p17"), 20);

		animeSamples[3] = new ASP_AnimeSample;
		animeSample = animeSamples[3];
		animeSample->resize(4);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"p20"), 20);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"p21"), 20);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"p22"), 20);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"p23"), 20);

		animeSamples[4] = new ASP_AnimeSample;
		animeSample = animeSamples[4];
		animeSample->resize(4);
		(*animeSample)[0] = ASP_AnimeNode((*asp)(L"p24"), 20);
		(*animeSample)[1] = ASP_AnimeNode((*asp)(L"p25"), 20);
		(*animeSample)[2] = ASP_AnimeNode((*asp)(L"p26"), 20);
		(*animeSample)[3] = ASP_AnimeNode((*asp)(L"p27"), 20);

		anima = animeSamples[0];
	}
	return true;
}

void MainLoop::Update()
{
	g_inputDevice.BeginFrame(g_processManager->GetWndInfo()->hWnd);

	++anima;

	g_inputDevice.EndFrame();
}

bool MainLoop::Render()
{
	ASP_Texture* asp = SingletonInstance(ASP_Reader)->FindASP(L"Reisen");
	if (asp)
	{
		const ASP_Sprite* aspp = nullptr;
		if (g_inputDevice.IsKeyPressed(VK_F1))			anima = animeSamples[0];
		if (g_inputDevice.IsKeyPressed(VK_F2))			anima = animeSamples[1];
		if (g_inputDevice.IsKeyPressed(VK_F3))			anima = animeSamples[2];
		if (g_inputDevice.IsKeyPressed(VK_F4))			anima = animeSamples[3];
		if (g_inputDevice.IsKeyPressed(VK_F5))			anima = animeSamples[4];
		aspp = anima();
		

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
