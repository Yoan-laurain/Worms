#include "Levels/WormLevel.h"
#include "Config.h"
#include <Spoon.h>
#include <Renders/SFML/SfmlWindow.h>

class App : public Application
{
	public : 
		App() : Application("Spoon", FVector2D(Config::WindowWidth, Config::WindowHeight))
		{
			SetLevel(new WormLevel());

			SfmlWindow* window = dynamic_cast<SfmlWindow*>(GetWindow());

			if (window)
				window->SetWidgetDrawingInterface("SFML");
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