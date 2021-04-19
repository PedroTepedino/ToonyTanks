// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"

#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}
	
	// if Player is in range THEM FIRE!

	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() const
{
	if (!PlayerPawn) {return 0.0f;}

	return FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
