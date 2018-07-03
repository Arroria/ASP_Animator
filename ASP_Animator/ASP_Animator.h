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

enum class ASPAnimeState
{
	Nothing,
	NextFrame,
	End,
};
class ASP_Animation
{
private:
	const ASP_AnimeSample* m_animeSample;
	
public:
	size_t m_index;
	size_t m_time;

public:
	ASPAnimeState operator++()
	{
		if (m_animeSample &&
			++m_time >= (*m_animeSample)[m_index].duration)
		{
			m_time = 0;
			if (++m_index >= m_animeSample->size())
			{
				m_index = 0;
				return ASPAnimeState::End;
			}
			return ASPAnimeState::NextFrame;
		}
		return ASPAnimeState::Nothing;
	};

	bool operator==(const ASP_Animation& animation) const
	{
		return m_animeSample == animation.m_animeSample;
	};

	const ASP_Sprite * operator()() const
	{
		return m_animeSample ?
			(*m_animeSample)[m_index].aspSprite :
			nullptr;
	};

public:
	ASP_Animation() : m_animeSample(nullptr), m_index(NULL), m_time(NULL) {}
	ASP_Animation(ASP_AnimeSample* animeSample) : m_animeSample(animeSample), m_index(0), m_time(0) {}
	ASP_Animation & operator=(ASP_AnimeSample* animeSample) { return *this = ASP_Animation(animeSample); }
	// 동적할당하면 위에 생성자 작동안할줄 알고 만들었는데 혹시나해서 테스트하니 잘되가지고 필요없어진 코드 //ASP_Animation & operator=(ASP_AnimeSample* animeSample) { m_animeSample = animeSample; m_index = 0, m_time = 0; return *this; }
};



class ASP_Animated
{
private:
	ASP_Texture * m_aspTex;
	std::map<std::wstring, ASP_AnimeSample*> m_aspAnimeSample;

public:
	bool RegistAnimeSample(const std::wstring& key, ASP_AnimeSample* animeSample);
	
	ASP_Texture * aspTex() { return m_aspTex; }
	ASP_AnimeSample * operator() (const std::wstring& key);

public:
	ASP_Animated(ASP_Texture* aspTex);
	~ASP_Animated();
};
