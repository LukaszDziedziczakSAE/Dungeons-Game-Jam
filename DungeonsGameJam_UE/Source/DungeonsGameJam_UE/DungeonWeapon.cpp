// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonWeapon.h"
#include "Components/BoxComponent.h"

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
}

void ADungeonWeapon::WeaponEdgeActivate()
{
	WeaponEdge->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ADungeonWeapon::WeaponEdgeDeactivate()
{
	WeaponEdge->SetCollisionProfileName(TEXT("NoCollision"));
}
