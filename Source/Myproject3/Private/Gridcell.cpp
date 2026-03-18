// Fill out your copyright notice in the Description page of Project Settings.


#include "Gridcell.h"
#include "Engine/World.h"
#include "Tower.h"  
#include "Unit.h"

// Sets default values
AGridcell::AGridcell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGridcell::BeginPlay()
{
	Super::BeginPlay();
	RandomSeed = FMath::FRandRange(0.f, 10000.f);
	GenerateGrid();
	SpawnTowers();
	SpawnUnits();
}

// Called every frame
void AGridcell::GenerateGrid()
{
	//Super::Tick(DeltaTime);
	if (!CellClass) return;

	for (int32 X = 0; X < GridSize; X++)
	{
		for (int32 Y = 0; Y < GridSize; Y++)
		{
			FVector Location = FVector(X * CellSpacing - (GridSize * CellSpacing / 2), Y * CellSpacing - (GridSize * CellSpacing / 2), 0.f);
			//FRotator Rotation = FRotator::ZeroRotator;

			//GetWorld()->SpawnActor<AMyActor>(CellClass, Location, FRotator::ZeroRotator);
			AMyActor* NewCell = GetWorld()->SpawnActor<AMyActor>(CellClass, Location, FRotator::ZeroRotator);

			if (NewCell)
			{
				float NoiseValue = FMath::PerlinNoise2D(FVector2D((X + RandomSeed) * NoiseScale, (Y + RandomSeed) * NoiseScale));

				NoiseValue = (NoiseValue + 1.f) / 2.f;

				int32 Height;

				if (NoiseValue < 0.35f)
				{
					Height = 0;
				}
				else if (NoiseValue < 0.50f)
				{
					Height = 1;
				}
				else if (NoiseValue < 0.60f)
				{
					Height = 2;
				}
				else if (NoiseValue < 0.69f)
				{
					Height = 3;
				}
				else
				{
					Height = 4;
				}
				
				GridCells.Add(NewCell);

				NewCell->InitializeCell(X, Y, Height);
			}

			
		}



	}


}



void AGridcell::SpawnTowers()
{
	if (!TowerClass) return;

	TArray<FIntPoint> IdealPositions;

	IdealPositions.Add(FIntPoint(12, 12));
	IdealPositions.Add(FIntPoint(5, 12));
	IdealPositions.Add(FIntPoint(19, 12));

	for (FIntPoint Pos : IdealPositions)
	{
		AMyActor* Cell = FindNearestValidCell(Pos.X, Pos.Y);		

		if (!Cell) continue;
		FVector Location = Cell->GetActorLocation() + FVector(0, 0, 100);

		ATower* NewTower = GetWorld()->SpawnActor<ATower>(TowerClass,Location,FRotator::ZeroRotator);

		if (NewTower)
		{
			Cell->bIsWalkable = false;
		}

		Cell = FindNearestValidCell(Pos.X, Pos.Y);
	}

	
}

AMyActor* AGridcell::FindNearestValidCell(int32 TargetX, int32 TargetY)
{
	AMyActor* BestCell = nullptr;
	float BestDistance = FLT_MAX;

	for (AMyActor* Cell : GridCells)
	{
		if (!Cell)
		{
			continue;
		}
		if (Cell->Height == 0) continue; // solo verde
		if (!Cell->bIsWalkable) continue;

		float Distance = FVector2D(Cell->X - TargetX, Cell->Y - TargetY).Size();

		if (Distance < BestDistance)
		{
			BestDistance = Distance;
			BestCell = Cell;
		}
	}

	return BestCell;
}

void AGridcell::SpawnUnits()
{
	if (!UnitClass) return;

	int32 UnitsToSpawn = 2;

	int32 Spawned = 0;

	for (AMyActor* Cell : GridCells)
	{
		if (!Cell) continue;
		if (Cell->Height == 0 && Cell->bIsWalkable)
		{
			FVector Location = Cell->GetActorLocation() + FVector(0, 0, 100);
			GetWorld()->SpawnActor<AUnit>(UnitClass, Location, FRotator::ZeroRotator);

			Cell->bIsWalkable = false;

			Spawned++;
			if (Spawned >= UnitsToSpawn)
				break;
		}
	}

	FVector Location1 = FVector(-200, -600, 200);
	FVector Location2 = FVector(200, -600, 200);

	if (SniperClass)
	{
		GetWorld()->SpawnActor<AUnit>(SniperClass, Location1, FRotator::ZeroRotator);
	}

	if (BrawlerClass)
	{
		GetWorld()->SpawnActor<AUnit>(BrawlerClass, Location2, FRotator::ZeroRotator);
	}
	
}