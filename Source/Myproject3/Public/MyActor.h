// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C:/Program Files/Epic Games/UE_5.6/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h"
#include "Components/TextRenderComponent.h"

#include "MyActor.generated.h"



UCLASS()
class MYPROJECT3_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

//protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere) //{
		UStaticMeshComponent* Mesh;

		UPROPERTY(BlueprintReadOnly)
		int32 X;

		UPROPERTY(BlueprintReadOnly)
		int32 Y;

		//UPROPERTY(BlueprintReadOnly)
		int32 Height;

		UPROPERTY(BlueprintReadOnly)
		FString CellID;

		UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* Text;

		UPROPERTY()
		bool bIsWalkable;

		UPROPERTY()
		bool bIsOccupied = false;

		void InitializeCell(int32 X, int32 Y, int32 Height);
	//}
};
