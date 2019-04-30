// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy.h"
#include "EngineUtils.h"
#include "PacManGameModeBase.generated.h"

// 游戏状态定义
enum class EGameState : short
{
    EMenu,
    EPlaying,
    EPause,
    EWin,
    EGameOver,
};

/**
 *
 */
UCLASS()

class PACMAN_API APacManGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    EGameState GetCurrentState() const;

    void SetCurrentState(EGameState value);

    void SetEnemysVulnerable();

private:
    EGameState currentState;
    TArray<class AEnemy *> Enemys;
};

inline EGameState APacManGameModeBase::GetCurrentState() const
{
    return currentState;
}
