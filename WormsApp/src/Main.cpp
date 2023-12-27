#include "Spoon.h"
#include "Levels/WormLevel.h"
#include "Config.h"

class App : public Application
{
	public : 
		App() : Application("Spoon", FVector2D(Config::WindowWidth, Config::WindowHeight))
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