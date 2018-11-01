#pragma once

#include <map>
#include <vector>
#include <string>

#include "Animation.h"
#include "Sprite.h"

namespace apryx {


	//TODO checks everywhere
	class AnimationTransition {
	public:
		enum Condition{
			Equal,
			NotEqual,
			Greater,
			Less
		};
	private:
		std::string m_From;
		std::string m_To;

		std::string m_Variable;

		Condition m_Condition;
		float m_Threshold;
	public:
		AnimationTransition(std::string from, std::string to, std::string variable, Condition condition, float threshold);
		AnimationTransition(std::string from, std::string to, std::string variable, bool value);

		bool evaluate(bool value) { evaluate(value ? 1.0f : 0.0f); }
		bool evaluate(float value);

		const std::string &getSource() const { return m_From; }
		const std::string &getTarget() const { return m_To; }
		const std::string &getVariable() const { return m_Variable; }
	};

	class AnimationController {
		std::map<std::string, Animation> m_States;
		std::vector<AnimationTransition> m_Transitions;

		std::map<std::string, float> m_Values;

		std::string m_CurrentState;
	public:
		void update(float delta);

		const Sprite &getCurrentSprite();

		void setCurrentState(std::string state) { m_CurrentState = state; }
		void setState(std::string stateName, Animation animation);

		float getValue(const std::string &variable);
		void setValue(const std::string &variable, float value);
		void setValue(const std::string &variable, bool value) { setValue(variable, value ? 1.0f : 0.0f);}

		void addTransition(AnimationTransition transition);
		void addTransition(std::string from, std::string to, std::string variable, bool value);
		void addTransition(std::string from, std::string to, std::string variable, AnimationTransition::Condition condition, float threshold);
	};

}