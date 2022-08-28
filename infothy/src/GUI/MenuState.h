#pragma once

#include "State.h"

class MenuState : public State {
private:

public:

	MenuState();

	virtual ~MenuState() {}

	virtual void update(const float delta_time) override;

	virtual void render() override;

};