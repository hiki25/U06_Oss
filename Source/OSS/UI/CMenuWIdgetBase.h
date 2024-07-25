#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Game/CMenuInterface.h"
#include "CMenuWIdgetBase.generated.h"

UCLASS()
class OSS_API UCMenuWIdgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetOwningInterface(ICMenuInterface* InInterface);
	void SetInputToUI();
	void SetInputToGame();

protected:
	ICMenuInterface* OwningInterface;

};
