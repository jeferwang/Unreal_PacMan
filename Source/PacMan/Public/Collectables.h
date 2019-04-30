// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Collectables.generated.h"

UCLASS()

class PACMAN_API ACollectables : public AActor {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACollectables();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

//    // 是否可以吃敌人
//    UPROPERTY(EditAnywhere,Category=Collectable)
//    bool bIsSuperCollectable;

    // 给豆子定义网格组件（用来显示形状）
    UPROPERTY(VisibleAnywhere, Category = Collectable)
    UStaticMeshComponent *CollectableMesh;

    // 给豆子定义碰撞体组件
    UPROPERTY(EditDefaultsOnly, Category = Collectable)
    USphereComponent *BaseCollisionComponent;

    // 定义是否可以吃敌人
    UPROPERTY(EditAnywhere, Category = Collectable)
    bool bIsSuperCollection;

};
