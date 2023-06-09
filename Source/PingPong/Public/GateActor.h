// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateActor.generated.h"

UENUM()
enum EGate : int
{
	Player1 = 1,
	Player2 = 2
};

UCLASS()
class PINGPONG_API AGateActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGateActor();

	UPROPERTY(EditInstanceOnly)
	TEnumAsByte<EGate> GateType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
