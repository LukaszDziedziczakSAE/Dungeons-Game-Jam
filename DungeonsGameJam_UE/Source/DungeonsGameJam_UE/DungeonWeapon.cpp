// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonWeapon.h"
#include "Components/BoxComponent.h"
#include "DungeonCharacter.h"

ADungeonWeapon::ADungeonWeapon()
{
	WeaponEdge = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Edge"));
	WeaponEdge->SetupAttachment(Mesh);

	
}

void ADungeonWeapon::SetPlayerRelatives()
{
	SetActorRelativeLocation(PlayerRelativePosition);
	SetActorRelativeRotation(PlayerRelativeRotation);
}

void ADungeonWeapon::BeginPlay()
{
	WeaponEdgeDeactivate();
	WeaponEdge->OnComponentBeginOverlap.AddDynamic(this, &ADungeonWeapon::OnBeginOverlap);
}

void ADungeonWeapon::WeaponEdgeActivate()
{
	WeaponEdge->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HitCharacters.Empty();
}

void ADungeonWeapon::WeaponEdgeDeactivate()
{
	WeaponEdge->SetCollisionProfileName(TEXT("NoCollision"));
}

void ADungeonWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADungeonCharacter* OtherCharacter = Cast<ADungeonCharacter>(OtherActor);
	ADungeonCharacter* OwnerCharacter = Cast<ADungeonCharacter>(GetOwner());

	if (OtherCharacter == nullptr || OtherCharacter == OwnerCharacter || !OtherCharacter->IsAlive() || HitCharacters.Contains(OtherCharacter)) return;

	HitCharacters.Add(OtherCharacter);
	OtherCharacter->GotHit(WeaponDamage);
	UE_LOG(LogTemp, Warning, TEXT("%s Hit %s"), *OwnerCharacter->GetName(), *OtherActor->GetName());
}

float ADungeonWeapon::Attack()
{
	ADungeonCharacter* DungeonCharacter = Cast<ADungeonCharacter>(GetOwner());
	if (AttackMontage != nullptr && DungeonCharacter != nullptr)
	{
		return DungeonCharacter->PlayAnimMontage(AttackMontage);
	}

	return -1;
}
