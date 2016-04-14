#include "TestGame.h"

int main(int argc, char** argv)
{
	TestGame g;
	g.SetWindowProperties("This is the 2D Engine", 500, 500, 0);
	g.Run();
	return 0;
}