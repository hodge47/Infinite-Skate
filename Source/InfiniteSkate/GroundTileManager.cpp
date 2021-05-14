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

	// Spawn the ground tiles
	SpawnGroundTiles();
	// Spawn the obstacles
	SpawnObstacles();
}

// Called every frame
void AGroundTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroundTileManager::SpawnGroundTiles()
{
	FActorSpawnParameters SpawnParams;
	FVector TileOffset = FVector(0.f, -200.f, 0.f);
	for(int i = 0; i < NumberOfTilesToSpawn; i++)
	{
		// Create ground tile
		AGroundTile* Tile = GetWorld()->SpawnActor<AGroundTile>(GroundTileToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);	
		Tile->SetActorLocation(TileOffset);
		GroundTiles.Add(Tile);

		// Increase the tile offset
		TileOffset = TileOffset + FVector(400.f, 0.f, 0.f);
	}
	
	// Initialize the ground tiles
	InitializeGroundTiles();
}

void AGroundTileManager::SpawnObstacles()
{
	FActorSpawnParameters SpawnParams;
	FVector ObstacleOffset = FVector(0.f, 0.f, 0.f);

	for(int i = 0; i < GroundTiles.Num(); i++)
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		Obstacle->SetActorLocation(ObstacleOffset);
		Obstacles.Add(Obstacle);

		ObstacleOffset = ObstacleOffset + FVector(400.f, 0.f, 0.f);
	}

	// Initialize the obstacles
	InitializeObstacles();
}


void AGroundTileManager::InitializeGroundTiles()
{
	/*
	 * The tile offset for the next spawned tile -
	 * offset by -200 on y axis to so middle of tile is actually 0
	 */
	
	for(int i = 0; i < GroundTiles.Num(); i++)
	{
		// Get leading tile
		AGroundTile* LeadingTile;
		if(i == 0)
			LeadingTile = GroundTiles[GroundTiles.Num() - 1];
		else if(i == 1)
		{
			LeadingTile = GroundTiles[0];
		}
		else 
			LeadingTile = GroundTiles[i - 1];
		// Initialize the tile
		GroundTiles[i]->InitializeTile(TileMoveSpeed, TileDestinationPoint, LeadingTile);
	}
}

void AGroundTileManager::InitializeObstacles()
{
	/*
	* The obstacle offset for the next spawned obstacle -
	* offset by -200 on y axis to so middle of tile is actually 0
	*/
	
	for(int i = 0; i < NumberOfTilesToSpawn; i++)
	{
		// Get leading tile
		AObstacle* LeadingObstacle;
		if(i == 0)
			LeadingObstacle = Obstacles[Obstacles.Num() - 1];
		else if(i == 1)
		{
			LeadingObstacle = Obstacles[0];
		}
		else 
			LeadingObstacle = Obstacles[i - 1];
		// Initialize the tile
		Obstacles[i]->InitializeObstacle(TileMoveSpeed, TileDestinationPoint, LeadingObstacle);
	}
}



