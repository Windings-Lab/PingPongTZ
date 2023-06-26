// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"

#include "PingPong/Public/GameMode/PPGameState.h"

// Sets default values
AGateActor::AGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AGateActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AGateActor::OnComponentHit);
}

void AGateActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorld()->GetGameState<APPGameState>()->OnGoalHappened.Broadcast(GateType);
}

