#include "Application.h"


Application::Application() : _shouldQuit{false}
{
	
}

Application::~Application()
{
	// Clear all states
	while (!_states.empty()) {
		_states.pop();
	}
}

void Application::loop()
{

	InitWindow(_screen_width, _screen_height, "inf0thy");

	SetTargetFPS(60);

	_states.push(std::make_unique<MenuState>());

	while (!WindowShouldClose() && !_shouldQuit) {

		update(GetFrameTime());
		render();

	}

}

void Application::update(const float dt)
{
	if (!_states.empty()) {

		_states.top()->update(dt);

		if (_states.top()->getEndState() == true) {
			// Quit current state
			_states.pop();
		}
	}
	else {
		// No more virtual states. Quit the application
		quit();
	}
}

void Application::render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (!_states.empty())
		_states.top()->render();


	DrawFPS(10, 10);

	EndDrawing();

}


