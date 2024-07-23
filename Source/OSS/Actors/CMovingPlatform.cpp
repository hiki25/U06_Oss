#include "CMovingPlatform.h"

ACMovingPlatform::ACMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	ActiveCount = 1;
	Speed = 100.f;
}

void ACMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	TargetWS = GetTransform().TransformPosition(TargetLS);
	StartWS = GetActorLocation();
}

void ACMovingPlatform::IncreaseActiveCount()
{
	ActiveCount++;
}

void ACMovingPlatform::DecreaseActiveCount()
{
	if (ActiveCount > 0)
	{
		ActiveCount--;
	}
}


void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveCount > 0)
	{

	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();

		float TotalDistance = (StartWS - TargetWS).Size();
		float CurrentDistance = (CurrentLocation - StartWS).Size();

		if (CurrentDistance >= TotalDistance)
		{
			FVector Temp = StartWS;
			StartWS = TargetWS;
			TargetWS = Temp;
		}

		FVector Direction = (TargetWS - StartWS).GetSafeNormal();

		CurrentLocation += Direction * Speed * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
	}

}
