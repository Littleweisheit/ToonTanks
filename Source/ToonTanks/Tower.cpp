// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "Tank.h"
#include "VectorTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		if (InFireRange())
			RotateTurrent(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	
}

void ATower::CheckFireCondition()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fireing"));
	if (InFireRange())
		Fire();
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (Distance < FireRange)
			return true;
	}
	return false;
}
