// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	APawnTank* PlayerTank = nullptr;
	int32 TargetTurrets;
	APlayerControllerBase* PlayerControllerRef = nullptr;

	int32 GetTargetTurretCount() const;
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:

	void ActorDied(AActor* DeadActor);
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game loop", meta=(AllowPrivateAccess = "true"))
    int32 StartDelay = 3.f;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};
