// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
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

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Return if this is not initialized
	if(!IsInitialized)
		return;
	// See if the tile needs to be recycled
	CheckNeedToRecycle();
	// Move the tile
	MoveObstacle(DeltaTime);
}

void AObstacle::SetStaticMesh(UStaticMeshComponent* mesh)
{
	Mesh = mesh;
}

void AObstacle::InitializeObstacle(float moveSpeed, FVector destinationPoint, AObstacle* leadingObstacle)
{
	// Set the move speed
	SetMoveSpeed(moveSpeed);
	// Set the destination point
	SetDestinationPoint(destinationPoint);
	// Set the start point
	SetLeadingObstacle(leadingObstacle);
	// Turn off movement
	EnableMovement(true);
	// Randomize the initial y position
	FVector position = FVector(this->GetActorLocation().X, RandomizePositionY().Y, this->GetActorLocation().Z);
	this->SetActorLocation(position);

	// Set IsInitialized to true
	IsInitialized = true;
}

void AObstacle::SetMoveSpeed(float moveSpeed)
{
	MoveSpeed = moveSpeed;
}

void AObstacle::SetDestinationPoint(FVector destinationPoint)
{
	DestinationPoint = destinationPoint;
}

void AObstacle::SetLeadingObstacle(AObstacle* leadingObstacle)
{
	LeadingObstacle = leadingObstacle;
}

void AObstacle::EnableMovement(bool enableMovement)
{
	CanMove = enableMovement;
}

void AObstacle::MoveObstacle(float DeltaTime)
{
	if(!CanMove)
		return;
	FVector NextMoveLocation = FVector(this->GetActorLocation().X + (-MoveSpeed * DeltaTime), this->GetActorLocation().Y, 0.f);
	this->SetActorLocation(NextMoveLocation);
}

void AObstacle::CheckNeedToRecycle()
{
	if (this->GetActorLocation().X <= this->DestinationPoint.X)
	{
		FVector offset = FVector(400.f, 0.f, 0.f) + RandomizePositionY();
		this->SetActorLocation(LeadingObstacle->GetActorLocation() + offset);
	}
}

FVector AObstacle::RandomizePositionY()
{
	// Seed rand
	srand(time(NULL));
	// Get random number - 0 or 1
	int side = rand() % 2;

	FVector yOffset;

	if(side == 0)
		yOffset = FVector(0.f, -100.f, 0.f);
	else
		yOffset = FVector(0.f, 200.f, 0.f);

	return yOffset;
}