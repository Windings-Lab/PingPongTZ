// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPong/GameMode/PPGameMode.h"

#include "ContainerActor.h"
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

	Container = Cast<AContainerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AContainerActor::StaticClass()));
}

void APPGameMode::PostLogin(APlayerController* NewPlayer)
{
	if(GetNumPlayers() > 2)
	{
		NewPlayer->StartSpectatingOnly();
	}
	else
	{
		NewPlayer->SetPawn(GetNumPlayers() == 1 ? Container->Player1 : Container->Player2);
	}
	Super::PostLogin(NewPlayer);
	NewPlayer->SetViewTarget(GetNumPlayers() == 1 ? Container->Camera1 : Container->Camera2);
}
