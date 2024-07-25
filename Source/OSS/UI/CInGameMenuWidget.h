#pragma once

#include "CoreMinimal.h"
#include "CMenuWIdgetBase.h"
#include "CInGameMenuWidget.generated.h"

class UButton;

UCLASS()
class OSS_API UCInGameMenuWidget : public UCMenuWIdgetBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void CancelButtonPressed();

	UFUNCTION()
	void QuitButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitBtn;
};
