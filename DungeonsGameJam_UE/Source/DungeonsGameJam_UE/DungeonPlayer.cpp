// Created by Lukasz Dziedziczak. Copyright 2025


#include "DungeonPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ADungeonPlayer::ADungeonPlayer()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    SpringArmComp->SetupAttachment(GetRootComponent());

    //Attach the Camera to the SpringArmComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComp);
    //CameraComponent->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADungeonPlayer::DestroyCharacter()
{
	Super::DestroyCharacter();
	UGameplayStatics::OpenLevel(GetWorld(), FName{ *GetWorld()->GetMapName() });
}

void ADungeonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Movement.Length() > 0) // if we are recieving input from player
	{
		// determin rotation based on input from player
		TargetRotation = (FMath::Atan2(-Movement.Y, Movement.X)) * (180 / PI);
	}

	float CurrentRotation = GetMesh()->GetRelativeRotation().Euler().Z;
	if (CurrentRotation != TargetRotation) // if the character is not at the target rotation
	{
		float Differance = TargetRotation - CurrentRotation; // differance between where we are and where we need to be
		float Step = (RotationRate * DeltaTime); // the rotation that is performed per frame
		//UE_LOG(LogTemp, Warning, TEXT("CurrentRoll=%f, TargetRotation=%f, Differance=%f"), CurrentRoll, TargetRotation, Differance);

		if (Differance < (Step * 1.1) && Differance > -(Step * 1.1)) // is the differance smaller than the step I would take?
		{
			// set rotation to target instead of where the step would take us
			GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, TargetRotation)));
			//UE_LOG(LogTemp, Warning, TEXT("Inside Step=%f"), step);
		}
		else
		{
			float NewRotation;
			if ((Differance < 0 && Differance > -180) || Differance > 180) // do we turn left(counter clockwise) or right(clockwise)
			{
				NewRotation = CurrentRotation - Step; // counter clockwise step
			}
			else
			{
				NewRotation = CurrentRotation + Step; // clockwise step
			}
			GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, NewRotation)));
			//UE_LOG(LogTemp, Warning, TEXT("NewRoll=%f, Step=%f"), NewRoll, step);
		}
	}
}
