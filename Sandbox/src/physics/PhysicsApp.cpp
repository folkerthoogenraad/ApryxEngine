#include "PhysicsApp.h"

namespace apryx {

	static float random_f() {
		return rand() / (float)RAND_MAX;
	}

	static float random_range(float min, float max) {
		return random_f() * (max - min) + min;
	}


	void PhysicsApp::init(std::shared_ptr<Context> context)
	{
		Application::init(context);
		
		
		for (int i = 0; i < 100; i++) {
			Entity e = m_System.createEntity();
			Ball *b = m_System.addComponent<Ball>(e);
			
			b->position = Vector2f(
				random_range(-1, 1),
				random_range(-1, 1)
			);
			b->radius = 1;
		}
	}

	void PhysicsApp::draw(Graphics2D & graphics)
	{
		graphics.save();

		float aspect = graphics.getWidth() / graphics.getHeight();

		graphics.setMatrix(
			Matrix4f::orthographic(-10 * aspect, 10 * aspect, 10, -10, -10, 10)
		);

		graphics.drawClear(Color32::black());

		Paint outline = Paint(Color32::white());
		outline.setStyle(Paint::Stroke);
		outline.setStrokeWidth(0.1f);

		m_System.process<Ball>([&](Entity e, Ball &b) {
			graphics.drawCircle(outline, b.position, b.radius);
		});

		graphics.restore();
	}

	void PhysicsApp::update()
	{
		static bool animate = false;

		if (m_Context->input.isKeyPressed(KEY_SPACE))
			animate = true;

		if (animate) {
			m_System.process<Ball>([&](Entity e1, Ball &ball) {

				m_System.process<Ball>([&](Entity e2, Ball &other) {
					// Same object collision
					if (e1.id == e2.id)
						return;

					float distance = (ball.position - other.position).magnitude();

					float overlap = -(distance - ball.radius - other.radius);

					if (overlap < 0)
						return;

					// Direction from ball to other
					Vector2f direction = (other.position - ball.position);

					if (direction.sqrmagnitude() == 0) {
						direction = Vector2f(1, 0);
					}
					else {
						direction.normalize();
					}

					ball.position -= direction * (overlap / 2);
					other.position += direction * (overlap / 2);
				});

			});
		}
	}

	void PhysicsApp::destroy()
	{
	}

}
