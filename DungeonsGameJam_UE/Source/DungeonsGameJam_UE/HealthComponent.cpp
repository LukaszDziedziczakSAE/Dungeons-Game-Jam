// Created by Lukasz Dziedziczak. Copyright 2025


#include "HealthComponent.h"
#include "DungeonCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	Character = Cast<ADungeonCharacter>(GetOwner());
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(float Amount)
{
	if (CurrentHealth <= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0, MaxHealth);

	if (IsAlive())
		Character->PlayGotHitMontage();
	else
		Character->PlayDeathMontage();
}

void UHealthComponent::Heal(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
}

