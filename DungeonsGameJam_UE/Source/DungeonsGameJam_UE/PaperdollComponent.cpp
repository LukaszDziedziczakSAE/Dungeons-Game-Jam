// Created by Lukasz Dziedziczak. Copyright 2025


#include "PaperdollComponent.h"
#include "DungeonWeapon.h"
#include "DungeonCharacter.h"

// Sets default values for this component's properties
UPaperdollComponent::UPaperdollComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPaperdollComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ADungeonCharacter>(GetOwner());
	
	if (StartingWeapon != nullptr) SpawnWeapon(StartingWeapon);
}


// Called every frame
void UPaperdollComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPaperdollComponent::SpawnWeapon(TSubclassOf<ADungeonWeapon> WeaponToSpawn)
{
	if (Character != nullptr)
	{
		FActorSpawnParameters SpawnInfo;

		CurrentWeapon = GetWorld()->SpawnActor<ADungeonWeapon>(WeaponToSpawn, SpawnInfo);

		if (CurrentWeapon != nullptr)
		{
			//CurrentWeapon->AttachToActor(Character, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
			CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightHand"));
			CurrentWeapon->SetPlayerRelatives();
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn weapon"));

		}
	}
}
