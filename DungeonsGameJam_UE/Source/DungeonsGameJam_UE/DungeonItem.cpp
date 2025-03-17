// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonItem.h"

// Sets default values
ADungeonItem::ADungeonItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADungeonItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

