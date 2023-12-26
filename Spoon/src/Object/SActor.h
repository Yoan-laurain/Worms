#pragma once

#include "Spoon/Core/SObject.h"
#include "Spoon/Library/TColor.h"

class SPOON_API SActor : public SObject
{
public:
	SActor();

	virtual ~SActor();

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	void DestroyActor();

	void OnEvent(class SpoonEvent& event);

#pragma region Render

private:

	ObjectRender* Render;

public:

	ObjectRender* GetRender() const { return Render; };

#pragma endregion

#pragma region Color

private:

	FColor ObjectColor;

public:

	FColor GetColor() const { return ObjectColor; };

	void SetColor(const FColor& color);

#pragma endregion

#pragma region World

private:

	class Level* WorldRef = nullptr;

public:

	inline class Level* GetWorld() const { return WorldRef; };

	void SetWorldRef(class Level* parentRef);

};

