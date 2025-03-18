// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonHUD.h"
#include "UserWidget_DungeonHUD.h"

void ADungeonHUD::BeginPlay()
{
	if (DungeonHUD != nullptr) DungeonHUD->AddToViewport();
}
