// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundTileManager.h"

// Sets default values
AGroundTileManager::AGroundTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroundTileManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnGroundTiles();
}

// Called every frame
void AGroundTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroundTileManager::SpawnGroundTiles()
{
	FActorSpawnParameters SpawnParams;

	// The tile offset for the next spawned tile -
	// offset by -200 on y axis to so middle of tile is actually 0
	FVector TileOffset = FVector(0.f, -200.f, 0.f);
	for(int i = 0; i < NumberOfTilesToSpawn; i++)
	{
		AGroundTile* Tile = GetWorld()->SpawnActor<AGroundTile>(GroundTileToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		Tile->SetActorLocation(TileOffset);
		GroundTiles.Add(Tile);
		TileOffset = TileOffset + FVector(400.f, 0.f, 0.f);
	}
	
	//AActor* SpawnedActorReference = GetWorld()->SpawnActor<AActor>(GroundTileToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}


