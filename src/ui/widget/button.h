#pragma once

#include <functional>
#include "SDL2/SDL_ttf.h"
#include "widget.h"
#include "utils.h"

class Button : public Widget {
public:
	Button(SDL_Rect rect, const Context& ctx);
	~Button();

	void on_event(SDL_Event& event);
	void on_render(const Context& ctx);

	Button& on_click(std::function<void(void)> f);
	Button& set_text(const std::string& text);
	Button& set_color(SDL_Color active_color, SDL_Color inactive_color);
	Button& set_text_color(SDL_Color color);
	Button& set_position(int32_t x, int32_t y);
	Button& set_dimension(int32_t w, int32_t h);
	Button& set_rel_position(int32_t x, int32_t y);
	Button& set_rel_dimension(int32_t w, int32_t h);

private:
	void update_rect();
	void update_font(int32_t width);

private:
	bool m_active = false;
	std::string m_text = "Button";
	std::string o_text = m_text;

	SDL_Rect m_rect;
	SDL_Rect m_rel = { -1, -1, -1, -1 };
	SDL_Color m_active_color = { 125, 125, 125, 255 };
	SDL_Color m_inactive_color = { 165, 165, 165, 255 };
	SDL_Color m_color;
	SDL_Color m_text_color = { 0, 0, 0, 255 };

	TTF_Font* m_font;
	TTF_Font* o_font;
	int32_t m_font_size, m_start_font_size = 10;

	std::function<void(void)> on_click_callback;
};
