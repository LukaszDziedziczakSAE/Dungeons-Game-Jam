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
	if (PaperdollComponent == nullptr) return;

	if (PaperdollComponent->GetCurrentWeapon() == nullptr) return;

	PaperdollComponent->GetCurrentWeapon()->Attack();
}

