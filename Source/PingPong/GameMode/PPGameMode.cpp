// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPong/GameMode/PPGameMode.h"

#include "PPPlayerController.h"
#include "Kismet/GameplayStatics.h"

APPGameMode::APPGameMode()
{
	PlayerControllerClass = APPPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void APPGameMode::InitGameState()
{
	Super::InitGameState();

	TArray<AActor*> PlayerPawnAsActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), PlayerPawnAsActor);
	Player1 = Cast<APlayerPawn>(PlayerPawnAsActor[0]);
	Player2 = Cast<APlayerPawn>(PlayerPawnAsActor[1]);
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
}
