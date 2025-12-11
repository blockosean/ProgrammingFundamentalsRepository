#pragma once
class Circle
{
public:
	Circle();
	void ChangeDir();
	void Draw();
	void Update();
	char GetRed();
	char GetGreen();
	char GetBlue();
private:
	char r;
	char g;
	char b;
	int x;
	int y;
	int xDir;
	float yDir;
	int size;
};

