#include "WormsPlayer.h"
#include "../Weapons/WeaponStrategy.h"
#include "../Weapons/SimpleGun/SimpleGun.h"
#include "Inputs/InputAction.h"
#include "Spoon/Core/Level.h"
#include "Objects/Components/SShapeComponent.h"
#include "../Levels/WormLevel.h"
#include "../Weapons/FragGrenade/GrenadeLauncher.h"
#include <Widgets/Image/ImageWidget.h> 
#include <Objects/Prefab/CircleObject.h>
#include <Inputs/InputType.h>
#include <Widgets/TextBlock/TextBlockWidget.h>
#include <Widgets/ProgressBar/ProgressBarWidget.h>
#include <Widgets/Button/ButtonWidget.h>
#include <Library/WidgetHandler.h>

WormsPlayer::WormsPlayer() :
	weaponStrategy(nullptr),
	currentHealth(100),
	maxHealth(100),
	HasShot(false)
{
	GetPolygonComponent()->texturePath = "Ressources/WormsPlayer.png";
	GetPolygonComponent()->name = "WormsPlayer";
	SetDensity(2.f);

	SetWeaponStrategy( std::make_unique<SimpleGun>() );

	ApplyBinding();
}

WormsPlayer::~WormsPlayer()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	level->m_TurnManager->unregisterObserver(this);	 
}

void WormsPlayer::SetWeaponStrategy(std::unique_ptr<WeaponStrategy> weaponStrategy)
{
	this->weaponStrategy = std::move(weaponStrategy);
}

WeaponStrategy* WormsPlayer::GetWeaponStrategy() const
{
	return weaponStrategy.get();
}

void WormsPlayer::onTurnChange(int currentWormsPlayer)
{
	if (!IsMyTurn())
		return;

	HasShot = false;
}

void WormsPlayer::MoveVertical(float value, float sign)
{
	if (!IsMyTurn() || HasShot)
		return;
	
	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(0.f, sign * GetSize().Y);

		AddForce(direction * value * 500.f);
	}
}

void WormsPlayer::MoveHorizontal(float value, float sign)
{
	if (!IsMyTurn() || HasShot)
		return;

	if (value > 0.f)
	{	
		// TODO : Adapt object to world size
		FVector2D direction = FVector2D(sign * GetSize().X, 0.f);

		AddForce(direction * value * 500.f); 
	}
}

void WormsPlayer::ApplyBinding()
{
	BindFunctionToInputAction(InputAction::Left, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, -1.f),InputType::Hold);
	BindFunctionToInputAction(InputAction::Right, std::bind(&WormsPlayer::MoveHorizontal, this, std::placeholders::_1, 1.f), InputType::Hold);

	BindFunctionToInputAction(InputAction::Up, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, -1.f), InputType::Hold);
	BindFunctionToInputAction(InputAction::Down, std::bind(&WormsPlayer::MoveVertical, this, std::placeholders::_1, 1.f), InputType::Hold);

	BindFunctionToInputAction(InputAction::Fire, std::bind(&WormsPlayer::Shoot, this), InputType::Pressed);
}

void WormsPlayer::Shoot()
{
	if (!IsMyTurn() || HasShot)
		return;

	HasShot = true;

	FVector2D location = GetLocation();
	location.X += GetForwardVector().X * GetSize().X + 10.f;
	FTransform transform = FTransform(location, FVector2D(5.f, 5.f));

	weaponStrategy->Shoot(*GetWorld(),transform);
}

bool WormsPlayer::IsMyTurn()
{
	WormLevel* level = static_cast<WormLevel*>(GetWorld());
	return level->m_TurnManager->currentPlayer == PlayerId;
}

void WormsPlayer::UpgradeWeapon()
{
	std::cout << "Upgrade" << std::endl;
}

void WormsPlayer::BeginPlay()
{
	healthText = WidgetHandler::CreateWidget<TextBlockWidget>(this);
	healthText->setText("Life : " + std::to_string(currentHealth));
	healthText->SetSize(FVector2D(100.f, 100.f));
	healthText->setFontSize(20);
	healthText->setColor(FColor(125, 15, 245, 255));
	healthText->SetRelativePosition(FVector2D( -GetSize().X *2 , -GetSize().Y * 2 - healthText->size.Y));
	healthText->AddToViewport();

	healthImage = WidgetHandler::CreateWidget<ImageWidget>(this);
	healthImage->SetBackgroundImage("Ressources/WormsPlayer.png");
	healthImage->SetSize(FVector2D(50.f, 50.f));
	healthImage->SetRelativePosition(FVector2D( -healthImage->size.X / 2.f, -GetSize().Y * 2 - healthImage->size.Y / 2.f));
	healthImage->AddToViewport();

	UpgradeButton = WidgetHandler::CreateWidget<ButtonWidget>(this);
	UpgradeButton->SetSize(FVector2D(100.f, 30.f));
	UpgradeButton->SetRelativePosition(FVector2D(-UpgradeButton->size.X / 2.f, -GetSize().Y * 2 - UpgradeButton->size.Y * 2));
	UpgradeButton->SetText("Upgrade");
	UpgradeButton->SetOnClick(std::bind(&WormsPlayer::UpgradeWeapon, this));
	UpgradeButton->AddToViewport();

	healthBar = WidgetHandler::CreateWidget<ProgressBarWidget>(this);
	healthBar->SetSize(FVector2D(100.f, 10.f));
	healthBar->SetRelativePosition(FVector2D(-healthBar->size.X / 2.f, -GetSize().Y * 2 - healthBar->size.Y * 12));
	healthBar->setProgress( currentHealth / maxHealth );
	healthBar->setBackgroundColor(FColor(127, 127, 127, 150));
	healthBar->setColor(FColor(0, 255, 0, 255));
	healthBar->AddToViewport();
}

bool WormsPlayer::OnDamageTaken(int damage)
{
	currentHealth = std::max(0.f, std::min(currentHealth - damage, maxHealth));

	healthBar->setProgress(currentHealth / maxHealth);
	healthText->setText("Life : " + std::to_string(currentHealth));

	if (currentHealth <= 0)
	{
		MarkActorToDestruction();

		WormLevel* level = dynamic_cast<WormLevel*>(GetWorld());
		level->m_TurnManager->OnEndGame();
	}

	return currentHealth > 0;
}