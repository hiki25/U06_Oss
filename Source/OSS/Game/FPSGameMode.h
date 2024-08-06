#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

class APlayerStart;

UCLASS(minimalapi)
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameMode();

public:
	void OnActorKilled(AActor* VictimActor);

protected:
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;


private:
	UFUNCTION()
	void RespawnPlayerElpased(APlayerController* Controller);

private:
	TArray<APlayerStart*> RedTeamPlayerStarts;
	TArray<APlayerStart*> GreenTeamPlayerStarts;

	TArray<APawn*> RedTeamPawns;
	TArray<APawn*> GreenTeamPawns;
};



