#include "WindWidget.h"
#include "../../Config.h"
#include <Widgets/Image/ImageWidget.h>
#include <Library/WidgetHandler.h>

WindWidget::WindWidget()
    : WindLogo(nullptr)
    , WindDirection(nullptr)
{
   bIsTickable = true;
}

void WindWidget::Init()
{
    WindLogo = WidgetHandler::CreateWidget<ImageWidget>(nullptr);
	
    WindLogo->Size = FVector2D(60.f, 40.f);
    WindLogo->RelativePosition = FVector2D(Config::SectionForOnePlayer - WindLogo->Size.X / 2.f, 100.f);
    WindLogo->ImagePath = Config::Wind;
    WindLogo->AddToViewport();

    WindDirection = WidgetHandler::CreateWidget<ImageWidget>(WindLogo);
	
    WindDirection->Size = FVector2D(30.f, 20.f);
    WindDirection->RelativePosition = FVector2D(WindLogo->Size.X / 2.f - WindDirection->Size.X / 2.f, WindLogo->Size.Y + 10.f);
    WindDirection->ImagePath = Config::WindDirection;
    WindDirection->AddToViewport();
}

void WindWidget::UpdateWindDirection(float WindDirection)
{
    this->WindDirection->Rotation = WindDirection;
}

void WindWidget::Render()
{
}

void WindWidget::Tick(float DeltaTime)
{
    Widget::Tick(DeltaTime);
    
    UpdateWindDirection(WindDirection->Rotation + 40.f * DeltaTime);
}