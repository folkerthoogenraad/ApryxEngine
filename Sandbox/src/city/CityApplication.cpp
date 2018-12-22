#include "CityApplication.h"

#include "BSP2.h"
#include "math/Line2.h"
#include "math/math.h"

#include <queue>
#include <ctime>

namespace apryx {

	static float random_f() {
		return rand() / (float)RAND_MAX;
	}

	void CityApplication::init(std::shared_ptr<Context> context)
	{
		Application::init(context);
		setAutomaticRedraw(false);

		srand(1200);

		
	}

	void CityApplication::doStuff() {
		generations++;
		lines.clear();

		BSP2f bsp(Line2f(
			Vector2f(0, 0),
			Vector2f::angled(random_f() * PI * 2)
		));

		// Filling the BSP
		{
			std::queue<BSP2f*> queue;

			queue.push(&bsp);

			for (int i = 0; i < 500; i++) {
				BSP2f *current = queue.front();
				queue.pop();

				Line2f line = current->line;

				const float distance = 30;

				float amountFront = random_f() * distance + distance;
				float amountBack = random_f() * distance + distance;

				const float randomness = 0;

				float angleOffsetFront = random_f() * randomness - randomness / 2;
				float angleOffsetBack = random_f() * randomness - randomness / 2;

				//angleOffsetFront = random_f() > 0.5 ? randomness : -randomness;
				//angleOffsetBack = random_f() > 0.5 ? randomness : -randomness;

				Vector2f directionFront = Vector2f::angled(line.direction.angle() + PI / 2 + angleOffsetFront);
				Vector2f directionBack = Vector2f::angled(line.direction.angle() - PI / 2 + angleOffsetBack);

				

				// Inserting the front
				current->insertFrontRaw(Line2f(
					line.position + directionFront + line.direction * amountFront,
					directionFront
				));

				// Inserting the back
				current->insertBackRaw(Line2f(
					line.position + directionBack + line.direction * amountBack,
					directionBack
				));


				queue.push(current->front.get());
				queue.push(current->back.get());
			}
		}

		// Generating lines
		{
			bsp.forEach([&](BSP2f *node) {
				float min = -1000;
				float max = 1000;

				BSP2f *previousParent = node;
				BSP2f *parent = node->parent;

				bool genLine = true;

				while (parent != nullptr) {
					// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
					Vector2f p = node->line.position;
					Vector2f r = node->line.direction;
					Vector2f q = parent->line.position;
					Vector2f s = parent->line.direction;

					float dir = -1;

					if (parent->back.get() == previousParent)
						dir = 1;

					float div = Vector2f::cross(r, s);

					if (div != 0) {
						float t = Vector2f::cross((q - p), s) / div;

						float distanceToMin = parent->line.distanceFrom(p + min * r) * dir;
						float distanceToMax = parent->line.distanceFrom(p + max * r) * dir;

						if (distanceToMin < 0 && distanceToMax < 0) {
							genLine = false;
						}
						else if (distanceToMin < 0) {
							min = apryx::max_t(t, min);
						}
						else if (distanceToMax < 0) {
							max = apryx::min_t(t, max);
						}						
					}
					else {
						if (parent->line.distanceFrom(p) * dir < 0)
							genLine = false;
					}


					previousParent = parent;
					parent = parent->parent;
				}

				if (genLine && min < max) {
					lines.push_back(LineSegment2f(
						node->line.position + node->line.direction * min,
						node->line.position + node->line.direction * max
					));
				}
			});
		}
	}

	void CityApplication::draw(Graphics2D & graphics)
	{
		Application::draw(graphics);

		graphics.drawClear(Color32::white());

		graphics.save();
		graphics.translate(Vector2f(graphics.getWidth() / 2, graphics.getHeight() / 2));

		Paint paint(Color32::blue());
		paint.setStrokeWidth(2);

		for (auto &line : lines) {
			graphics.drawLine(paint, line.a, line.b);
		}

		graphics.restore();
	}

	void CityApplication::update()
	{
		if (getContext().getWindow()->isResized()) {
			redraw();
		}

		if(getContext().input.isKeyPressed(KEY_SPACE)){
			doStuff();
			redraw();
		}
	}

	void CityApplication::destroy()
	{

	}
}