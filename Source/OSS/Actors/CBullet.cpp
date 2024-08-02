#include "CBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GamePlayStatics.h"

ACBullet::ACBullet()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(SphereComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bInitialVelocityInLocalSpace = true;
	ProjectileComp->InitialSpeed = 8000.f;
	ProjectileComp->MaxSpeed = 10000.f;
	ProjectileComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 10.f;

	SetReplicates(true);
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentHit.AddDynamic(this, &ACBullet::OnComponentHit);

}

void ACBullet::OnComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsPendingKill())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVFX,GetActorLocation(),GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		Destroy();
	}
}

