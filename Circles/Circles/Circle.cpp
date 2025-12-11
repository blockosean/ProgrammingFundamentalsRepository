#include "Circle.h"
#include <cstdlib>
#include <iostream>
#include "Framework.h"

extern int minSpeed;
extern int maxSpeed;
extern int gScreenWidth;
extern int gScreenHeight;

using namespace std;

Circle::Circle()
{
	size = (rand() % 10) + 10;
	x = 0 + rand() % (gScreenWidth - (size * 2) + 1);
	y = 0 + rand() % (gScreenHeight - (size * 2) + 1);
	xDir = minSpeed + rand() % (maxSpeed - minSpeed + 1);
	yDir = minSpeed + rand() % (maxSpeed - minSpeed + 1);
	r = rand() % 255; g = rand() % 255; b = rand() % 255;
	//colour[0] = 255; colour[1] = 0; colour[2] = 0;
}

void Circle::ChangeDir()
{
	xDir = minSpeed + rand() % (maxSpeed - minSpeed + 1);
	yDir = minSpeed + rand() % (maxSpeed - minSpeed + 1);
}

void Circle::Draw()
{
	DrawCircle(x, y, size);
	ChangeColour(GetRed(), GetGreen(), GetBlue());
}

void Circle::Update()
{

	x += xDir;
	y += yDir;

	if (x > gScreenWidth - size * 2 || x < 0)
	{
		xDir = -xDir;

	}

	if (y > gScreenHeight - size * 2 || y < 0)
	{
		yDir = -yDir;
	}

	if (rand() % 100 == 1)
	{
		ChangeDir();
	}

	if (IsButtonPressed(EButton::eRight) == false && IsButtonPressed(EButton::eLeft))
	{
		int mouseX; int mouseY;
		GetMousePosition(mouseX, mouseY);
		x = mouseX - size;
		y = mouseY - size;
	}
}

char Circle::GetRed()
{
	return r;
}
char Circle::GetGreen()
{
	return g;
}
char Circle::GetBlue()
{
	return b;
}
