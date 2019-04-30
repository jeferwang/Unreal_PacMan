// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AiEnemy.h"
#include "NavigationSystem.h"
#include "Public/TimerManager.h"

void AAiEnemy::OnPossess(class APawn *InPawn)
{
    Super::OnPossess(InPawn);
    // 获取Enemy
    Bot = Cast<AEnemy>(InPawn);
    // 获取敌人初始位置
    HomeLocation = Bot->GetActorLocation();
    // 开始的时候就自动寻路
    SearchNewPoint();
}

void AAiEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    if (!Bot->bIsDead)
    {
        SearchNewPoint();
    }
}

void AAiEnemy::SearchNewPoint()
{
    // 获得导航系统
    UNavigationSystem *NavMesh = FNavigationSystem::GetCurrent<UNavigationSystem>(this);
    if (NavMesh)
    {
        const float SearchRadius = 1000.0f;
        FVector RandomPoint;

        bool bFound = NavMesh->K2_GetRandomReachablePointInRadius(this, Bot->GetActorLocation(), RandomPoint, SearchRadius);

        if (bFound)
        {
            MoveToLocation(RandomPoint);
        }
    }
}

void AAiEnemy::GoHome()
{
    MoveToLocation(HomeLocation);
    GetWorldTimerManager().SetTimer(DeadTime, this, &AAiEnemy::ReArm, 5.0f, false);
}
void AAiEnemy::ReArm()
{
    GetWorldTimerManager().ClearTimer(DeadTime);
    // 让敌人恢复行动
    Bot->ReArm();
}

void AAiEnemy::StopMove()
{
    StopMovement();
}
