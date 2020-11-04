// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacterBase.h"

// Sets default values
AVRCharacterBase::AVRCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitiateComponents();
}

// Called when the game starts or when spawned
void AVRCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	// Setting Oculus Tracking origin
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);

}

// Called every frame
void AVRCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Thumstick locomotion for testing purposes only, enable by removing comments
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_Y"), this, &AVRCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbLeft_X"), this, &AVRCharacterBase::MoveRight);
	// right thumb x
	PlayerInputComponent->BindAxis(TEXT("MotionControllerThumbRight_X"), this, &AVRCharacterBase::TurnAtRate);

}

void AVRCharacterBase::InitiateComponents()
{
	InitRootCameraHead();
	InitLeftHand();
	InitRightHand();
}

void AVRCharacterBase::InitRootCameraHead()
{
	// Setting our root component
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());


	// Setting up camera 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);


	// Creating character head mesh
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Camera);


}

void AVRCharacterBase::InitLeftHand()
{
	// Setting left controller and hand mesh
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(VRRoot);
	LeftController->SetTrackingSource(EControllerHand::Left);


}

void AVRCharacterBase::InitRightHand()
{
	// setting right controller and hand mesh
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(VRRoot);
	RightController->SetTrackingSource(EControllerHand::Right);




}

void AVRCharacterBase::MoveForward(float Throttle)
{
	AddMovementInput((Throttle)*Camera->GetForwardVector());
}

void AVRCharacterBase::MoveRight(float Throttle)
{
	AddMovementInput((Throttle)*Camera->GetRightVector());
}

void AVRCharacterBase::TurnAtRate(float Rotation)
{
	Sensitivity = 70.0f;
	float ComfortLevel = 0.8f;
	AddControllerYawInput((Rotation * Sensitivity * ComfortLevel) * GetWorld()->GetDeltaSeconds());
}