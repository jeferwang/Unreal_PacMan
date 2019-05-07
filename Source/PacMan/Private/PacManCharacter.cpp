// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PacManCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Public/Collectables.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Public/EngineUtils.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
    Super::BeginPlay();
    // 设置主角的生命值
    Lives = 3;
    // 获取主角出生点的位置
    StartPoint = GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("StartPoint:%s"), *StartPoint.ToString());
    // 获取GameMode
    GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
    // 主角绑定碰撞检测函数
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
    // 统计当前场景中有多少个豆子
    for (TActorIterator<ACollectables> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
    {
        CollectablesToEat++;
    }
    UE_LOG(LogTemp, Warning, TEXT("豆子总数：%d"), CollectablesToEat);
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // 绑定轴向移动
    PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis); // X轴移动
    PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis); // Y轴移动
    // 绑定游戏状态转换
    PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart); // 重新开始
    PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);     // 暂停
    PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame); // 开始新游戏
}

// X Axis的移动控制
void APacManCharacter::MoveXAxis(float AxisValue)
{
    if(GameMode->GetCurrentState()==EGameState::EPlaying){
    CurrentVelocity.X = AxisValue;
    AddMovementInput(CurrentVelocity);
    }
}

// Y Axis的移动控制
void APacManCharacter::MoveYAxis(float AxisValue)
{
    if(GameMode->GetCurrentState()==EGameState::EPlaying){
    CurrentVelocity.Y = AxisValue;
    AddMovementInput(CurrentVelocity);
    }
}

// 暂停
void APacManCharacter::Pause()
{
    if (GameMode->GetCurrentState() == EGameState::EPlaying)
    {
        GameMode->SetCurrentState(EGameState::EPause);
    }
    else if (GameMode->GetCurrentState() == EGameState::EPause)
    {
        GameMode->SetCurrentState(EGameState::EPlaying);
    }
}

// 开始新游戏
void APacManCharacter::NewGame()
{
    if (GameMode->GetCurrentState() == EGameState::EMenu)
    {
        GameMode->SetCurrentState(EGameState::EPlaying);
    }
}

// 重新开始
void APacManCharacter::ReStart()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::OnCollision(
    UPrimitiveComponent *HitComp,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweepResult)
{
    if (GameMode->GetCurrentState() == EGameState::EPlaying)
    {
        if (OtherActor->IsA(ACollectables::StaticClass()))
        {
            // 判断吃到的豆子是不是大力丸
            ACollectables *collectable = Cast<ACollectables>(OtherActor);
            if (collectable->bIsSuperCollection)
            {
                GameMode->SetEnemysVulnerable();
            }
            OtherActor->Destroy();
            if (--CollectablesToEat == 0)
            {
                GameMode->SetCurrentState(EGameState::EWin);
            }
            UE_LOG(LogTemp, Warning, TEXT("吃掉了一个豆子，剩余豆子总数：%d"), CollectablesToEat);
        }
    }
}

void APacManCharacter::Killed()
{
    // 没有生命值，GameOver
    if (--Lives < 0)
    {
        GameMode->SetCurrentState(EGameState::EGameOver);
    }
    // 返回出生点
    else
    {
        SetActorLocation(StartPoint);
    }
}
