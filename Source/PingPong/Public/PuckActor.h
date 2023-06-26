// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuckActor.generated.h"

enum EGate : int;

UCLASS()
class PINGPONG_API APuckActor : public AActor
{
	GENERATED_BODY()

	const float Speed = 3000.f;
	
public:	
	// Sets default values for this actor's properties
	APuckActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
	void Respawn();

	UFUNCTION(Server, Reliable)
	void OnPuckHit_Server(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnGameStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
