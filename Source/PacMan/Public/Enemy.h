// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Materials/MaterialInterface.h"
#include "Engine/Public/TimerManager.h"
#include "Enemy.generated.h"

UCLASS()

class PACMAN_API AEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AEnemy();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // 给敌人增加StaticMesh以显示形状
    UPROPERTY(VisibleAnywhere, Category = Body)
    UStaticMeshComponent *EnemyBody;

    // 设置敌人当前状态为易受攻击的
    void SetVulnerable();

    // 设置为不易受攻击的
    void SetInVulnerable();

    // 设置敌人是否可移动
    void SetMove(bool MoveIt);

    // 敌人被杀死（迅速移动到出生点）
    void Killed();

    // 重新装填（重新设置为正常的敌人状态）
    void ReArm();

    void OnCollision(
        class UPrimitiveComponent *HitComp,
        class AActor *OtherActor,
        class UPrimitiveComponent *OtherComp,
        int OtherBodyIndex,
        bool bFromSweep,
        const FHitResult &SweetResult);

    // 是否处于死亡状态
    bool bIsDead;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    // 正常情况下的材质
    class UMaterialInterface *DefaultMaterial;

    // 易受攻击时候的材质
    class UMaterialInterface *VulnerableMaterial;

    // 易受攻击状态的计时器
    FTimerHandle TimeVulnerable;

    // 是否处于易受攻击的状态
    bool bIsVulnerable;
};
