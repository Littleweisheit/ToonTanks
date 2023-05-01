// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Componets", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	APlayerController* PlayerControllerRef;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void Move(float Value);
	void Turn(float Value);
	void TurnTurret(float Value);
	void HandleDestuction();
	APlayerController* GetPlayerController() const {return PlayerControllerRef;}
};
