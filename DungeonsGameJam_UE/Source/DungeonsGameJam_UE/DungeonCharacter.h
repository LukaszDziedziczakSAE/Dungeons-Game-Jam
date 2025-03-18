// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DungeonCharacter.generated.h"

UCLASS()
class DUNGEONSGAMEJAM_UE_API ADungeonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADungeonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperdollComponent* PaperdollComponent;

	UFUNCTION()
	void AttackTimerComplete();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* GotHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* DeathMontage;

	bool isPlayingMontage;

	UFUNCTION()
	void MontageCompelete();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION()
	bool IsAttacking() { return isAttacking; }

	UFUNCTION(BlueprintCallable)
	void GotHit(float DamageAmount);

	UFUNCTION(BlueprintPure)
	bool IsAlive();

	UFUNCTION(BlueprintPure)
	bool IsPlayingMontage() { return isPlayingMontage; }

	UFUNCTION(BlueprintCallable)
	void PlayGotHitMontage();

	UFUNCTION(BlueprintCallable)
	void PlayDeathMontage();
};
