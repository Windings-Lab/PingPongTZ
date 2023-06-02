// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/Public/PuckActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "PingPong/GameMode/PPGameState.h"

// Sets default values
APuckActor::APuckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	RootComponent = StaticMeshComponent;
}

void APuckActor::Respawn(EGate GateType)
{
	SetActorLocation(FVector(0.f, 0.f, 80.f));
}

void APuckActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Vel = StaticMeshComponent->GetPhysicsLinearVelocity();
	Vel = UKismetMathLibrary::Normal(Vel) * Speed;
	StaticMeshComponent->SetPhysicsLinearVelocity(Vel);
}

// Called when the game starts or when spawned
void APuckActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameState<APPGameState>()->OnGoalHappened.AddUniqueDynamic(this, &APuckActor::Respawn);
	StaticMeshComponent->AddImpulse(FVector(0.f, Speed, 0.f), NAME_None, true);
}

