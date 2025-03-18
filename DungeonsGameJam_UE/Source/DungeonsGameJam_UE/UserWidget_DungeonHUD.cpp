// Created by Lukasz Dziedziczak. Copyright 2025


#include "UserWidget_DungeonHUD.h"
#include "DungeonPlayer.h"

void UUserWidget_DungeonHUD::PreConstruct(bool IsDesignTime)
{
	Super::PreConstruct(IsDesignTime);
	//Player = Cast<ADungeonPlayer>(GetWorld()->GetFirstLocalPlayerFromController());
}

void UUserWidget_DungeonHUD::NativeConstruct()
{
	Super::NativeConstruct();

	
}
