// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Engine/Public/TimerManager.h"
// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHear);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn *SeenPawn)
{
	if (SeenPawn==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SeenPawn is null !"));
		return;
	}
	//画出圆形区域，半径32，距离12，颜色黄色，最后射线（持久谱线）否，持续时长10秒。
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

//Instigator命名为NoiseInstigator，不然会与Actor里面的Instigator属性冲突。
void AFPSAIGuard::OnNoiseHear(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	//画出圆形区域，半径32，距离12，颜色黄色，最后射线（持久谱线）否，持续时长10秒。
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	//这个函数是LookForRotation的返回值函数。返回一个朝向朝着目标点。
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Roll = 0.0f;
	NewLookAt.Pitch = 0.0f;

	SetActorRotation(NewLookAt);

	//计时器3秒
	//清除旧的计时器,免得重复触发。
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation,this,&AFPSAIGuard::ResetOrientation,3.0f,false);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

