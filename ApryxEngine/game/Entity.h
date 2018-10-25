#pragma once

namespace apryx {

	class Scene;

	class Entity{
		Scene *m_Scene;
	public:
		void setScene(Scene *scene) { m_Scene = scene; }
		Scene *getScene() { return m_Scene; }
	};

}