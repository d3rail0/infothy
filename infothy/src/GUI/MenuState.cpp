#include "MenuState.h"

MenuState::MenuState()
{

	// Do initial setup

}

void MenuState::update(const float delta_time)
{
}

void MenuState::render()
{
	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
}
