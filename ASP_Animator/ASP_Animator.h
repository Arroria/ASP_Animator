#pragma once
#include "ASP.h"

struct ASP_AnimeNode
{
	const ASP_Sprite * aspSprite;
	size_t duration;
	
	ASP_AnimeNode() : aspSprite(nullptr), duration(NULL) {}
	ASP_AnimeNode(ASP_Sprite * _aspSprite, size_t _duration) : aspSprite(_aspSprite), duration(_duration) {}
};

using ASP_AnimeSample = std::vector<ASP_AnimeNode>;
class ASP_Animation
{
private:
	const ASP_AnimeSample* m_animeSample;
	
public:
	size_t m_index;
	size_t m_time;

public:
	ASP_Animation * operator++()
	{
		if (++m_time >= (*m_animeSample)[m_index].duration)
		{
			m_time = 0;
			if (++m_index >= m_animeSample->size())
			{
				m_index = 0;
			}
		}
		return this;
	};

	const ASP_Sprite * operator()() const
	{
		return (*m_animeSample)[m_index].aspSprite;
	};

public:
	ASP_Animation(ASP_AnimeSample* animeSample) : m_animeSample(animeSample), m_index(0), m_time(0) {}
};

class ASP_Animator
{
public:
	ASP_Animator();
	~ASP_Animator();
};
