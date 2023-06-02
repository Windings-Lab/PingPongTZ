// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/GameMode/PPGameState.h"

void APPGameState::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnPuck && PuckActorClass)
	{
		GetWorld()->SpawnActor<APuckActor>(PuckActorClass, FVector(0.f, 0.f, 80.f), FRotator());
	}
}
