// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    
	RootComponent = Mesh;
	Health = 100;
	Damage = 20;
	Range = 3;
	Movement = 2;
}


// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AUnit::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

//}

