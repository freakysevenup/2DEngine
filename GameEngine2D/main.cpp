#include "TestGame.h"

int main(int argc, char** argv)
{
	TestGame g;
	g.SetWindowProperties("This is how to set up the window!", 500, 500, 0);
	g.Run();
	return 0;
}