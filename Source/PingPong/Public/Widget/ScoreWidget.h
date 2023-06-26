// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GateActor.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PINGPONG_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Player1ScoreText;
	int Player1Score;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Player2ScoreText;
	int Player2Score;

	UFUNCTION()
	void ChangeScore(EGate GateType);
};
