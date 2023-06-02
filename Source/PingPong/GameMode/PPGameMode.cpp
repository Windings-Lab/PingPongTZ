// Fill out your copyright notice in the Description page of Project Settings.

#include "PingPong/GameMode/PPGameMode.h"

#include "PPGameState.h"

void APPGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	GetWorldTimerManager().SetTimer(WaitBeforeStart, this, &APPGameMode::WaitBeforeStartFunction, 10.f, false);
	GetWorldTimerManager().SetTimer(OutputRemainingTime, this, &APPGameMode::OutputRemainingTimeFunction, 1.f, true);
}

void APPGameMode::WaitBeforeStartFunction()
{
	auto* PPGameState = GetGameState<APPGameState>();

	if(GetNumPlayers() >= 2)
	{
		PPGameState->OnGameStart.Broadcast();
	}

	GetWorldTimerManager().PauseTimer(OutputRemainingTime);
}

void APPGameMode::OutputRemainingTimeFunction()
{
	if(GEngine)
	{
		float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(WaitBeforeStart);
		GEngine->AddOnScreenDebugMessage(-1
			, 1.f
			, FColor::Yellow
			, FString::Printf(TEXT("Waitint for players: %f"), TimeRemaining));
	}
}
