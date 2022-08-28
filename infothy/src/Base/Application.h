#pragma once

#include <stack>
#include <string>
#include <memory>

#include "../GUI/MenuState.h"

class Application {
private:

	std::stack<std::unique_ptr<State>> _states;


	const int _screen_width = 1024;
	const int _screen_height = 860;

	bool _shouldQuit;

	// Keep the application running	
	void loop();

	void update(const float dt);

	void render();

public:

	Application();

	~Application();

	void run() { loop(); };

	void quit() { _shouldQuit = true; }

};