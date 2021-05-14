// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GroundTile.h"
#include "Obstacle.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTileManager.generated.h"

UCLASS()
class INFINITESKATE_API AGroundTileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundTileManager();

	UPROPERTY(EditDefaultsOnly, Category=Spawning)
	int NumberOfTilesToSpawn;
	UPROPERTY(EditDefaultsOnly, Category=Spawning)
	TSubclassOf<AGroundTile> GroundTileToSpawn;
	UPROPERTY(EditDefaultsOnly, Category=Spawning)
	float TileMoveSpeed;
	UPROPERTY(EditDefaultsOnly, Category=Spawning)
	FVector TileDestinationPoint;

	UPROPERTY(EditDefaultsOnly, Category=Spawning)
	TSubclassOf<AObstacle> ObstacleToSpawn;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<AGroundTile*> GroundTiles;
	TArray<AObstacle*> Obstacles;

	UFUNCTION()
    void SpawnGroundTiles();
	void SpawnObstacles();
	void InitializeGroundTiles();
	void InitializeObstacles();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
