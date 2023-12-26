#include "Spoon.h"
#include "Levels/WormLevel.h"

class App : public Application
{
	public : 
		App() : Application("Spoon", FVector2D(1280, 720))
		{
			SetLevel(new WormLevel());
		}
};

Application* CreateApplication()
{
	return new App();
}

int main()
{
	Application* app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}