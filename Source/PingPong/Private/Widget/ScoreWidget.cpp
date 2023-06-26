// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ScoreWidget.h"

#include "Components/TextBlock.h"
#include "GameMode/PPGameState.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetGameState<APPGameState>()->OnGoalHappened.AddDynamic(this, &UScoreWidget::ChangeScore);
}

void UScoreWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetWorld()->GetGameState<APPGameState>()->OnGoalHappened.RemoveDynamic(this, &UScoreWidget::ChangeScore);
}

void UScoreWidget::ChangeScore(EGate GateType)
{
	switch (GateType) {
	case Player1:
		Player1Score++;
		Player1ScoreText->SetText(FText::FromString(FString::FromInt(Player1Score)));
		break;
	case Player2:
		Player2Score++;
		Player2ScoreText->SetText(FText::FromString(FString::FromInt(Player2Score)));
		break;
	default: ;
	}
}


