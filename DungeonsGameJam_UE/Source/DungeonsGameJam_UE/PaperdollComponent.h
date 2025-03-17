// Created by Lukasz Dziedziczak. Copyright 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperdollComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONSGAMEJAM_UE_API UPaperdollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPaperdollComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
