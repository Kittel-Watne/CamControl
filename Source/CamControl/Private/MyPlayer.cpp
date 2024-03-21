// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "MyCamera.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <EnhancedInputComponent.h>
// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UE_LOG(LogTemp, Display, TEXT("Player controller OK"));
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem) {
			subsystem->AddMappingContext(inputMapping, 0);
		}
	}

}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Bind Move() to the mapping
		//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
		//ETriggerEvent is an enum, where Triggered means "button is held down".
		EnhancedInputComponent->BindAction(slow, ETriggerEvent::Triggered, this, & AMyPlayer::slowMove);
		EnhancedInputComponent->BindAction(slow, ETriggerEvent::Triggered, this, &AMyPlayer::fastMove);
		EnhancedInputComponent->BindAction(camSwitch, ETriggerEvent::Triggered, this, &AMyPlayer::SwitchCamera);

	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Cast error line 47"));

	}
}

void AMyPlayer::slowMove(const FInputActionValue& Value)
{
	val = Value.Get<float>();
	UE_LOG(LogTemp, Display, TEXT("Float value: %f"), val);

}

void AMyPlayer::fastMove(const FInputActionValue& Value)
{
}

void AMyPlayer::SwitchCamera()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//UE_LOG(LogTemp, Display, TEXT("Cam change OK"));

	if (MyPlayerController && myCam)
	{
		// Change the camera
		MyPlayerController->SetViewTargetWithBlend(myCam, 0.5f);
		UE_LOG(LogTemp, Display, TEXT("Cam change OK"));
	}
}



