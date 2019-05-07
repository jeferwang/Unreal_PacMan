// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManGameModeBase.h"
#include "Public/PacManCharacter.h"
#include "PacManHUD.generated.h"
/**
 *
 */
UCLASS()

class PACMAN_API APacManHUD : public AHUD {
    GENERATED_BODY()

private:
 APacManGameModeBase * GameMode;

public:
    // 字体
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
    UFont *HUDFont;

    APacManCharacter *PacMan;

    virtual void DrawHUD() override;
};
