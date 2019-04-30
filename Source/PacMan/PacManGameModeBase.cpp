// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"

void APacManGameModeBase::SetCurrentState(EGameState value)
{
    currentState = value;
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
    SetCurrentState(EGameState::EPlaying);
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
