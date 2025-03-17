// Created by Lukasz Dziedziczak. Copyright 2025

#pragma once

#include "CoreMinimal.h"
#include "DungeonItem.h"
#include "DungeonWeapon.generated.h"

UCLASS()
class DUNGEONSGAMEJAM_UE_API ADungeonWeapon : public ADungeonItem
{
	GENERATED_BODY()

public:
	ADungeonWeapon();

	UFUNCTION(BlueprintCallable)
	void SetPlayerRelatives();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* WeaponEdge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WeaponDamage;

	UFUNCTION(BlueprintCallable)
	void WeaponEdgeActivate();

	UFUNCTION(BlueprintCallable)
	void WeaponEdgeDeactivate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector PlayerRelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FQuat PlayerRelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AttackMontage;

public:

	UFUNCTION(BlueprintCallable)
	void Attack();
};
