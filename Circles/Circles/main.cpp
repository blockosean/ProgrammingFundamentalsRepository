/*
    Start shape drawing file
*/

#include <iostream>
#include "Framework.h"
#include <cstdlib>
#include "Circle.h"
#include <ctime>
#include <vector>

// Variables with global scope - do not rename them, feel free to change values though

// Screen dimensions
bool circleCD{false};

int gScreenWidth{800};
int gScreenHeight{600};

int minSpeed{ 1 };
int maxSpeed{ 10 };

// Delay to slow things down
int gTimeDelayMS{10};

using namespace std;

int main()
{
	srand(time(0));

	const int circleCount = 1;

	vector<Circle> circles;

	circles.resize(circleCount);

	cout << "Hello circles" << endl;


	while (UpdateFramework())
	{
		for (size_t i = 0; i < circles.size(); i++)
		{
			circles[i].Draw();
			circles[i].Update();
		}

		if (IsButtonPressed(EButton::eRight))
		{
			if (IsButtonPressed(EButton::eLeft) && circleCD == false)
			{
				cout << "Yea";
				Circle newCircle;

				circles.push_back(newCircle);
				circleCD = true;
			}
			else if (IsButtonPressed(EButton::eLeft) == false)
			{
				circleCD = false;
			}
		}
	}

	cout << "Bye bye" << endl;

	return 0;
}