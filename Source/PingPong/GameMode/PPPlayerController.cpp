// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/GameMode/PPPlayerController.h"

#include "ContainerActor.h"
#include "PlayerPawn.h"
#include "Camera/CameraActor.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

APPPlayerController::APPPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxis", this, &APPPlayerController::XMovement);
}

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayersToPosses = Cast<AContainerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AContainerActor::StaticClass()));
	if(!PlayersToPosses)
	{
		StartSpectatingOnly();
		return;
	}
	
	int PlayerCount = GetWorld()->GetGameState()->PlayerArray.Num();

	if(PlayerCount == 1 && PlayersToPosses->Player1)
	{
		Possess(PlayersToPosses->Player1);
		SetViewTarget(PlayersToPosses->Player1->PlayerCamera);
	}
	else if(PlayerCount == 2 && PlayersToPosses->Player2)
	{
		Possess(PlayersToPosses->Player2);
		SetViewTarget(PlayersToPosses->Player2->PlayerCamera);
	}
	else
	{
		StartSpectatingOnly();
	}
	
	if(PlayerScoreWidgetClass)
	{
		PlayerScoreWidget = CreateWidget<UScoreWidget>(this, PlayerScoreWidgetClass);
		PlayerScoreWidget->AddToViewport();
		PlayerScoreWidget->SetVisibility(ESlateVisibility::Visible);
	}
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