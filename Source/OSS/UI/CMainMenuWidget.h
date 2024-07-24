#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Game/CMenuInterface.h"
#include "CMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableText;


UCLASS()
class OSS_API UCMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//Like BeginPlay
	virtual bool Initialize() override;

public:
	void SetOwningInterface(ICMenuInterface* InInterface);
	void SetInputToUI();
	void SetInputToGame();

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void SwitchJoinMenu();

	UFUNCTION()
	void SwitchMainMenu();


protected:
	//Buttons
	UPROPERTY(meta = (BindWidget))
	UButton* HostBtn;
	
	UPROPERTY( meta = (BindWidget))
	UButton* JoinBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerBtn;
	 

	//Widgets
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenutSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	//TextBox
	UPROPERTY(meta = (BindWidget))
	UEditableText* IPAddressField;


private:
	ICMenuInterface* OwningInterface;

};
