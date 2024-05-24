#pragma once

#include <vector>
#include "SDL2/SDL_ttf.h"
#include "app/context.h"
#include "widget.h"
#include "utils.h"

class Column : public Widget {
public:
	Column(SDL_Rect rect);
	~Column();

	void on_event(SDL_Event& event);
	void on_render(const Context& ctx);

	Column& set_background(SDL_Color color);
	Column& set_rel_position(int32_t rel_x, int32_t rel_y);
	Column& set_rel_dimension(int32_t rel_w, int32_t rel_h);
	Column& set_padding(Padding padd);
	Column& add_widgets(std::vector<Widget*> widgets);

private:
	SDL_Color m_bg = { 165, 165, 165, 255 };
	std::vector<Widget*> m_widgets;
	SDL_Rect m_rect;
	SDL_Rect m_rel = { -1, -1, -1, -1 };
	Padding m_padd = { 0, 0, 0, 0 };
};


