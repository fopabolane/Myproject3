// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.h"

#include "Gridcell.generated.h" // Questo include DEVE essere l'ULTIMO prima delle dichiarazioni UCLASS/USTRUCT/UENUM

UCLASS()
class MYPROJECT3_API AGridcell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridcell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	int32 GridSize = 25;

	UPROPERTY(EditAnywhere)
	float CellSpacing = 220.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyActor> CellClass;
    
	UPROPERTY(EditAnywhere)
	float NoiseScale = 0.15f;

	UPROPERTY(EditAnywhere)
	int32 MaxHeight = 4;

	UPROPERTY(EditAnywhere, Category = "Towers")
	TSubclassOf<class ATower> TowerClass;

	UPROPERTY()
	TArray<AMyActor*> GridCells;
	//TArray<AMyActor*> Grid;
	struct FGridCell
	{
		int32 X;
		int32 Y;

		bool bIsWater = false;
		bool bIsWalkable = true;
	};

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUnit> UnitClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnit> SniperClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnit> BrawlerClass;

	void SpawnTowers();

	AMyActor* FindNearestValidCell(int32 TargetX, int32 TargetY);

	float RandomSeed;

	void GenerateGrid();
	//void SpawnTowers(int32 NumTowers);

	void SpawnUnits();
};
