// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksMode.h"

#include "Tank.h"
#include "TankGameController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATanksMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		
		Tank->HandleDestuction();
		TankGameController->SetPlayEnabledState(false);
		GameOver(false);
	}
	else if (ATower* DeadTower = Cast<ATower>(DeadActor))
	{
		DeadTower->HandleDestuction();
		if (GetTargetTower() <= 0)
			GameOver(true);
	}
}


int32 ATanksMode::GetTargetTower()
{
	TArray<AActor*> Tower;
	TSubclassOf<AActor> TowerClass = ATower::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(this, TowerClass, Tower);
	return Tower.Num();
}

void ATanksMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void ATanksMode::HandleGameStart()
{
	GameStart();
	TargetTower = GetTargetTower();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TankGameController = Cast<ATankGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	TankGameController->SetPlayEnabledState(false);
	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
		TankGameController,
		&ATankGameController::SetPlayEnabledState,
		true);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, DelayTime, false);
}
