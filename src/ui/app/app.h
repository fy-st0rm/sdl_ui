#pragma once

#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "utils.h"
#include "page/page.h"
#include "context.h"

class Application {
public:
	virtual void on_attach() {}
	void run(const std::string& title, uint32_t width, uint32_t height);
	void set_background(SDL_Color color);
	void set_font(const std::string& font_path);

	template<typename T>
	void add_page(const std::string& name) {
		m_pages.insert({name, std::make_shared<T>(m_ctx)});
		m_curr_page = name;
	}

	void goto_page(const std::string& name) {
		std::stringstream ss;
		ss << "Cannot find page with name: " << name;
		assert(
			m_pages.find(name) != m_pages.end(),
			ss.str()
		);

		m_curr_page = name;
	}

private:
	void init();
	void clear();
	void loop();

private:
	std::string m_title;
	uint32_t m_width, m_height;
	bool m_running = true;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Context m_ctx;

	SDL_Color m_bg = { 0, 0, 0, 255 };

	std::unordered_map<
		std::string,
		std::shared_ptr<Page>
	> m_pages;
	std::string m_curr_page = "";
};
