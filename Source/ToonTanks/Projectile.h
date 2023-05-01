// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float InitSpeed = 200;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float MaxSpeed = 300;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
	float Damage = 20;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* HitedParticle;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> CameraShakeBaseClass;
	
		
};
