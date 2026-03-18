// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    bIsWalkable = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
    Text->SetupAttachment(RootComponent);
    Text->SetHorizontalAlignment(EHTA_Center);
    Text->SetWorldSize(100);
    Text->SetRelativeLocation(FVector(0.f, 0.f, 120.f));

    RootComponent = Mesh;

    static; ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Materials/M_Cell"));

    if (Material.Succeeded())
    {
        Mesh->SetMaterial(0, Material.Object);
    }

    if (CubeMesh.Succeeded())
    {
        Mesh->SetStaticMesh(CubeMesh.Object);
    }

    Mesh->SetWorldScale3D(FVector(2.f, 2.f, 5.f));
    UE_LOG(LogTemp, Error, TEXT("MYACTOR NUOVO CODICE ATTIVO"));
}

void AMyActor::InitializeCell(int32 InX, int32 InY, int32 InHeight)
{
    X = InX;
    Y = InY;
    Height = InHeight;

    if (Height == 0)
    {
        bIsWalkable = false;
    }
    else
    {
        bIsWalkable = true;
    }

    //Height = FMath::RandRange(0, 4);

    float ZScale = 0.2f + Height * 0.5f;
    Mesh->SetWorldScale3D(FVector(2.f, 2.f, ZScale));

    UMaterialInstanceDynamic* DynMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);

    if (DynMaterial)
    {
        FLinearColor Color;
        switch (Height)
        {
        case 0: Color = FLinearColor::Blue; break;
        case 1: Color = FLinearColor::Green; break;
        case 2: Color = FLinearColor::Yellow; break;
        case 3: Color = FLinearColor(1.f, 0.5f, 0.f); break;
        case 4: Color = FLinearColor::Red; break;
        }

        DynMaterial->SetVectorParameterValue("Color", Color);

    }

    //TCHAR Letter = 'A' + X;

    CellID = FString::Printf(TEXT("%d,%d"), X, Y);
    Text->SetText(FText::FromString(CellID));

}

// Called when the game starts or when spawned
//void AMyActor::BeginPlay()
//{
	//Super::BeginPlay();
	
//}

// Called every frame
//void AMyActor::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

//}
