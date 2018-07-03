#include "stdafx.h"
#include "ASP.h"



ASP_Texture * ASP_Texture::Create(LPDIRECT3DDEVICE9 device, const std::experimental::filesystem::path & texPath, const std::experimental::filesystem::path & aspPath)
{
	//Create Texture
	LPDIRECT3DTEXTURE9 texture = nullptr;
	D3DXIMAGE_INFO texInfo;

	if (FAILED( D3DXCreateTextureFromFileExW(DEVICE, texPath.wstring().data(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, NULL, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &texInfo, nullptr, &texture) ))
		return nullptr;


	//Create ASP Texture
	ASP_Texture* aspTex = nullptr;
	if (aspTex = new ASP_Texture(texture, texInfo))
	{
		//Open File
		std::wfstream fstream;
		fstream.imbue(std::locale("kor"));
		fstream.open(aspPath, std::ios::in);
		if (fstream.fail())
		{
			delete aspTex;
			aspTex = nullptr;
		}
		else
		{
			//Create ASP Sprite
			while (!fstream.eof())
			{
				std::wstring spriteKey;
				ASP_UV uv;
				{
					fstream >> spriteKey;
					if (spriteKey.empty())
						continue;

					fstream
						>> uv.minU
						>> uv.minV
						>> uv.maxU
						>> uv.maxV;
				}

				constexpr size_t OffsetSize = 16;
				(uv.minU /= texInfo.Width) += 1.f / (1 << OffsetSize);
				(uv.maxU /= texInfo.Width);
				(uv.minV /= texInfo.Height) += 1.f / (1 << OffsetSize);
				(uv.maxV /= texInfo.Height);

				ASP_Sprite* aspSprite = new ASP_Sprite(aspTex->texture, aspTex->texInfo, uv);
				aspTex->spriteList.insert(std::make_pair(spriteKey, aspSprite));
			}
		}
		fstream.close();
	}
	texture->Release();
	return aspTex;
}
