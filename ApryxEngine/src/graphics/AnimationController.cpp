#include "AnimationController.h"

namespace apryx {
	AnimationTransition::AnimationTransition(std::string from, std::string to, std::string variable, Condition condition, float threshold)
		: m_From(from),
			m_To(to),
			m_Variable(variable),
			m_Condition(condition),
			m_Threshold(threshold)
	{ }

	AnimationTransition::AnimationTransition(std::string from, std::string to, std::string variable, bool value)
		: m_From(from),
		m_To(to),
		m_Variable(variable),
		m_Condition(Equal),
		m_Threshold(value ? 1 : 0)
	{ }

	bool AnimationTransition::evaluate(float value)
	{
		switch (m_Condition) {
		case Equal:		return value == m_Threshold;
		case NotEqual:	return value != m_Threshold;
		case Greater:	return value > m_Threshold;
		case Less:		return value < m_Threshold;
		}
		return false;
	}

	void AnimationController::update(float delta)
	{
		m_States[m_CurrentState].update(delta);

		// TODO multiple in one frame

		for (auto &transition : m_Transitions) {
			if (m_CurrentState != transition.getSource())
				continue;

			float value = getValue(transition.getVariable());

			if (transition.evaluate(value)) {
				m_CurrentState = transition.getTarget(); 
				m_States[m_CurrentState].restart();
				break;
			}
		}
	}

	const Sprite & AnimationController::getCurrentSprite()
	{
		return m_States[m_CurrentState].getCurrentSprite();
	}

	void AnimationController::setState(std::string stateName, Animation animation)
	{
		m_States[stateName] = animation;
	}

	float AnimationController::getValue(const std::string & variable)
	{
		return m_Values[variable];
	}

	void AnimationController::setValue(const std::string & variable, float value)
	{
		m_Values[variable] = value;
	}

	void AnimationController::addTransition(AnimationTransition transition)
	{
		m_Transitions.push_back(std::move(transition));
	}

	void AnimationController::addTransition(std::string from, std::string to, std::string variable, bool value)
	{
		addTransition(AnimationTransition(from, to, variable, value));
	}

	void AnimationController::addTransition(std::string from, std::string to, std::string variable, AnimationTransition::Condition condition, float threshold)
	{
		addTransition(AnimationTransition(from, to, variable, condition, threshold));
	}
}
