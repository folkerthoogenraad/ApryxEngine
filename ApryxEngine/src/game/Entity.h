#pragma once

#include "Scene.h"

#include "resources/Context.h"
#include "graphics/Graphics2D.h"

#include <optional>

namespace apryx {

	struct EntityState {
		Scene2D &scene;
		Context &context;
		InputManager &input;
	};

	class Entity2D {
	protected:
		Scene2D *m_Scene;
	public:
		Vector2f position;
	protected:
		Vector2f previousPosition;
	public:
		virtual void init(Scene2D *m_Scene) {};
		virtual void update() {};
		virtual void draw(Graphics2D &graphics) {};

		virtual std::optional<Rectanglef> getBoundingBox() const { return std::nullopt; };

		void setScene(Scene2D* scene) { m_Scene = scene; }
		Scene2D *getScene() { return m_Scene; }


		void preUpdate();

		EntityState getState();

		Vector2f getDrawPosition() const;
	};


}