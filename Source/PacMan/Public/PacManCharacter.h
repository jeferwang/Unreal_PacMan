// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacManGameModeBase.h"
#include "PacManCharacter.generated.h"

UCLASS()

class PACMAN_API APacManCharacter : public ACharacter {
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    APacManCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    int CollectablesToEat;

    int Lives;


    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // 角色的水平移动
    void MoveXAxis(float AxisValue);

    // 角色的垂直移动
    void MoveYAxis(float AxisValue);

    // 重新开始游戏
    void ReStart();

    // 开始新一轮游戏
    void NewGame();

    // 暂停游戏
    void Pause();

    // 主角死亡
    void Killed();



    UFUNCTION()

    void OnCollision(
            class UPrimitiveComponent *HitComp,
            class AActor *OtherActor,
            class UPrimitiveComponent *OtherComp,
            int OtherBodyIndex,
            bool bFromSweep,
            const FHitResult &SweepResult);

private:
    // 当前的速度
    FVector CurrentVelocity;

    APacManGameModeBase *GameMode;


    FVector StartPoint;
};
