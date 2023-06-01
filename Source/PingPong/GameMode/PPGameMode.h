// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerPawn.h"
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
	UPROPERTY(EditDefaultsOnly)
	APlayerPawn* Player1;

	UPROPERTY(EditDefaultsOnly)
	APlayerPawn* Player2;
};

