// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	LifeTime = MaxLifeTime;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime -= DeltaTime;
	const float LifeFactor = LifeTime / MaxLifeTime;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(SourceActor);

	const FVector StartTrace = GetActorLocation();
	const FVector EndTrace = (Velocity * DeltaTime) + StartTrace;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Destructible, CollisionParams))
	{
		if (HitResult.GetActor())
		{
			DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.0f), FColor::Blue, true);
		}
		DrawDebugLine(GetWorld(), StartTrace, HitResult.ImpactPoint, FColor((1 - LifeFactor) * 255.0f, LifeFactor * 255.0f, 0.0f), false, 1.0f);
		Destroy();
	}
	else
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor((1 - LifeFactor) * 255.0f, LifeFactor * 255.0f, 0.0f), false, 1.0f);
		SetActorLocation(EndTrace);
		Velocity += Gravity * DeltaTime;
	}

	if (LifeTime <= 0.0f)
	{
		Destroy();
	}
}
