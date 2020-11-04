// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "XRMotionControllerBase.h"
#include "Math/Rotator.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HeadMountedDisplayTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputCoreTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ChildActorComponent.h"
#include "VRCharacterBase.generated.h"

UCLASS()
class BASEVR2_API AVRCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* VRRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Head;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* RightController;


	// Setting up our left hand with touch collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* LeftController;



private:

	// Setting up controller input smooth rotation param
	UPROPERTY(EditAnywhere, Category = "Camera Rotation")
		float Sensitivity;

private:
	// Setting up our player character
	void InitiateComponents();

	// Initializing player character components

	// Setting initial information for root, camera and head
	void InitRootCameraHead();


	// Settining initial info for left hand and watch
	void InitLeftHand();

	// Setting up right hand as well as collisions
	void InitRightHand();

	// Axis Bindings
	void MoveForward(float Throttle);
	void MoveRight(float Throttle);
	void TurnAtRate(float Rotation);


};
