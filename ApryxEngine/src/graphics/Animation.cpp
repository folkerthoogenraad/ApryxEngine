#include "Animation.h"

namespace apryx {

	void Animation::update(float delta)
	{
		m_Index += delta * m_Speed;

		// TODO just use fmod
		while (m_Index > m_Sprites.size())
			m_Index -= m_Sprites.size();

		while (m_Index < 0)
			m_Index += m_Sprites.size();
	}

	void Animation::restart()
	{
		m_Index = 0;
	}

	const Sprite & Animation::getCurrentSprite() const
	{
		return m_Sprites[(int)m_Index];
	}

	void Animation::addSprite(Sprite sprite)
	{
		m_Sprites.push_back(std::move(sprite));
	}
}