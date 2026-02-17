// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/Characters/ExoCharacterBase.h"
#include "ExoEnemyBase.generated.h"

class AEnemyManager;
/**
 * 
 */
UCLASS()
class EXO_API AExoEnemyBase : public AExoCharacterBase
{
	GENERATED_BODY()

public:
	AExoEnemyBase();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	// =========================
	//		POOLING VARIABLES
	// =========================

	UPROPERTY(Transient)
	AExoEnemyBase* NextInPool = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Pooling")
	AEnemyManager* MyManager;


	// =========================
	//		POOLING FUNCTIONS
	// =========================

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual void Activate(FVector SpawnLocation);

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual void Deactivate();

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual void OnDeath();
	
};
