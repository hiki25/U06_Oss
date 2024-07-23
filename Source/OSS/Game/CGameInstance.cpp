#include "CGameInstance.h"
#include "../OSS.h"
#include "Blueprint/UserWidget.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Game/UI/WB_MainMenu"));
	if (WidgetClass.Succeeded())
	{
		MainMenuWidgetClass = WidgetClass.Class;
	}
}


void UCGameInstance::Init()
{
	Super::Init();

}

void UCGameInstance::Host()
{
	//ServerTraval
	LogOnScreen(this, "Host", FColor::Green);

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	//ClientTraval
	LogOnScreen(this, "Join To " + InAddress, FColor::Green);

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	if (!MainMenu)
	{
		return;
	}

	MainMenu->AddToViewport();

	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);


		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
	


}
