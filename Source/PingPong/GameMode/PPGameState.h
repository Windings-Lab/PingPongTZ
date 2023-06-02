// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GateActor.h"
#include "PPGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoalHappened, EGate, GateTypeParam);

/**
 * 
 */
UCLASS()
class PINGPONG_API APPGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	FOnGoalHappened OnGoalHappened;
};
