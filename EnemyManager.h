// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExoEnemyBase.h"
#include "EnemyManager.generated.h"

UCLASS()
class EXO_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	// =========================
	//		POOLING VARIABLES
	// =========================

	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AExoEnemyBase> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 PoolSize{ 50 };

	UPROPERTY(Transient)
	AExoEnemyBase* PoolHead = nullptr;

	// =========================
	//		POOLING FUNCTIONS
	// =========================

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	AExoEnemyBase* GetEnemyFromPool(FVector SpawnLocation);

	UFUNCTION(BlueprintCallable, Category="Pooling")
	void ReturnEnemyToPool(AExoEnemyBase* EnemyToReturn);

private:
	void ExpandPool(int32 Count);
};
