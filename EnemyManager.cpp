// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Characters/EnemyManager.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	if(EnemyClass)
	{
		ExpandPool(PoolSize);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyManager: EnemyClass is not set!"));
	}
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::ExpandPool(int32 Count)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i{ 0 }; i < Count; ++i)
	{
		AExoEnemyBase* NewEnemy = GetWorld()->SpawnActor<AExoEnemyBase>(
			EnemyClass, 
			FVector::ZeroVector, 
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (NewEnemy)
		{
			NewEnemy->MyManager = this;
			ReturnEnemyToPool(NewEnemy);
		}
	}
}

AExoEnemyBase* AEnemyManager::GetEnemyFromPool(FVector SpawnLocation)
{
	if (!PoolHead)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyManager: Pool exhausted, expanding pool by %d"), PoolSize);
		ExpandPool(PoolSize);

		if(!PoolHead)
		{
			UE_LOG(LogTemp, Error, TEXT("EnemyManager: Pool expansion failed, cannot provide enemy"));
			return nullptr;
		}
	}
	AExoEnemyBase* SelectedEnemy = PoolHead;

	PoolHead = SelectedEnemy->NextInPool;

	SelectedEnemy -> NextInPool = nullptr;

	SelectedEnemy -> Activate(SpawnLocation);

	return SelectedEnemy;
}

void AEnemyManager::ReturnEnemyToPool(AExoEnemyBase* EnemyToReturn)
{
	if (!EnemyToReturn)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyManager: Attempted to return a null enemy to the pool"));
		return;
	}
	EnemyToReturn->Deactivate();
	EnemyToReturn->NextInPool = PoolHead;
	PoolHead = EnemyToReturn;
}