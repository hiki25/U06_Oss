#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CMovingPlatform.generated.h"

UCLASS()
class OSS_API ACMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACMovingPlatform();

public:
	void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (MakeEditWidget))
	FVector TargetLS;

private:
	FVector StartWS; 
	FVector TargetWS; 
};
