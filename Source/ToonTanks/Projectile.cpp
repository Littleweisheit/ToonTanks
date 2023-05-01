// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = InitSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMesh->SetSimulatePhysics(true);
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound!=nullptr)
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	if (this->GetOwner() == nullptr)
		return;

	auto ProjectileInstigator = GetOwner()->GetInstigatorController();
	auto DamageType = UDamageType::StaticClass();
	if (OtherActor != this->GetOwner())
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileInstigator, this, DamageType);
	

	if(CameraShakeBaseClass!=nullptr)
		//UGameplayStatics::PlayWorldCameraShake(this,CameraShakeBaseClass,GetActorLocation(),400,200);
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeBaseClass);
	if (HitedParticle != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(this, HitedParticle, Hit.Location, this->GetActorRotation());
	if (HitSound != nullptr)
	UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	Destroy();
}
