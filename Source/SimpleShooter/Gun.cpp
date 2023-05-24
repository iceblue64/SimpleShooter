/*****************************************************************//**
 * \file   Gun.cpp
 * \brief  General gun logic, including calculating gun traces and
 * trigger logic.
 * 
 * \author Mike Doeren
 * \date   May 2023
 *********************************************************************/

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"           // SpawnEmitterAttached()
#include "DrawDebugHelpers.h"                 // DrawDebugCamera()

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup a root component to nest future components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	FHitResult Hit; // A struct that contains info about a collision hit during a line trace
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection); // If the line trace hits an object on the ECC_GameTraceChannel1 collision channel, return true

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket")); // Create a muzzle flash particle effect
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));   // Create a muzzle flash sound effect

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation()); // Spawn particle effect at location
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);                               // Spawn sound effect at location

		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); // A struct representing an event of damage being applied to a point on an actor	
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);	
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = -Rotation.Vector(); // Show which dir the shot came from

	FVector End = Location + Rotation.Vector() * MaxRange; // Calculation to get end point
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);       // Ignore the gun actor
	Params.AddIgnoredActor(GetOwner()); // Ignore the owner of the gun so it doesn't hit itself w/ own gun

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner()); // Cast as pawn - only pawns can be possessed by controllers
	if (OwnerPawn == nullptr)
		return nullptr;

	return OwnerPawn->GetController();
}
