// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurrent(FVector LookAtTarget);
	void Fire();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	UParticleSystem* DeathPartic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Componets", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPoint;
	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* DeathSound;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnRate = 5;
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeBase;


	void HandleDestuction();

	FVector GetSpawnPointLocation();
	FVector GetSpawnPointForwardVector();
};
