#include "CBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

ACBullet::ACBullet()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(SphereComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bInitialVelocityInLocalSpace = true;
	ProjectileComp->InitialSpeed = 8000.f;
	ProjectileComp->MaxSpeed = 10000.f;
	ProjectileComp->ProjectileGravityScale = 0.f;
}
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

