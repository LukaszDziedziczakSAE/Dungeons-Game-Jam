// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADungeonPlayer::ADungeonPlayer()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    SpringArmComp->SetupAttachment(GetRootComponent());

    //Attach the Camera to the SpringArmComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComp);
    //CameraComponent->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}
