// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//处理Pawn死亡
void ABasePawn::HandleDestuction()
{
	if (DeathPartic != nullptr && !this->IsHidden())
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathPartic, GetActorLocation(), GetActorRotation(),
		                                         FVector(1.5));

	if (DeathSound != nullptr && !this->IsHidden())
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeBase != nullptr && !this->IsHidden())
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeBase);
}

FVector ABasePawn::GetSpawnPointLocation()
{
	return SpawnPoint->GetComponentLocation();
}

FVector ABasePawn::GetSpawnPointForwardVector()
{
	return SpawnPoint->GetForwardVector();
}

void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	FVector ToTaget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0, ToTaget.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			5));
}

void ABasePawn::Fire()
{
	FVector SpawnPointLocation = SpawnPoint->GetComponentLocation();
	FRotator SpawnPointRotaion = SpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnPointLocation, SpawnPointRotaion);
	Projectile->SetOwner(this);
}
