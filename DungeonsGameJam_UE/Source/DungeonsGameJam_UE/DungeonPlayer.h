// Created by Lukasz Dziedziczak. Copyright 2025

#pragma once

#include "CoreMinimal.h"
#include "DungeonCharacter.h"
#include "DungeonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSGAMEJAM_UE_API ADungeonPlayer : public ADungeonCharacter
{
	GENERATED_BODY()

public:
	ADungeonPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	virtual void DestroyCharacter() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector Movement;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	float TargetRotation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RotationRate;
};
