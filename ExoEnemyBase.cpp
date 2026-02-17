// Fill out your copyright notice in the Description page of Project Settings.


#include "ExoEnemyBase.h"
#include "EnemyManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AExoEnemyBase::AExoEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExoEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AExoEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExoEnemyBase::Activate(FVector SpawnLocation)
{
	// 1. teleport
	SetActorLocation(SpawnLocation);

	// 2. enable visibility & collision
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	// 3. enable logic
	SetActorTickEnabled(true);

	// 4. reset movement physics
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		GetCharacterMovement()->SetComponentTickEnabled(true);
	}

	// 5. reset ai (if applicable)
	if (GetController())
	{
		// TK Restart Behavior Tree here (if needed)
	}
}

void AExoEnemyBase::Deactivate()
{
	// 1. disable visibility & collision

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	// 2. disable logic
	SetActorTickEnabled(false);

	// 3. stop movement physics
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		GetCharacterMovement()->SetComponentTickEnabled(false);
	}

	NextInPool = nullptr;
}

void AExoEnemyBase::OnDeath()
{
	if (MyManager)
	{
		MyManager->ReturnEnemyToPool(this);
	}
	else
	{
		Destroy();
	}
}