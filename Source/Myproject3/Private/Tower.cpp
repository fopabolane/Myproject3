// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	 ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
		Mesh->SetWorldScale3D(FVector(2.f, 2.f, 3.f));
	}
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::InitializeTower(int32 InX, int32 InY)
{
	GridX = InX;
	GridY = InY;
}

// Called every frame
//void ATower::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

//}

