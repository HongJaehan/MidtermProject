#pragma once

class CVector
{
public:
	CVector();
	~CVector();
	CVector(float, float);

	void SetX(float);
	float GetX();
	void SetY(float);
	float GetY();
	void SetXY(float, float);
	CVector& GetXY();

	CVector operator+(const CVector&);
	CVector operator-(const CVector&);
	void operator=(const CVector&);

private:
	float x;
	float y;
};

