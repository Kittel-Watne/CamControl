// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamera.h"
#include "MyPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
// Sets default values
AMyCamera::AMyCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CameraOriginLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraOriginLocation"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(CameraComp);
    RootComponent = CameraComp;
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->bEnableCameraLag = true;
    SpringArmComp->TargetArmLength = 300.0f;
    // initialize your variables
    AngleAxis = 0.0f;
    Radius = 1000.0f;
    Speed = 2.0f;

    

}

// Called when the game starts or when spawned
void AMyCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Handle the input
    APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (MyPlayerController->IsInputKeyDown(EKeys::Left))
        Speed -= DeltaTime * 10.0f;
    if (MyPlayerController->IsInputKeyDown(EKeys::Right))
        Speed += DeltaTime * 10.0f;
    if (MyPlayerController->IsInputKeyDown(EKeys::C))
        switchCam();

    // Clamp Speed
    Speed = FMath::Clamp(Speed, 1.0f, 100.0f);

    // Update angle
    AngleAxis += DeltaTime * Speed;

    // Calculate new position
    FVector NewLocation;
    NewLocation.X = Radius * FMath::Cos(AngleAxis);
    NewLocation.Y = Radius * FMath::Sin(AngleAxis);
    NewLocation.Z = GetActorLocation().Z;

    // Update actor location
    SetActorLocation(NewLocation);

}

void AMyCamera::switchCam()
{
    CameraComp->SetRelativeLocation(CameraOriginLocation->GetRelativeLocation()+200);
    FVector camLoc = this->GetActorLocation();
    UE_LOG(LogTemp, Display, TEXT("Cam Loc %s"),*this->GetActorLocation().ToString());

}

