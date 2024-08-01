#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class UParticlSystem;
class USoundCue;

UCLASS()
class OSS_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBullet();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly)
		UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileComp;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	UParticlSystem* ImpactVFX;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	USoundCue* ImpactSound;

};
