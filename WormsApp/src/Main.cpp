#include "Spoon.h"
#include "Levels/WormLevel.h"
#include "Config.h"
#include <Widgets/DrawingInterface.h>
#include <Widgets/Renderer/SFML/SFMLRenderer.h>
#include <Widgets/DrawingInterfaceManager.h>
#include <Widgets/Renderer/ImGui/ImGuiRenderer.h>

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

void SetDrawingInterface(bool useSFML)
{
	std::shared_ptr<DrawingInterface> interface;

	if (useSFML)
	{
		interface = std::make_shared<SFMLRenderer>();
	}
	else 
	{
		interface = std::make_shared<ImGuiRenderer>();
	}

	DrawingInterfaceManager::getInstance().setDrawingInterface(interface);
}

int main()
{
	Application* app = CreateApplication();
	SetDrawingInterface(false);
	app->Run();
	delete app;
	return 0;
}