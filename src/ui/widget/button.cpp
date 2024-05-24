#include "button.h"

Button::Button(SDL_Rect rect, const Context& ctx) {
	set_rect(rect);
	m_rect = get_rect();

	m_font = (TTF_Font*) sdl_check_ptr(
		TTF_OpenFont(ctx.font_path.c_str(), m_start_font_size)
	);
	o_font = (TTF_Font*) sdl_check_ptr(
		TTF_OpenFont(ctx.font_path.c_str(), m_start_font_size)
	);
	m_color = m_inactive_color;
}

Button::~Button() {
	TTF_CloseFont(m_font);
	TTF_CloseFont(o_font);
}

void Button::update_rect() {
	SDL_Rect rect = get_rect();
	if (m_rect.x != rect.x
		|| m_rect.y != rect.y
		|| m_rect.w != rect.w
		|| m_rect.h != rect.h
	) {
		m_rect = rect;
		update_font(m_rect.w);
	}
}

void Button::update_font(int32_t width) {
	int w, h;
	sdl_check(TTF_SizeText(o_font, m_text.c_str(), &w, &h));
	m_font_size = ((float) (width - 20) / w) * m_start_font_size;
	sdl_check(TTF_SetFontSize(m_font, m_font_size));
}

void Button::on_event(SDL_Event& event) {
	int32_t x, y;
	SDL_GetMouseState(&x, &y);

	SDL_Point p = { x, y };
	if (SDL_PointInRect(&p, &m_rect)) {
		m_active = true;
		m_color = m_active_color;
	} else {
		m_active = false;
		m_color = m_inactive_color;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		switch (event.button.button) {
			case SDL_BUTTON_LEFT: {
				if (m_active)
					on_click_callback();
			} break;
		}
	}
}

void Button::on_render(const Context& ctx) {
	update_rect();

	SDL_Rect r = m_rect;
	if (m_rel.x >= 0) {
		r.x = ctx.px + ctx.pwidth * (m_rel.x / 100.0);
	}
	if (m_rel.y >= 0) {
		r.y = ctx.py + ctx.pheight * (m_rel.y / 100.0);
	}
	if (m_rel.w >= 0) {
		r.w = ctx.pwidth * (m_rel.w / 100.0);
		update_font(r.w);
	}
	if (m_rel.h >= 0) {
		r.h = ctx.pheight * (m_rel.h / 100.0);
	}

	SDL_Surface* surface = (SDL_Surface*) sdl_check_ptr(
			TTF_RenderUTF8_Blended(m_font, m_text.c_str(), m_text_color
	));
	SDL_Texture* texture = (SDL_Texture*) sdl_check_ptr(
			SDL_CreateTextureFromSurface(ctx.renderer, surface
	));

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect font_r = {
		r.x + (r.w / 2 - w / 2), r.y + (r.h / 2 - h / 2), w, h
	};

	set_rect(r);
	m_rect = get_rect();

	SDL_SetRenderDrawColor(ctx.renderer, COLO_EXP(m_color));
	SDL_RenderFillRect(ctx.renderer, &m_rect);
	SDL_RenderCopy(ctx.renderer, texture, NULL, &font_r);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

Button& Button::on_click(std::function<void(void)> f) {
	on_click_callback = f;
	return *this;
}

Button& Button::set_text(const std::string& text) {
	if (o_text == text) return *this;

	m_text = text;
	o_text = m_text;

	update_font(m_rect.w);
	return *this;
}

Button& Button::set_color(SDL_Color active_color, SDL_Color inactive_color) {
	m_active_color = active_color;
	m_inactive_color = inactive_color;
	return *this;
}

Button& Button::set_text_color(SDL_Color color) {
	m_text_color = color;
	return *this;
}

Button& Button::set_position(int32_t x, int32_t y) {
	m_rect.x = x;
	m_rect.y = y;
	set_rect(m_rect);
	return *this;
}

Button& Button::set_dimension(int32_t w, int32_t h) {
	m_rect.w = w;
	m_rect.h = h;
	set_rect(m_rect);
	return *this;
}

Button& Button::set_rel_position(int32_t x, int32_t y) {
	m_rel.x = x;
	m_rel.y = y;
	return *this;
}

Button& Button::set_rel_dimension(int32_t w, int32_t h) {
	m_rel.w = w;
	m_rel.h = h;
	return *this;
}
