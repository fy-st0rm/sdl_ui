#define CBUILD_IMPLEMENTATION
#include "cbuild.h"

// Copy all dll to one spot

int main(int argc, char** argv) {
	cbuild_rebuild(argc, argv);
	CBuild cbuild("g++");
	cbuild
		.out("bin", "main")
		.flags({
			"-std=c++20"
		})
		.inc_paths({
			"SDL2_64bit/include",
			"src/ui",
			"src"
		})
		.lib_paths({
			"SDL2_64bit/lib/linux"
		})
		.libs({
			"SDL2",
			"SDL2_image",
			"SDL2_ttf"
		})
		.src({
			"src/ui/widget/button.cpp",
			"src/ui/widget/switch.cpp",
			"src/ui/widget/row.cpp",
			"src/ui/widget/column.cpp",
			"src/ui/page/page.cpp",
			"src/ui/app/app.cpp",
			"src/main.cpp"
		})
		.build()
		.clean()
		.run();
	return 0;
}
