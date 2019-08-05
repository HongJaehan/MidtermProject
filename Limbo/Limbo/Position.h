#pragma once
class Position
{
public:
	Position();
	~Position();
	Position(float, float);

	void SetX(float);
	float GetX();
	void SetY(float);
	float GetY();
	void SetXY(float, float);
	Position& GetXY();

	Position operator+(const Position&);
	Position operator-(const Position&);
	void operator=(const Position&);

private:
	float x;
	float y;
};

