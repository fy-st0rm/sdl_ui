#include "row.h"

Row::Row(SDL_Rect rect) {
	set_rect(rect);
	m_rect = get_rect();
}

Row::~Row() {
}

void Row::on_event(SDL_Event& event) {
	for (auto widget : m_widgets) {
		widget->on_event(event);
	}
}

void Row::on_render(const Context& ctx) {
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

	Context c = ctx;
	c.px = r.x;
	c.py = r.y;
	c.pwidth = r.w;
	c.pheight = r.h;

	// Rendering childrens
	int32_t n = m_widgets.size();
	int32_t ch = (r.h - m_padd.top - m_padd.bottom - (m_padd.top * (n - 1))) / n;
	int i = 0;

	Widget* ow = nullptr;
	for (auto widget : m_widgets) {
		SDL_Rect wr;
		if (ow) {
			SDL_Rect owr = ow->get_rect();
			wr = {
				r.x + m_padd.left,
				owr.y + owr.h + m_padd.top,
				r.w - (m_padd.right * 2),
				ch
			};
		} else {
			wr = {
				r.x + m_padd.left,
				r.y + i * ch + m_padd.top * (i + 1),
				r.w - (m_padd.right * 2),
				ch
			};
		}
		widget->set_rect(wr);
		widget->on_render(c);
		ow = widget;
		i++;
	}
}

Row& Row::set_background(SDL_Color color) {
	m_bg = color;
	return *this;
}

Row& Row::set_rel_position(int32_t rel_x, int32_t rel_y) {
	m_rel.x = rel_x;
	m_rel.y = rel_y;
	return *this;
}

Row& Row::set_rel_dimension(int32_t rel_w, int32_t rel_h) {
	m_rel.w = rel_w;
	m_rel.h = rel_h;
	return *this;
}

Row& Row::set_padding(Padding padd) {
	m_padd = padd;
	return *this;
}

Row& Row::add_widgets(std::vector<Widget*> widgets) {
	m_widgets.insert(m_widgets.end(), widgets.begin(), widgets.end());
	return *this;
}

