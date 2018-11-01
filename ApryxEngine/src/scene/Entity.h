#pragma once

#include "Scene.h"

#include "graphics/Graphics2D.h"

#include <optional>

namespace apryx {

	struct EntityState {
		Scene &scene;
		Context &context;
		InputManager &input;
	};

	class Entity {
	protected:
		Scene *m_Scene;

	public:
		Vector2f position;

	protected:
		Vector2f previousPosition;
	public:
		virtual void init(Scene *m_Scene) {};
		virtual void update() {};
		virtual void draw(Graphics2D &graphics) {};

		virtual std::optional<Rectanglef> getBoundingBox() const { return std::nullopt; };

		void setScene(Scene* scene) { m_Scene = scene; }
		Scene *getScene() { return m_Scene; }


		void preUpdate();

		EntityState getState();

		Vector2f getDrawPosition() const;
	};


}