#pragma once

#include "State.h"

class MenuState : public State {
private:

	AssetManager<Font>* _fontManager;

	void initResources();

public:

	MenuState();

	virtual ~MenuState() {}

	virtual void update(const float delta_time) override;

	virtual void render() override;

};