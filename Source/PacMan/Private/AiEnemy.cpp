// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/AiEnemy.h"
#include "NavigationSystem.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"

void AAiEnemy::OnPossess(class APawn *InPawn)
{
    Super::OnPossess(InPawn);
    // 获取Enemy
    Bot = Cast<AEnemy>(InPawn);
    // 获取敌人初始位置
    HomeLocation = Bot->GetActorLocation();
    GameMode=Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void AAiEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    if (!Bot->bIsDead && GameMode->GetCurrentState()!=EGameState::EPause)
    {
        SearchNewPoint();
    }
}

void AAiEnemy::SearchNewPoint()
{

    // 获得导航系统
    UNavigationSystemV1 *NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavMesh)
    {
        float SearchRadius = 10000.0f;
        FNavLocation RandomPoint;
        const FVector currLoc=Bot->GetActorLocation();

        bool bFound = NavMesh->GetRandomReachablePointInRadius( currLoc,SearchRadius,RandomPoint);

        if (bFound)
        {
            MoveToLocation(RandomPoint);
        }else{
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
    MoveToLocation(Bot->GetActorLocation());
}
