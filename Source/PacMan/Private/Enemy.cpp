// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/PacManCharacter.h"
#include "AiEnemy.h"

// Sets default values
AEnemy::AEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // 给敌人创建StaticMesh组件
    EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    // 找到圆柱体组件
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("'/Game/StarterContent/Shapes/Shape_Cylinder'"));
    if (CylinderObj.Succeeded())
    {
        EnemyBody->SetStaticMesh(CylinderObj.Object);
    }
    EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
    EnemyBody->SetRelativeLocation(FVector(0, 0, -50));
    EnemyBody->AttachTo(RootComponent);
    GetCapsuleComponent()->SetCapsuleRadius(40.0f);
    GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);
    // 找到状态处于易受攻击时的材质
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MVulnerable(TEXT("Material'/Game/Materials/M_Vulnerable.M_Vulnerable'"));
    if (MVulnerable.Succeeded())
    {
        VulnerableMaterial = (UMaterialInterface *)MVulnerable.Object;
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *VulnerableMaterial->GetFullName())

    AIControllerClass = AAiEnemy::StaticClass();
    // 启用碰撞检测
    SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    // 获取默认的材质
    DefaultMaterial = EnemyBody->GetMaterial(0);
    // 绑定碰撞函数
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetVulnerable()
{
    // 设置定时器
    GetWorldTimerManager().SetTimer(TimeVulnerable, this, &AEnemy::SetInVulnerable, 10.0f, false);
    if (bIsVulnerable)
    {
        return;
    }
    bIsVulnerable = true;
    EnemyBody->SetMaterial(0, VulnerableMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemy::SetInVulnerable()
{
    UE_LOG(LogTemp, Warning, TEXT("InVulnerable"));
    GetWorldTimerManager().ClearTimer(TimeVulnerable);
    bIsVulnerable = false;
    EnemyBody->SetMaterial(0, DefaultMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemy::SetMove(bool bMoveIt)
{
    AAiEnemy *AI = Cast<AAiEnemy>(GetController());
    if (bMoveIt)
    {
        AI->SearchNewPoint();
    }
    else
    {
        AI->StopMove();
    }
}

void AEnemy::Killed()
{
    if (bIsDead)
    {
        return;
    }
    bIsDead = true;
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    AAiEnemy *AI = Cast<AAiEnemy>(GetController());
    AI->GoHome();
}

void AEnemy::ReArm()
{
    bIsDead = false;
    GetCharacterMovement()->MaxWalkSpeed = 150.0f;
    if (bIsVulnerable)
    {
       SetInVulnerable();
    }
    SetMove(true);
}

void AEnemy::OnCollision(
    class UPrimitiveComponent *HitComp,
    class AActor *OtherActor,
    class UPrimitiveComponent *OtherComp,
    int OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweetResult)
{
            UE_LOG(LogTemp, Warning, TEXT("发生碰撞"));

    if (OtherActor->IsA(APacManCharacter::StaticClass()))
    {
        if (bIsVulnerable)
        {
            UE_LOG(LogTemp, Warning, TEXT("发生碰撞，吃掉敌人"));
            Killed();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("发生碰撞，主角被吃掉"));
            // 找到主角
            APacManCharacter *PacMan = Cast<APacManCharacter>(OtherActor);
            PacMan->Killed();
        }
    }
}
