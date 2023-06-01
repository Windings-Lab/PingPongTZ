// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPong/GameMode/PPGameMode.h"

#include "PlayerPawn.h"
#include "PPPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

APPGameMode::APPGameMode()
{
	PlayerControllerClass = APPPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void APPGameMode::InitGameState()
{
	Super::InitGameState();

	TArray<AActor*> Player1Actors;
	TArray<AActor*> Player2Actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("PlayerTag1"), Player1Actors);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("PlayerTag2"), Player2Actors);

	// Player 1
	if(auto* PlayerPawn = Cast<APlayerPawn>(Player1Actors[0]))
	{
		Player1 = PlayerPawn;
	}
	else
	{
		Camera1 = Cast<ACameraActor>(Player1Actors[0]);
	}

	if(auto* PlayerPawn = Cast<APlayerPawn>(Player1Actors[1]))
	{
		Player1 = PlayerPawn;
	}
	else
	{
		Camera1 = Cast<ACameraActor>(Player1Actors[1]);
	}

	// Player 2
	if(auto* PlayerPawn = Cast<APlayerPawn>(Player2Actors[0]))
	{
		Player2 = PlayerPawn;
	}
	else
	{
		Camera2 = Cast<ACameraActor>(Player2Actors[0]);
	}

	if(auto* PlayerPawn = Cast<APlayerPawn>(Player2Actors[1]))
	{
		Player2 = PlayerPawn;
	}
	else
	{
		Camera2 = Cast<ACameraActor>(Player2Actors[1]);
	}
}

void APPGameMode::PostLogin(APlayerController* NewPlayer)
{
	if(GetNumPlayers() > 2)
	{
		NewPlayer->StartSpectatingOnly();
	}
	else
	{
		NewPlayer->SetPawn(GetNumPlayers() == 1 ? Player1 : Player2);
	}
	Super::PostLogin(NewPlayer);
	NewPlayer->SetViewTarget(GetNumPlayers() == 1 ? Camera1 : Camera2);
}
