// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCharacter.h"
#include "HealthComponent.h"
#include "PaperdollComponent.h"
#include "DungeonWeapon.h"

// Sets default values
ADungeonCharacter::ADungeonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	PaperdollComponent = CreateDefaultSubobject<UPaperdollComponent>(TEXT("Paperdoll Component"));
}

// Called when the game starts or when spawned
void ADungeonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonCharacter::MontageCompelete()
{
	isPlayingMontage = false;
}

// Called every frame
void ADungeonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADungeonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADungeonCharacter::Attack()
{
	if (isAttacking || PaperdollComponent == nullptr || PaperdollComponent->GetCurrentWeapon() == nullptr) return;

	float t =  PaperdollComponent->GetCurrentWeapon()->Attack();

	if (t > 0)
	{
		FTimerHandle AttackTimer;
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ADungeonCharacter::AttackTimerComplete, t * PaperdollComponent->GetCurrentWeapon()->GetCompletedPercentage(), false);
		isAttacking = true;
	}
}

void ADungeonCharacter::GotHit(float DamageAmount)
{
	HealthComponent->TakeDamage(DamageAmount);
}

bool ADungeonCharacter::IsAlive()
{
	return HealthComponent->IsAlive();
}

void ADungeonCharacter::PlayGotHitMontage()
{
	if (GotHitMontage == nullptr) return;

	float t = PlayAnimMontage(GotHitMontage);
	if (t > 0)
	{
		FTimerHandle AttackTimer;
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ADungeonCharacter::MontageCompelete, t , false);
		isPlayingMontage = true;
	}
}

void ADungeonCharacter::PlayDeathMontage()
{
	if (DeathMontage == nullptr) return;

	PlayAnimMontage(DeathMontage);
}

void ADungeonCharacter::AttackTimerComplete()
{
	isAttacking = false;
}

