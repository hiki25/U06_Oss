#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CMenuInterface.h"
#include "OnlineSubSystem.h"
#include "CGameInstance.generated.h"

class UUserWidget;
class UCMainMenuWidget;

UCLASS()
class OSS_API UCGameInstance : public UGameInstance, public ICMenuInterface
{
	GENERATED_BODY()
public:
	UCGameInstance();
	virtual void Init() override;

public:
	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& InAddress) override;

	virtual void OpenMainMenuLevel() override;

	UFUNCTION(BlueprintCallable, Exec)
	void LoadMainMenu(); 

	UFUNCTION(BlueprintCallable, Exec)
	void LoadInGameMenu();

private:
	void OnCreateSessionCompleted(FName InSessionName, bool bWasSuccessful);


private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UCMainMenuWidget* MainMenu;

	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	IOnlineSessionPtr SessionInterface;
};
