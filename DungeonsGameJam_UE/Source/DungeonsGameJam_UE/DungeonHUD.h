// Created by Lukasz Dziedziczak. Copyright 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DungeonHUD.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSGAMEJAM_UE_API ADungeonHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UUserWidget_DungeonHUD* DungeonHUD;
};
