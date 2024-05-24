#include "app.h"

void Application::run(const std::string& title, uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;
	m_title = title;

	m_ctx.width = width;
	m_ctx.height = height;

	init();
	on_attach();
	assert(!m_curr_page.empty(), "No pages added.");
	loop();
}

void Application::set_background(SDL_Color color) {
	m_bg = color;
}

void Application::set_font(const std::string& font_path) {
	m_ctx.font_path = font_path;
}

void Application::init() {
	assert(
		SDL_Init(SDL_INIT_EVERYTHING) >= 0,
		"Failed to initialize SDL"
	);

	assert(
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) >= 0,
		"Failed to initialize SDL_image"
	);

	assert(
		TTF_Init() >= 0,
		"Failed to initialize SDL_ttf"
	);

	m_window = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_RESIZABLE
	);
	assert(m_window, "Failed to create window\n");

	m_renderer = SDL_CreateRenderer(
		m_window, -1, SDL_RENDERER_ACCELERATED
	);
	assert(m_renderer, "Failed to create renderer\n");

	m_ctx.renderer = m_renderer;
}

void Application::clear() {
	SDL_RenderPresent(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, COLO_EXP(m_bg));
	SDL_RenderClear(m_renderer);
}

void Application::loop() {
	while (m_running) {
		clear();

		auto page = m_pages[m_curr_page];
		auto widget = page->build();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			widget->on_event(event);
			if (event.type == SDL_QUIT) {
				m_running = false;
				break;
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					m_width = event.window.data1;
					m_height = event.window.data2;
					m_ctx.width = m_width;
					m_ctx.height = m_height;
				}
			}
		}

		m_ctx.px = 0;
		m_ctx.py = 0;
		m_ctx.pwidth = m_width;
		m_ctx.pheight = m_height;
		widget->on_render(m_ctx);
	}
}
