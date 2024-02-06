#pragma once

#include "Objects/SObject.h"
#include <vector>
#include <memory>
#include "Renderer/DrawingInterface.h"

enum class Visibility 
{
    VISIBLE,
    HIDDEN,
    COLLAPSED
};

class Widget : public SObject 
{
    public:
        Widget();
        virtual ~Widget() = default;

        virtual void render() = 0;

        void AddToViewport();
        void RemoveFromParent();

        void SetIsEnabled(bool bIsEnabled);
        void SetVisibility(Visibility visibility);

        void SetParent(std::shared_ptr<SObject> parent);

    private:

        void SetPosition(FVector2D position);
        void SetSize(FVector2D size);

        bool bIsAddedToViewport;
        bool bIsEnabled;
        Visibility visibility;

        std::weak_ptr<SObject> parent;

    protected:
        std::shared_ptr<DrawingInterface> renderer;

        FVector2D position;
        FVector2D size;
};

template <typename WidgetT = Widget, typename OwnerType = SObject>
WidgetT* CreateWidget(std::unique_ptr<OwnerType> OwningObject)
{
    if (!OwningObject)
    {
        assert(false," The owning object of the widget is null");
		return nullptr;
	}

    WidgetT* widget = new WidgetT();
    if (widget)
    {
        OwningObject->addChild(std::unique_ptr<Widget>(widget));
        widget->SetParent(OwningObject);
        
        return widget;
    }

    assert(false, "Failed to create widget");

    return nullptr;
}