#pragma once

struct ASPP
{
	float minU;
	float minV;
	float maxU;
	float maxV;
	ASPP() : minU(NULL), minV(NULL), maxU(NULL), maxV(NULL) {}
	ASPP(float _minU, float _minV, float _maxU, float _maxV) : minU(_minU), minV(_minV), maxU(_maxU), maxV(_maxV) {}
};

struct ASP
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	std::map<std::wstring, ASPP> asp;
	ASP() : tex(nullptr) { ZeroMemory(&info, sizeof(D3DXIMAGE_INFO)); }
};


class ASP_Reader
{
private:

public:
	ASP_Reader();
	~ASP_Reader();
};

