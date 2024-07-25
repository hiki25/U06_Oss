#include "CInGameMenuWidget.h"
#include "Components/Button.h"

bool UCInGameMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (Success == false)
	{
		return false;
	}

	if (QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &UCInGameMenuWidget::QuitButtonPressed);
	}

	if (CancelBtn)
	{
		CancelBtn->OnClicked.AddDynamic(this, &UCInGameMenuWidget::CancelButtonPressed);
	}
	return true;
}

void UCInGameMenuWidget::CancelButtonPressed()
{
	SetInputToGame();
}

void UCInGameMenuWidget::QuitButtonPressed()
{
	if (OwningInterface)
	{
		SetInputToUI();
		OwningInterface->OpenMainMenuLevel();
	}
}
