// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/GameMode/PPPlayerController.h"

#include "PlayerPawn.h"

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxis", this, &APPPlayerController::XMovement);
}

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APPPlayerController::XMovement(float AxisValue)
{
	Velocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * 5000.f * GetWorld()->GetDeltaSeconds();

	auto& CameraTransform = GetViewTarget()->GetRootComponent()->GetComponentTransform();
	
	FVector PawnToCameraLocation = CameraTransform.InverseTransformPosition(GetPawn()->GetActorLocation());
	PawnToCameraLocation += Velocity;
	FVector PawnToWorldLocation = CameraTransform.TransformPosition(PawnToCameraLocation);
	
	GetPawn()->SetActorLocation(PawnToWorldLocation, true);
}