#pragma once

#include <unordered_map>
#include <sstream>
#include <memory>
#include "SDL2/SDL.h"
#include "page/page.h"
#include "utils.h"

class Switch : public Widget {
public:
	Switch(SDL_Rect rect, const Context& ctx);
	~Switch();

	void on_event(SDL_Event& event);
	void on_render(const Context& ctx);

	Switch& set_background(SDL_Color color);
	Switch& set_rel_position(int32_t rel_x, int32_t rel_y);
	Switch& set_rel_dimension(int32_t rel_w, int32_t rel_h);

	template<typename T>
	Switch& add_page(const std::string& name) {
		m_pages.insert({name, std::make_shared<T>(m_ctx)});
		m_curr = name;
		return *this;
	}
	Switch& goto_page(std::string name);

private:
	Context m_ctx;
	SDL_Rect m_rect;
	SDL_Rect m_rel = { -1, -1, -1, -1 };
	SDL_Color m_bg = { 165, 165, 165, 255 };
	std::unordered_map<std::string, std::shared_ptr<Page>> m_pages;
	std::string m_curr;
};
