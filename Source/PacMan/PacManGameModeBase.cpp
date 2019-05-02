// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"

void APacManGameModeBase::SetCurrentState(EGameState value)
{
    currentState = value;

    switch (value)
    {
    case EGameState::EMenu:
    UE_LOG(LogTemp,Warning,TEXT("Menu"));
        break;
    case EGameState::EPlaying:
    UE_LOG(LogTemp,Warning,TEXT("playing"));
        for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
        {
             (*Iter)->SetMove(true);
        }
        break;
    case EGameState::EPause:
    UE_LOG(LogTemp,Warning,TEXT("pause"));
        for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
        {
            (*Iter)->SetMove(false);
        }
        break;
    case EGameState::EWin:
    UE_LOG(LogTemp,Warning,TEXT("win"));
        for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
        {
             (*Iter)->Destroy();
        }
        break;
    case EGameState::EGameOver:
    UE_LOG(LogTemp,Warning,TEXT("over"));
        for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
        {
             (*Iter)->Destroy();
        }
        break;
    default:
    UE_LOG(LogTemp,Warning,TEXT("default"));
        break;
    }
}
void APacManGameModeBase::SetEnemysVulnerable()
{
    for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
    {
        (*Iter)->SetVulnerable();
    }
}

void APacManGameModeBase::BeginPlay()
{
    SetCurrentState(EGameState::EMenu);
    // 找到场景中的所有敌人
    for (TActorIterator<AEnemy> enemyItr(GetWorld()); enemyItr; ++enemyItr)
    {
        AEnemy *enemy = Cast<AEnemy>(*enemyItr);
        if (enemy)
        {
            Enemys.Add(enemy);
        }
    }
}
