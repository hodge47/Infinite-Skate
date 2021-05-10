// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTile.generated.h"

UCLASS()
class INFINITESKATE_API AGroundTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh)
	class UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(UStaticMeshComponent* mesh);
};
