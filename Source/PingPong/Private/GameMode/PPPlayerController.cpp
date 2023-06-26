// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/Public/GameMode/PPPlayerController.h"

#include "PingPong/Public/GameMode/ContainerActor.h"
#include "PlayerPawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Components/SlateWrapperTypes.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/ScoreWidget.h"

APPPlayerController::APPPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("XAxis", this, &APPPlayerController::XMovement_Client);
}

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		PlayersToPosses = Cast<AContainerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AContainerActor::StaticClass()));
		if(!PlayersToPosses)
		{
			return;
		}
		return;
	}
	
	PossessPawn_Server();
}

void APPPlayerController::XMovement_Client(float AxisValue)
{
	if(!GetPawn()) return;
	
	FVector Velocity = FVector(0.f, 0.f, 0.f);
	Velocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * 5000.f * GetWorld()->GetDeltaSeconds();
	
	auto& CameraTransform = GetViewTarget()->GetRootComponent()->GetComponentTransform();
	
	FVector PawnToCameraLocation = CameraTransform.InverseTransformPosition(GetPawn()->GetActorLocation());
	PawnToCameraLocation += Velocity;
	FVector PawnToWorldLocation = CameraTransform.TransformPosition(PawnToCameraLocation);

	XMovement_Server(PawnToWorldLocation);
}

void APPPlayerController::PossessPawn_Server_Implementation()
{
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

	PossessPawn_Client();
}

void APPPlayerController::PossessPawn_Client_Implementation()
{
	if(PlayerScoreWidgetClass)
	{
		PlayerScoreWidget = CreateWidget<UScoreWidget>(this, PlayerScoreWidgetClass);
		if(PlayerScoreWidget)
		{
			PlayerScoreWidget->AddToViewport();
			PlayerScoreWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void APPPlayerController::XMovement_Server_Implementation(FVector NewLocation)
{
	GetPawn()->SetActorLocation(NewLocation, true);
}
