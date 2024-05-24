#pragma once

#include <source_location>
#include <iostream>
#include "SDL2/SDL.h"

#define COLO_EXP(c) (c).r, (c).g, (c).b, (c).a

static int sdl_check(
	int result,
	const std::source_location location = std::source_location::current()
) {
	if (result < 0) {
		std::cerr << "[SDL_ERROR]: "
		          << location.file_name() << ":"
		          << location.line() << ":"
		          << location.column() << ": "
		          << SDL_GetError() << std::endl;
		exit(1);
	}
	return result;
}

static void* sdl_check_ptr(
	void* result,
	const std::source_location location = std::source_location::current()
) {
	if (!result) {
		std::cerr << "[SDL_PTR_ERROR]: "
		          << location.file_name() << ":"
		          << location.line() << ":"
		          << location.column() << ": "
		          << SDL_GetError() << std::endl;
		exit(1);
	}
	return result;
}

static void assert(
	bool condition,
	const std::string& log,
	const std::source_location location = std::source_location::current()
) {
	if (condition) return;

	std::cerr << "[ASSERTION]: "
	          << location.file_name() << ":"
	          << location.line() << ":"
	          << location.column() << ": "
	          << log << std::endl;
	exit(1);
}

static float pix_to_points(int pix) {
	assert(pix >= 8, "Pixel size should not be less than 8");
	return (pix - 8) * 0.75f + 6.0f;
}

