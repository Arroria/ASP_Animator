#include "stdafx.h"
#include "ASP_Animator.h"



ASP_Animated::ASP_Animated(ASP_Texture * aspTex)
{
}
ASP_Animated::~ASP_Animated()
{
	for (auto& aspAnimeSampleIter : m_aspAnimeSample)
		SAFE_DELETE(aspAnimeSampleIter.second);
	m_aspAnimeSample.clear();
}



bool ASP_Animated::RegistAnimeSample(const std::wstring & key, ASP_AnimeSample * animeSample)
{
	auto findIter = m_aspAnimeSample.find(key);
	if (findIter == m_aspAnimeSample.end())
	{
		m_aspAnimeSample.insert(std::make_pair(key, animeSample));
		return true;
	}
	return false;
}

ASP_AnimeSample * ASP_Animated::operator() (const std::wstring& key)
{
	auto findIter = m_aspAnimeSample.find(key);
	if (findIter == m_aspAnimeSample.end())
		return nullptr;
	return findIter->second;
}
