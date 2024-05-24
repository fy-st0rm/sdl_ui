#pragma once

#include "SDL2/SDL.h"
#include <iostream>
#include "app/context.h"

struct Padding {
	int32_t left, right, top, bottom, between;
};

class Widget {
public:
	virtual void on_event(SDL_Event& event) {}
	virtual void on_render(const Context& ctx) {}

	void set_rect(SDL_Rect rect) {
		m_rect = rect;
	}
	inline SDL_Rect get_rect() {
		return m_rect;
	}

private:
	SDL_Rect m_rect;
};
