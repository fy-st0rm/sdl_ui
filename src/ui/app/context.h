#pragma once
#include <string>

struct Context {
	uint32_t width, height;
	uint32_t px, py, pwidth, pheight;
	std::string font_path = "assets/JetBrains.ttf";
	SDL_Renderer* renderer;
};

