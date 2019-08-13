#pragma once
#include "ControlComponent.h"

class Player;

class PlayerControlComponent :
	public ControlComponent
{
public:
	PlayerControlComponent();
	~PlayerControlComponent();
	void Update(Player&);
private:
};
