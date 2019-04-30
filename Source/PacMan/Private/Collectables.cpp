// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectables.h"
#include "Public/UObject/ConstructorHelpers.h"

// Sets default values
ACollectables::ACollectables() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false; // 被收集物品：豆子，不需要每帧更新

    // 开启组件的碰撞功能
    SetActorEnableCollision(true);

    // 创建网格组件
    CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
    // 球形碰撞体组件
    BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));
    // 网格和碰撞体绑定
    CollectableMesh->AttachTo(BaseCollisionComponent);

    // 找到Sphere球体形状
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (Sphere.Succeeded()) {
        // 设置网格的形状为球体
        CollectableMesh->SetStaticMesh(Sphere.Object);
    }
    // 设置球体大小
    CollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
    // 设置碰撞器半径
    BaseCollisionComponent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void ACollectables::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}
