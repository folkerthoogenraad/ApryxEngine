#pragma once

#include <assert.h>

#include "resources/Context.h"

namespace apryx {

	class Application {
	protected:
		std::shared_ptr<Context> m_Context;
		bool m_Redraw = true;
		bool m_AutomaticRedraw = true;
	public:
		virtual void init(std::shared_ptr<Context> context) { assert(context != nullptr); m_Context = context; };
		virtual void draw(Graphics2D &graphics) { m_Redraw = m_AutomaticRedraw; };
		virtual void update() { };
		virtual void destroy() { };

		void redraw() { m_Redraw = true; }
		void setAutomaticRedraw(bool redraw) { m_AutomaticRedraw = redraw; }

		virtual bool shouldRedraw() { return m_Redraw; };
		virtual bool shouldQuit() { return m_Context->getWindow()->isCloseRequested(); }

		Context &getContext() { return *m_Context; }
		const Context &getContext() const { return *m_Context; }
	};

}