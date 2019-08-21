#pragma once
#include "Component.h"
class InteractionComponent :
	public Component
{
public:
	InteractionComponent();
	InteractionComponent(int _x,int _y, int _disX, int _disY);
	~InteractionComponent();
	int GetInteractionDisX();
	int GetInteractionDisY();
	void SetX(int _x);
	void SetY(int _y);
	int GetX();
	int GetY();

private:
	int interactionDistanceX;
	int interactionDistanceY;
	int x;
	int y;

};

