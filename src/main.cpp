#include "ui/ui.h"

class OnGoingPage : public Page {
private:
	std::unique_ptr<Button> button;

public:
	OnGoingPage(const Context& ctx) {
		SDL_Rect r = {0};
		button = std::make_unique<Button>(r, ctx);
		button
			->set_text("On Going Thing")
			.set_rel_position(10, 10)
			.set_rel_dimension(20, 5)
			.on_click([]() {
				std::cout << "From On Going Page\n";
			});
	}

	Widget* build() {
		return button.get();
	}
};

class UpComingPage : public Page {
private:
	std::unique_ptr<Button> button;

public:
	UpComingPage(const Context& ctx) {
		SDL_Rect r = {0};
		button = std::make_unique<Button>(r, ctx);
		button
			->set_text("Up Coming Thing")
			.set_rel_position(10, 10)
			.set_rel_dimension(20, 5)
			.on_click([]() {
				std::cout << "From Up Coming Page\n";
			});
	}

	Widget* build() {
		return button.get();
	}
};

class Home : public Page {
private:
	std::unique_ptr<Button> on_going_button, up_coming_button;
	Button* selected_button;
	std::unique_ptr<Row> row;
	std::unique_ptr<Column> col;
	std::unique_ptr<Switch> sw;

public:
	Home(const Context& ctx) {
		SDL_Rect r = {0};
		on_going_button = std::make_unique<Button>(r, ctx);
		on_going_button
			->set_color({0, 125, 125, 255}, {0, 150, 150, 255})
			.set_text("On Going")
			.set_text_color({255, 255, 255, 255})
			.set_rel_dimension(-1, 20)
			.on_click([=]() {
				selected_button->set_color(
					{0, 125, 125, 255}, {0, 150, 150, 255}
				);
				selected_button = on_going_button.get();
				sw->goto_page("OnGoingPage");
			});

		up_coming_button = std::make_unique<Button>(r, ctx);
		up_coming_button
			->set_color({0, 125, 125, 255}, {0, 150, 150, 255})
			.set_text("Up Coming")
			.set_text_color({255, 255, 255, 255})
			.set_rel_dimension(-1, 20)
			.on_click([=]() {
				selected_button->set_color(
					{0, 125, 125, 255}, {0, 150, 150, 255}
				);
				selected_button = up_coming_button.get();
				sw->goto_page("UpComingPage");
			});

		selected_button = on_going_button.get();

		SDL_Rect rr = {
			0, 0, 100, 600
		};
		row = std::make_unique<Row>(rr);
		row
			->set_rel_position(0, 0)
			.set_rel_dimension(10, 100)
			.set_padding({10, 10, 10, 10})
			.set_background({255, 0, 0, 255})
			.add_widgets({
				on_going_button.get(),
				up_coming_button.get()
			});

		SDL_Rect rs = {
			200, 200, 500, 500
		};
		sw = std::make_unique<Switch>(rs, ctx);
		sw
			->set_background({255, 0, 0, 255})
			.set_rel_position(10, 0)
			.set_rel_dimension(90, 100)
			.add_page<OnGoingPage>("OnGoingPage")
			.add_page<UpComingPage>("UpComingPage")
			.goto_page("OnGoingPage");

		SDL_Rect rc = { 0 };
		col = std::make_unique<Column>(rs);
		col
			->set_rel_position(0, 0)
			.set_rel_dimension(100, 100)
			.set_padding({10, 10, 10, 10})
			.add_widgets({
				row.get(),
				sw.get()
			});
	}

	Widget* build() {
		selected_button->set_color(
			{0, 125, 125, 255},
			{0, 100, 100, 255}
		);
		return col.get();
	}
};

class App : public Application {
public:
	void on_attach() {
		set_background({0, 100, 100, 255});
		add_page<Home>("Home");
	}
};

int main() {
	App app;
	app.run("App", 800, 600);
	return 0;
}
