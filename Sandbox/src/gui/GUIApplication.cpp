#include "GUIApplication.h"

#include "ui/LinearLayout.h"
#include "ui/Label.h"
#include "ui/Button.h"
#include "ui/TextField.h"

namespace apryx {

	void GUIApplication::init(std::shared_ptr<Context> context)
	{
		Application::init(context);
		setAutomaticRedraw(false);

		ApryxUIStyle style;

		float dpi = m_Context->getWindow()->dpiScale();
		
		style.textFont = context->loadFont("fonts/OpenSans.ttf", (int) (16 * dpi));
		style.componentFont = context->loadFont("fonts/Exo2.ttf", (int) (16 * dpi));

		style.textFont->scale(1.0f / dpi);
		style.componentFont->scale(1.0f / dpi);

		ui.setStyle(style);

		ui.init(context);

		LayoutParams params;
		params.m_WidthScaling = LayoutParams::MatchParent;

		auto layout = std::make_shared<LinearLayout>(LinearLayout::Horizontal);
		layout->addComponent(std::make_shared<Button>("Submit"));
		layout->addComponent(std::make_shared<Button>("Cancel", Button::Secondary));

		auto label1 = std::make_shared<TextField>("Username ...");

		label1->setLayoutParams(params);

		layout->addComponent(label1);
		layout->addComponent(std::make_shared<Label>("There is some extra information text here."));

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
		ui.processEvents(m_Context->input.getEvents());

		if (ui.shouldRedraw())
			redraw();
	}

	void GUIApplication::destroy()
	{

	}


}
