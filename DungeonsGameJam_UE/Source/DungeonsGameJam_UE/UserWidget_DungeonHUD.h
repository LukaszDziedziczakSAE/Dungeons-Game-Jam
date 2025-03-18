// Created by Lukasz Dziedziczak. Copyright 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_DungeonHUD.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSGAMEJAM_UE_API UUserWidget_DungeonHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	void PreConstruct(bool IsDesignTime);

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ADungeonPlayer* Player;
	
};
