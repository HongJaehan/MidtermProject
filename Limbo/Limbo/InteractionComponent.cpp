#include "pch.h"
#include "InteractionComponent.h"

InteractionComponent::InteractionComponent()
{
}

InteractionComponent::InteractionComponent(int _x, int _y, int _disX, int _disY)
{
	x = _x;
	y = _y;
	interactionDistanceX = _disX;
	interactionDistanceY = _disY;
}

InteractionComponent::~InteractionComponent()
{
}

int InteractionComponent::GetInteractionDisX()
{
	return interactionDistanceX;
}

int InteractionComponent::GetInteractionDisY()
{
	return interactionDistanceY;

}

void InteractionComponent::SetX(int _x)
{
	x = _x;
}

void InteractionComponent::SetY(int _y)
{
	y = _y;
}

int InteractionComponent::GetX()
{
	return x;
}

int InteractionComponent::GetY()
{
	return y;
}
