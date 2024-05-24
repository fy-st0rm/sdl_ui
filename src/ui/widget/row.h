#pragma once

#include <vector>
#include "SDL2/SDL_ttf.h"
#include "app/context.h"
#include "widget.h"
#include "utils.h"

class Row : public Widget {
public:
	Row(SDL_Rect rect);
	~Row();

	void on_event(SDL_Event& event);
	void on_render(const Context& ctx);

	Row& set_background(SDL_Color color);
	Row& set_rel_position(int32_t rel_x, int32_t rel_y);
	Row& set_rel_dimension(int32_t rel_w, int32_t rel_h);
	Row& set_padding(Padding padd);
	Row& add_widgets(std::vector<Widget*> widgets);

private:
	SDL_Color m_bg = { 165, 165, 165, 255 };
	std::vector<Widget*> m_widgets;
	SDL_Rect m_rect;
	SDL_Rect m_rel = { -1, -1, -1, -1 };
	Padding m_padd = { 0, 0, 0, 0 };
};


