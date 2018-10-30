#pragma once

#include "Scene.h"

#include "graphics/Graphics2D.h"

#include <optional>

namespace apryx {

	class Entity {
	protected:
		Scene *m_Scene;
	public:
		virtual void init(Scene *m_Scene) {};
		virtual void update() {};
		virtual void draw(Graphics2D &graphics) {};

		virtual std::optional<Rectanglef> getBoundingBox() const { return std::nullopt; };

		void setScene(Scene* scene) { m_Scene = scene; }
		Scene *getScene() { return m_Scene; }

		static bool clipVector(Vector2f &motion, const Entity &first, const Entity &other);
	};


}