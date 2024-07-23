#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlatformTrigger.generated.h"

class UBoxComponent;
class ACMovingPlatform;

UCLASS()
class OSS_API ACPlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPlatformTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(EditInstanceOnly, Category = "MovingPlatform")
		TArray<ACMovingPlatform*> PlatformsToTriggers;

};
