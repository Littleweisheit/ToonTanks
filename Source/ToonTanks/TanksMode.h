// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATanksMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);
	class ATankGameController* TankGameController;
private:
	class ATank * Tank;
	void HandleGameStart();
	float DelayTime=3;
	int32 TargetTower=0;
	int32 GetTargetTower();
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
};
