// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DungeonPlayer.h"
#include "DungeonEnemy.h"

void ADungeonPlayerController::BeginPlay()
{
	SetShowMouseCursor(true);
}

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
		Input->BindAction(IA_AttackMove, ETriggerEvent::Triggered, this, &ADungeonPlayerController::AttackMove);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void ADungeonPlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter != nullptr && !PlayerCharacter->IsAttacking())
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

void ADungeonPlayerController::AttackMove(const FInputActionValue& Value)
{
	if (PlayerCharacter == nullptr) return;
	//UE_LOG(LogTemp, Warning, TEXT("AttackMove"));

	FVector Start;
	FVector Direction;
	FVector End;

	DeprojectMousePositionToWorld(Start, Direction);
	End = Start + (Direction * 1000);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	//RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingleByChannel(
		RV_Hit,		//result
		Start,	//start
		End, //end
		ECC_Pawn, //collision channel
		RV_TraceParams
	))
	{
		ADungeonEnemy* Enemy = Cast<ADungeonEnemy>(RV_Hit.GetActor());

		if (Enemy != nullptr) PlayerCharacter->Attack();

		else
		{
			FVector MoveDirection = FVector{ 
				RV_Hit.ImpactPoint.X - PlayerCharacter->GetActorLocation().X,
				RV_Hit.ImpactPoint.Y - PlayerCharacter->GetActorLocation().Y,
				0.0f} ;
			MoveDirection.Normalize();

			if (!PlayerCharacter->IsAttacking())
			{
				if (Value.Get<FVector2D>().Length() > 0)
				{
					PlayerCharacter->TargetRotation = (FMath::Atan2(-MoveDirection.X, MoveDirection.Y)) * (180 / PI);
				}

				//UE_LOG(LogTemp, Warning, TEXT("MoveDirection: %s"), *MoveDirection.ToString());

				FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

				PlayerCharacter->AddMovementInput(
					UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
					MoveDirection.X);

				PlayerCharacter->AddMovementInput(
					UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
					MoveDirection.Y);
			}
		}
		
	}
}
