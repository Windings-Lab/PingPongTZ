// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContainerActor.generated.h"

class APlayerPawn;

UCLASS()
class PINGPONG_API AContainerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainerActor();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	APlayerPawn* Player1;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	APlayerPawn* Player2;
};
