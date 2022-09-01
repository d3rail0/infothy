#include "MenuState.h"

void MenuState::initResources()
{
	_fontManager = AssetManager<Font>::getInstance(UnloadFont);
	_fontManager->load("default", LoadFontEx("./res/fonts/Roboto-Medium.ttf", 72, 0, NULL));

	GenTextureMipmaps(&_fontManager->get("default")->texture);
	SetTextureFilter(_fontManager->get("default")->texture, TEXTURE_FILTER_ANISOTROPIC_4X);
}

MenuState::MenuState()
{
	initResources();
}

void MenuState::update(const float delta_time)
{
}

void MenuState::render()
{
	DrawTextEx(*_fontManager->get("default"), "Congrats! You created your first window!", Vector2{ 190, 200 }, 36, 2, DARKGRAY);
	DrawText("Congrats! You created your first window!", 190, 300, 40, LIGHTGRAY);
}
