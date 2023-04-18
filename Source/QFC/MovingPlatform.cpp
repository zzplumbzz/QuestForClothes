// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//FString Name = GetName();

	//UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);

	//UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	GetDistanceMoved();
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	//FString NAO = GetName();
	//UE_LOG(LogTemp, Display, TEXT("%s Platform Over Shot By: %f"), *NAO, MoveDistance);
	
	if (ShouldPlatformReturn())
	{

		//float OverShoot = DistanceMoved - MoveDistance;
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
		//UE_LOG(LogTemp, Display, TEXT("Platform Over Shot By: %f"), OverShoot);
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//FString Rotating = GetName();
	//UE_LOG(LogTemp, Display, TEXT("PLATFORM IS ROTATING! %s"), *Rotating);

	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
	 
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}