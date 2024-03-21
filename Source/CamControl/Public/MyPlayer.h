// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MyPlayer.generated.h"

UCLASS()
class CAMCONTROL_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* inputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* slow;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* fast;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* camSwitch;
	class AMyCamera* myCam;

	//
	void slowMove(const FInputActionValue& Value);
	void fastMove(const FInputActionValue& Value);

	float val;

public:
	float returnVal() {
		return val;
	}
	void SwitchCamera();
};
