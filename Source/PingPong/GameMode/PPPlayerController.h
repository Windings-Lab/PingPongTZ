// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPong/Widgets/ScoreWidget.h"
#include "PPPlayerController.generated.h"

class AContainerActor;
class APlayerPawn;
/**
 * 
 */
UCLASS()
class PINGPONG_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()

	APPPlayerController();
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	void XMovement_Client(float AxisValue);

	UFUNCTION(Server, Reliable)
	void XMovement_Server(FVector NewLocation);

	UFUNCTION(Server, Reliable)
	void PossessPawn_Server();

	UFUNCTION(Client, Reliable)
	void PossessPawn_Client();

public:
	UPROPERTY()
	AContainerActor* PlayersToPosses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<UScoreWidget> PlayerScoreWidgetClass;

	UPROPERTY()
	UScoreWidget* PlayerScoreWidget;
};
