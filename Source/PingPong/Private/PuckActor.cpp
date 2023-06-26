// Fill out your copyright notice in the Description page of Project Settings.


#include "PuckActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameMode/PPGameState.h"

// Sets default values
APuckActor::APuckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	RootComponent = StaticMeshComponent;
}

void APuckActor::Respawn()
{
	SetActorLocation(FVector(0.f, 0.f, 80.f));
}

void APuckActor::OnPuckHit_Server_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector Vel = StaticMeshComponent->GetPhysicsLinearVelocity();
	Vel = UKismetMathLibrary::Normal(Vel) * Speed;
	StaticMeshComponent->SetPhysicsLinearVelocity(Vel);
}

void APuckActor::OnGameStart()
{
	Respawn();
	StaticMeshComponent->AddImpulse(FVector(0.f, Speed, 0.f), NAME_None, true);
}

// Called when the game starts or when spawned
void APuckActor::BeginPlay()
{
	Super::BeginPlay();

	auto* PPGameState = GetWorld()->GetGameState<APPGameState>();
	
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &APuckActor::OnPuckHit_Server);
	PPGameState->OnGameStart.AddUniqueDynamic(this, &APuckActor::OnGameStart);
}

