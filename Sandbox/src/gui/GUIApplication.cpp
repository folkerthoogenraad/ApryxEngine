#include "GUIApplication.h"

#include "ui/LinearLayout.h"
#include "ui/Label.h"
#include "ui/Button.h"

namespace apryx {

	void GUIApplication::init(std::shared_ptr<Context> context)
	{
		Application::init(context);
		setAutomaticRedraw(false);

		ApryxUIStyle style;

		style.textFont = context->loadFont("fonts/OpenSans.ttf", 16);
		style.componentFont = context->loadFont("fonts/Exo2.ttf", 16);

		style.textFont->scale(1.0f / context->getWindow()->dpiScale());
		style.componentFont->scale(1.0f / context->getWindow()->dpiScale());

		ui.setStyle(style);

		ui.init(context);

		LayoutParams params;
		params.m_HeightScaling = LayoutParams::MatchParent;

		auto layout = std::make_shared<LinearLayout>(LinearLayout::Horizontal);
		layout->addComponent(std::make_shared<Button>("Test123"));
		layout->addComponent(std::make_shared<Button>("Text321"));

		auto label1 = std::make_shared<Label>("text123");

		label1->setLayoutParams(params);

		layout->addComponent(label1);
		layout->addComponent(std::make_shared<Label>("Text321"));

		ui.setMainComponent(layout);
		ui.updateLayout(getContext().getWindow()->getWidth(), getContext().getWindow()->getHeight());
		redraw();
	}

	void GUIApplication::draw(Graphics2D & graphics)
	{
		Application::draw(graphics);

		ui.draw(graphics);
	}

	void GUIApplication::update()
	{
		ui.update();
	}

	void GUIApplication::destroy()
	{

	}


}
