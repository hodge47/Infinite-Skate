// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundTile.h"

// Sets default values
AGroundTile::AGroundTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set IsInitialized to false
	IsInitialized = false;

	// Add mesh to scene root
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	RootComponent = Mesh;
}

void AGroundTile::SetStaticMesh(UStaticMeshComponent* mesh)
{
	Mesh = mesh;
}

// Called when the game starts or when spawned
void AGroundTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Return if this is not initialized
	if(!IsInitialized)
		return;
	// See if the tile needs to be recycled
	CheckNeedToRecycle();
	// Move the tile
	MoveTile(DeltaTime);
	
}

void AGroundTile::InitializeTile(float moveSpeed, FVector destinationPoint, AGroundTile* leadingTile)
{
	// Set the move speed
	SetMoveSpeed(moveSpeed);
	// Set the destination point
	SetDestinationPoint(destinationPoint);
	// Set the start point
	SetLeadingTile(leadingTile);
	// Turn off movement
	EnableMovement(true);

	// Set IsInitialized to true
	IsInitialized = true;
}

void AGroundTile::SetMoveSpeed(float moveSpeed)
{
	MoveSpeed = moveSpeed;
}

void AGroundTile::SetDestinationPoint(FVector destinationPoint)
{
	DestinationPoint = destinationPoint;
}

void AGroundTile::SetLeadingTile(AGroundTile* leadingTile)
{
	LeadingTile = leadingTile;
}

void AGroundTile::EnableMovement(bool enableMovement)
{
	CanMove = enableMovement;
}

void AGroundTile::MoveTile(float DeltaTime)
{
	if(!CanMove)
		return;;
	FVector NextMoveLocation = FVector(this->GetActorLocation().X + (-MoveSpeed * DeltaTime), this->GetActorLocation().Y, 0.f);
	this->SetActorLocation(NextMoveLocation);
}

void AGroundTile::CheckNeedToRecycle()
{
	if (this->GetActorLocation().X <= this->DestinationPoint.X)
	{
		this->SetActorLocation(LeadingTile->GetActorLocation() + FVector(400.f, 0.f, 0.f));
	}
}
