#include "switch.h"

Switch::Switch(SDL_Rect rect, const Context& ctx) {
	m_ctx = ctx;
	set_rect(rect);
	m_rect = get_rect();
}

Switch::~Switch() {
}

void Switch::on_event(SDL_Event& event) {
	if (m_curr.empty()) return;

	auto page = m_pages[m_curr];
	Widget* widget = page->build();
	widget->on_event(event);
}

void Switch::on_render(const Context& ctx) {
	m_rect = get_rect();

	SDL_Rect r = m_rect;
	if (m_rel.x >= 0) {
		r.x = ctx.px + ctx.pwidth * (m_rel.x / 100.0);
	}
	if (m_rel.y >= 0) {
		r.y = ctx.py + ctx.pheight * (m_rel.y / 100.0);
	}
	if (m_rel.w >= 0) {
		r.w = ctx.pwidth * (m_rel.w / 100.0);
	}
	if (m_rel.h >= 0) {
		r.h = ctx.pheight * (m_rel.h / 100.0);
	}

	set_rect(r);
	m_rect = get_rect();

	SDL_SetRenderDrawColor(ctx.renderer, COLO_EXP(m_bg));
	SDL_RenderFillRect(ctx.renderer, &m_rect);

	if (m_curr.empty()) return;

	m_ctx.px = r.x;
	m_ctx.py = r.y;
	m_ctx.pwidth = r.w;
	m_ctx.pheight = r.h;

	auto page = m_pages[m_curr];
	Widget* widget = page->build();
	widget->on_render(m_ctx);
}

Switch& Switch::set_background(SDL_Color color) {
	m_bg = color;
	return *this;
}

Switch& Switch::set_rel_position(int32_t rel_x, int32_t rel_y) {
	m_rel.x = rel_x;
	m_rel.y = rel_y;
	return *this;
}

Switch& Switch::set_rel_dimension(int32_t rel_w, int32_t rel_h) {
	m_rel.w = rel_w;
	m_rel.h = rel_h;
	return *this;
}

Switch& Switch::goto_page(std::string name) {
	std::stringstream ss;
	ss << "Cannot find page with name: " << name;
	assert(
		m_pages.find(name) != m_pages.end(),
		ss.str()
	);

	m_curr = name;
	return *this;
}

