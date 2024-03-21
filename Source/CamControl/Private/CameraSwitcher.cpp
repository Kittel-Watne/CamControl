#include "CameraSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ACameraSwitcher::ACameraSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   // CurrentCameraIndex = 0;
    //// Create and attach cameras
    //for (int32 i = 0; i < 3; ++i) // Change 3 to the number of cameras you want
    //{
    //    UCameraComponent* NewCamera = CreateDefaultSubobject<UCameraComponent>(*FString::Printf(TEXT("Camera%d"), i));
    //    Cameras.Add(NewCamera);
    //    NewCamera->SetupAttachment(RootComponent); // Assuming you have a root component
    //    NewCamera->SetActive(i == 0); // Activate the first camera
    //}
    CameraOne = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraOne"));
    CameraOne->SetupAttachment(RootComponent);

    CameraTwo = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraTwo"));
    CameraTwo->SetupAttachment(RootComponent);

    // Make CameraOne the active camera at start
    CameraOne->SetActive(true);
    CameraTwo->SetActive(false);
}

// Called when the game starts or when spawned
void ACameraSwitcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (MyPlayerController->IsInputKeyDown(EKeys::C))
        SwitchCamera();

}

void ACameraSwitcher::SwitchCamera()
{

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (PlayerController)
    {
        // Check if CameraOne is currently active
        if (CameraOne->IsActive())
        {
            // If it is, deactivate it and activate CameraTwo
            CameraOne->Deactivate();
            CameraTwo->Activate();

            // Set the view target to CameraTwo
            PlayerController->SetViewTarget(this);
        }
        else
        {
            CameraTwo->Deactivate();
            CameraOne->Activate();

            // Set the view target to CameraOne
            PlayerController->SetViewTarget(this);
        }
    }
}

void ACameraSwitcher::UpdateCameraLocations(const TArray<FVector>& NewLocations)
{
    if (NewLocations.Num() != Cameras.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Number of new locations does not match the number of cameras."));
        return;
    }

    for (int32 i = 0; i < NewLocations.Num(); ++i)
    {
        // Get the transform of the camera component
        FTransform NewTransform = Cameras[i]->GetComponentTransform();
        // Update the location component of the transform
        NewTransform.SetLocation(NewLocations[i]);
        // Set the new transform for the camera component
        Cameras[i]->SetWorldTransform(NewTransform);
    }
}

