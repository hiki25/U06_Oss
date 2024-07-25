#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget>MainMenuWidgetClassAsset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuWidgetClassAsset.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget>InGameMenuWidgetClassAsset(TEXT("/Game/UI/WB_InGameWidget"));
	if (InGameMenuWidgetClassAsset.Succeeded())
	{
		InGameMenuWidgetClass = InGameMenuWidgetClassAsset.Class;
	}
}


void UCGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		UE_LOG(LogTemp, Display, TEXT("OSS Name : %s"), *OSS->GetSubsystemName().ToString());

		 SessionInterface = OSS->GetSessionInterface();		
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Display, TEXT("OSS Find"));

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UCGameInstance::OnCreateSessionCompleted);
		}


	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not Find OSS"));
	}
}

void UCGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		//Create Session
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0,TEXT("My Session"), SessionSettings);
	}
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

void UCGameInstance::OpenMainMenuLevel()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel("/Game/Maps/MainMenuMap", ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	ensure(MainMenuWidgetClass);
	 MainMenu = CreateWidget<UCMainMenuWidget>(this, MainMenuWidgetClass);
	if (!MainMenu)
	{
		return;
	}
		
	MainMenu->SetOwningInterface(this);
	MainMenu->SetInputToUI();

}

void UCGameInstance::LoadInGameMenu()
{
	ensure(InGameMenuWidgetClass);
	UCMenuWIdgetBase* InGameMenu = CreateWidget<UCMenuWIdgetBase>(this, InGameMenuWidgetClass);
	if (!InGameMenu)
	{
		return;
	}

	InGameMenu->SetOwningInterface(this);
	InGameMenu->SetInputToUI();
}

void UCGameInstance::OnCreateSessionCompleted(FName InSessionName, bool bWasSuccessful)
{
	if (bWasSuccessful == false)
	{
		LogOnScreen(this, "Could not create Session", FColor::Red);
		return;
	}

	//ServerTraval
	LogOnScreen(this, "Create Session Completed, Name : " + InSessionName.ToString(), FColor::Green);


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
