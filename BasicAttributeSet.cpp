// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AttributeSets/BasicAttributeSet.h"
#include "GameplayEffectExtension.h"

UBasicAttributeSet::UBasicAttributeSet()
	: Health(100.f)
	, MaxHealth(100.f)
	, Soul(100.f)
	, MaxSoul(100.f)
{
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		// Clamp Health to [0, MaxHealth]
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetSoulAttribute())
	{
		// Clamp Soul to [0, MaxSoul]
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxSoul());
	}

}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetSoulAttribute())
	{
		SetSoul(GetSoul());
	}
}