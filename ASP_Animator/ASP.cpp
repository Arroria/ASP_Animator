#include "stdafx.h"
#include "ASP.h"


ASP_Reader::ASP_Reader()
{
}
ASP_Reader::~ASP_Reader()
{
}



ASP * ASP_Reader::RegistASP(const std::wstring& key, const std::experimental::filesystem::path & texPath, const std::experimental::filesystem::path & aspPath)
{
	ASP* asp = nullptr;
	if (!(asp = new ASP))
		return nullptr;
	
	D3DXCreateTextureFromFileExW(DEVICE, L"./Resource/test.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, NULL, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &asp->info, nullptr, &asp->tex);
	if (!asp->tex)
		return nullptr;
	
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
	m_asp.insert(std::make_pair(key, asp));
	return asp;
}

ASP * ASP_Reader::FindASP(const std::wstring & key)
{
	auto findIter = m_asp.find(key);
	if (findIter == m_asp.end())
		return nullptr;
	return findIter->second;
}
