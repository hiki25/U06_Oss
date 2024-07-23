#include "CPlatformTrigger.h"
#include "../OSS.h"
#include "Components/BoxComponent.h"
#include "CMovingPlatform.h"

ACPlatformTrigger::ACPlatformTrigger()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;

}

void ACPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this,&ACPlatformTrigger::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this,&ACPlatformTrigger::OnEndOverlap);
	
}

void ACPlatformTrigger::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//LogOnScreen(this,GetNameSafe(OtherActor)+"is Begin Overlap");
	for (const auto& Platform : PlatformsToTriggers)
	{
		Platform->IncreaseActiveCount();
	}
}

void ACPlatformTrigger::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//LogOnScreen(this, GetNameSafe(OtherActor) + "is End Overlap");
	for (const auto& Platform : PlatformsToTriggers)
	{
		Platform->DecreaseActiveCount();
	}
}
