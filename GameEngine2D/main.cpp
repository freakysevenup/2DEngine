#include "TestGame.h"

int main(int argc, char** argv)
{
	TestGame g;
	g.SetWindowProperties("First Window Redone", 500, 500, 0, 60.0f);
	g.Run();
	return 0;
}