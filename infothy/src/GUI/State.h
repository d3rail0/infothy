#pragma once

#include "../Base/AssetManager.h"
#include "raylib/raygui.h" // Required for GUI controls

class State {
private:
	bool _endState;
protected:
		
	State() : _endState{false} {}

public:

	virtual ~State() {}

	virtual void update(const float delta_time) = 0;

	virtual void render() = 0;

	bool getEndState() const noexcept { return _endState; }
	void quit() noexcept { _endState = true; }

};