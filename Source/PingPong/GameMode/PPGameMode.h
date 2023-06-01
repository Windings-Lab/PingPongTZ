// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameMode.generated.h"

class APlayerPawn;
/**
 * 
 */
UCLASS()
class PINGPONG_API APPGameMode : public AGameModeBase
{
	GENERATED_BODY()

	APPGameMode();
	
	virtual void InitGameState() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	UPROPERTY()
	APlayerPawn* Player1;
	UPROPERTY()
	ACameraActor* Camera1;

	UPROPERTY()
	APlayerPawn* Player2;
	UPROPERTY()
	ACameraActor* Camera2;
};

