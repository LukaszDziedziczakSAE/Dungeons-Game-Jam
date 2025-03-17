// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DungeonPlayer.h"

void ADungeonPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<ADungeonPlayer>(aPawn);
}

void ADungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem != nullptr && InputMapping != nullptr)
	{
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}

	else if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Subsystem Referance"), *GetName());
		return;
	}
	else if (InputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Mapping Referance"), *GetName());
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input != nullptr)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ADungeonPlayerController::Move);
		Input->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &ADungeonPlayerController::Attack);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void ADungeonPlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter != nullptr)
	{
		if (Value.Get<FVector2D>().Length() > 0)
		{
			PlayerCharacter->TargetRotation = (FMath::Atan2(-Value.Get<FVector2D>().Y, Value.Get<FVector2D>().X)) * (180 / PI);
			//PlayerCharacter->SetActorRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, TargetRotation }));
		}

		
		FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
			Value.Get<FVector2D>().Y);

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
			Value.Get<FVector2D>().X);
	}
}

void ADungeonPlayerController::Attack(const FInputActionValue& Value)
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->Attack();
	}
}
