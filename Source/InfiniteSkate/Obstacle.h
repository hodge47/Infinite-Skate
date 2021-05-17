// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class INFINITESKATE_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh)
	class UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool IsInitialized = false;
	bool CanMove;
	float MoveSpeed;
	FVector DestinationPoint;
	AObstacle* LeadingObstacle;
	float LeadingObstacleDistance;
	float MeshBounds;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(UStaticMeshComponent* mesh);
	class UStaticMeshComponent* GetStaticMesh() { return Mesh;}
	void InitializeObstacle(float moveSpeed, FVector destinationPoint, AObstacle* leadingObstacle, float ObstacleDistance);
	void SetMoveSpeed(float moveSpeed);
	void SetDestinationPoint(FVector destinationPoint);
	void SetLeadingObstacle(AObstacle* leadingObstacle);
	void EnableMovement(bool enableMovement);
	FVector RandomizePositionY();
	
	private:
	void MoveObstacle(float DeltaTime);
	void CheckNeedToRecycle();
};
