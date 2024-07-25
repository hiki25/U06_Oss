#pragma once

#include "CoreMinimal.h"
#include "CMenuWIdgetBase.h"
#include "CMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableText;


UCLASS()
class OSS_API UCMainMenuWidget : public UCMenuWIdgetBase
{
	GENERATED_BODY()

protected:
	//Like BeginPlay
	virtual bool Initialize() override;



private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void SwitchJoinMenu();

	UFUNCTION()
	void SwitchMainMenu();

	UFUNCTION()
		void QuitPressed();


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

	UPROPERTY(meta = (BindWidget))
	UButton* QuitBtn;
	 

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




};
