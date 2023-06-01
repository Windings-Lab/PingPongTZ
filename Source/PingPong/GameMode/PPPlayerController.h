// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
};
