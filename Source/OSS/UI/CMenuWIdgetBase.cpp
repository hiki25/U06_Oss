#include "CMenuWIdgetBase.h"

void UCMenuWIdgetBase::SetOwningInterface(ICMenuInterface* InInterface)
{
	OwningInterface = InInterface;
}

void UCMenuWIdgetBase::SetInputToUI()
{
	AddToViewport();

	//PlayerController
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);


		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void UCMenuWIdgetBase::SetInputToGame()
{
	//Remove Widget
	RemoveFromParent();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		FInputModeGameOnly InputMode;

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}
