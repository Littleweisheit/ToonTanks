// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}


void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurrent(HitResult.ImpactPoint);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 8, FColor::Red, false);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Value is %f"), Value);
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation = FVector(Value, 0, 0) * Speed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Turn is %f"), Value);
	double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator(0, Value, 0) * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestuction()
{
	Super::HandleDestuction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
		
}
