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

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CompletedPercentage{ 0.5f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ADungeonCharacter*> HitCharacters;

public:

	UFUNCTION(BlueprintCallable)
	float Attack();

	UFUNCTION()
	float GetCompletedPercentage() { return CompletedPercentage; }
};
