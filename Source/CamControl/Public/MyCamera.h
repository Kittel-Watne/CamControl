// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MyCamera.generated.h"

UCLASS()
class CAMCONTROL_API AMyCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// Arrow Component for the Camera Origin viewpoint location
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* CameraOriginLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* CameraComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;
private:
	float AngleAxis;
	float Radius;
	float Speed;
	void switchCam();
};
