#include "CMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

bool UCMainMenuWidget::Initialize()
{	
	//제대로 실행이 되었는지 확인
	bool bSuccess = Super::Initialize();
	if (bSuccess == false)
	{
		return false;
	}

	if (HostBtn)
	{
		HostBtn->OnClicked.AddDynamic(this,&UCMainMenuWidget::HostServer);
	}

	if (JoinBtn)
	{
		JoinBtn->OnClicked.AddDynamic(this, &UCMainMenuWidget::SwitchJoinMenu);
	}

	if (CancelBtn)
	{
		CancelBtn ->OnClicked.AddDynamic(this, &UCMainMenuWidget::SwitchMainMenu);
	}

	if (JoinServerBtn)
	{
		JoinServerBtn->OnClicked.AddDynamic(this, &UCMainMenuWidget::JoinServer);
	}

	if (QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &UCMainMenuWidget::QuitPressed);
	}

	return true;
}



void UCMainMenuWidget::HostServer()
{
	ensure(OwningInterface);
	OwningInterface->Host();
}

void UCMainMenuWidget::JoinServer()
{
	ensure(OwningInterface);
	ensure(IPAddressField);

	const FString& IP = IPAddressField->GetText().ToString();

	OwningInterface->Join(IP);
}

void UCMainMenuWidget::SwitchJoinMenu()
{
	ensure(MenutSwitcher);

	MenutSwitcher->SetActiveWidget(JoinMenu);
}

void UCMainMenuWidget::SwitchMainMenu()
{
	ensure(MenutSwitcher);

	MenutSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenuWidget::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		PC->ConsoleCommand("Quit");
	}
}

