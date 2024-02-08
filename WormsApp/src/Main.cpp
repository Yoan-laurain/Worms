#include "Spoon.h"
#include "Levels/WormLevel.h"
#include "Config.h"
#include <Widgets/Renderer/SFML/SFMLRenderer.h>
#include <Widgets/Renderer/ImGui/ImGuiRenderer.h>
#include <Widgets/Renderer/DrawingInterfaceManager.h>

class App : public Application
{
	public : 
		App() : Application("Spoon", FVector2D(Config::WindowWidth, Config::WindowHeight))
		{
			SetLevel(new WormLevel());
			SetDrawingInterface(true);
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