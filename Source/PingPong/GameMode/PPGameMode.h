// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameMode.generated.h"

class AContainerActor;
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
	AContainerActor* Container;
};

