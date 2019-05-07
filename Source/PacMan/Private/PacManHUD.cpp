// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Engine/Canvas.h"


void APacManHUD::DrawHUD() {
    GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
    switch (GameMode->GetCurrentState()) {
        case EGameState::EMenu:
            DrawText(
                TEXT("Welcome To PacMan!\n\nN To Start New Game\n\nP To Pause"),
                FColor::White,
                (Canvas->SizeX / 2.0f),
                (Canvas->SizeY / 2.0f),
                HUDFont,
                1.0f,
                true
            );
            break;
        case EGameState::EPlaying:
            PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
            if (PacMan) {
                FString SLive = TEXT("Lives：") + FString::FromInt(PacMan->Lives);
                DrawText(SLive, FColor::Green, 50.0f, 50.0f, HUDFont);
                FString SCollectableToEat = TEXT("CollectableToEat：") + FString::FromInt(PacMan->CollectablesToEat);
                DrawText(SCollectableToEat, FColor::Green, Canvas->SizeX - 150.0f, 50, HUDFont);
            }
            break;
        case EGameState::EPause:
            break;
        case EGameState::EWin:
            break;
        case EGameState::EGameOver:
            break;
    }
}