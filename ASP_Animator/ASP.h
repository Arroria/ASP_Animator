#pragma once

class ASP_Reader;
struct ASP_UV
{
	float minU;
	float minV;
	float maxU;
	float maxV;

	ASP_UV() : minU(NULL), minV(NULL), maxU(NULL), maxV(NULL) {}
	ASP_UV(float _minU, float _minV, float _maxU, float _maxV) : minU(_minU), minV(_minV), maxU(_maxU), maxV(_maxV) {}
};

class ASP_Sprite;
class ASP_Texture
{
	friend ASP_Reader;
public:
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO texInfo;
	std::map<std::wstring, ASP_Sprite*> spriteList;

public:
	inline operator LPDIRECT3DTEXTURE9() { return texture; }
	ASP_Texture() : texture(nullptr) { ZeroMemory(&texInfo, sizeof(D3DXIMAGE_INFO)); }
	ASP_Texture(LPDIRECT3DTEXTURE9 _texture, const D3DXIMAGE_INFO& _texInfo) : texture(_texture), texInfo(_texInfo) { texture->AddRef(); }
	~ASP_Texture() { texture->Release(); }
};

class ASP_Sprite
{
private:
	LPDIRECT3DTEXTURE9& texture;
	D3DXIMAGE_INFO& texInfo;
	ASP_UV uv;

public:
	inline operator LPDIRECT3DTEXTURE9() { return texture; }
	inline LPDIRECT3DTEXTURE9 Texture() { return texture; }
	inline const D3DXIMAGE_INFO& Info() const { return texInfo; }
	inline const ASP_UV& UVData()		const { return uv; }

public:
	ASP_Sprite(LPDIRECT3DTEXTURE9 _texture, D3DXIMAGE_INFO& _texInfo, const ASP_UV& _uv) : texture(_texture), texInfo(_texInfo), uv(_uv) { texture->AddRef(); }
	~ASP_Sprite() { texture->Release(); }
};


#include <filesystem>
#include "Singleton.h"
class ASP_Reader :
	public Singleton<ASP_Reader>
{
private:
	std::map<std::wstring, ASP_Texture*> m_asp;

public:
	ASP_Texture * RegistASP(const std::wstring& key, const std::experimental::filesystem::path& texPath, const std::experimental::filesystem::path& aspPath);
	ASP_Texture * FindASP(const std::wstring& key);

public:
	ASP_Reader();
	~ASP_Reader();
};


