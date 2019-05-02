// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "PacManGameModeBase.h"
#include "AiEnemy.generated.h"

/**
 *
 */
UCLASS()

class PACMAN_API AAiEnemy : public AAIController
{
    GENERATED_BODY()

public:
    // 类似BeginPlay的入口函数
    virtual void OnPossess(class APawn *InPawn) override;

    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result) override;

    // 找到一个新的点作为下次移动的目标
    void SearchNewPoint();

    void GoHome();
    void ReArm();
    void StopMove();

private:
  APacManGameModeBase *GameMode;
    // 敌人实例
    class AEnemy *Bot;
    // 初始位置
    FVector HomeLocation;
    // 死亡时间，一段时间之后，重新复活从家里出来
    FTimerHandle DeadTime;
};
