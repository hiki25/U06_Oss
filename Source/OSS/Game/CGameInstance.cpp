#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"

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


	if (MainMenu)
	{
		MainMenu->SetInputToGame();
	}

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

	if (MainMenu)
	{
		
	MainMenu->SetInputToGame();
	}

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	 MainMenu = CreateWidget<UCMainMenuWidget>(this, MainMenuWidgetClass);
	if (!MainMenu)
	{
		return;
	}
		
	MainMenu->SetOwningInterface(this);
	MainMenu->SetInputToUI();

}
