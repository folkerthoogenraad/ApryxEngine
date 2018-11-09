#pragma once

#include <assert.h>

#include "resources/Context.h"

namespace apryx {

	class Application {
	protected:
		std::shared_ptr<Context> m_Context;
	public:
		virtual void init(std::shared_ptr<Context> context) { assert(context != nullptr); m_Context = context; };
		virtual void draw(Graphics2D &graphics) { };
		virtual void update() { };
		virtual void destroy() { };

		virtual bool shouldRedraw() { return true; };
		virtual bool shouldQuit() { return m_Context->getWindow()->isCloseRequested(); }

		Context &getContext() { return *m_Context; }
		const Context &getContext() const { return *m_Context; }
	};

}