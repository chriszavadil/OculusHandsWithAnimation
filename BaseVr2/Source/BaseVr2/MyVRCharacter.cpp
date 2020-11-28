// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVRCharacter.h"

AMyVRCharacter::AMyVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	// This code is specific for Oculus as it sets our players height based upon their current guardian settings
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
/*
#if PLATFORM_ANDROID

	// This code checks if we have mic access and if not it requests that access, additional requests like Read/Write can be included here as well for future needs
	TArray <FString> permissionName = { "android.permission.RECORD_AUDIO" };
	if (!UAndroidPermissionFunctionLibrary::CheckPermission(permissionName[0]))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions(permissionName);
	}
#endif

*/
}

void AMyVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Thumstick locomotion for testing purposes, disalbe by adding comment indicator
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_Y"), this, &AMyVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_X"), this, &AMyVRCharacter::MoveRight);

	// This can be used to turn our character, currently not working online
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_X"), this, &AMyVRCharacter::TurnAtRate);
}

void AMyVRCharacter::MoveForward(float Throttle)
{
	// Here we use our camera as the forward vector for movement
	AddMovementInput((Throttle)*VRReplicatedCamera->GetForwardVector());
}

void AMyVRCharacter::MoveRight(float Throttle)
{
	// Here we use our camera as the forward vector for rotation
	AddMovementInput((Throttle)*VRReplicatedCamera->GetRightVector());
}

void AMyVRCharacter::TurnAtRate(float Rotation)
{
	// Based on player comfort level we can adjust how quickly they rotate
	Sensitivity = 70.0f;
	float ComfortLevel = 0.8f;
	AddControllerYawInput((Rotation * Sensitivity * ComfortLevel) * GetWorld()->GetDeltaSeconds());
}
