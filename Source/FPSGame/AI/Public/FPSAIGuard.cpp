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
	//����Բ�����򣬰뾶32������12����ɫ��ɫ��������ߣ��־����ߣ��񣬳���ʱ��10�롣
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

//Instigator����ΪNoiseInstigator����Ȼ����Actor�����Instigator���Գ�ͻ��
void AFPSAIGuard::OnNoiseHear(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	//����Բ�����򣬰뾶32������12����ɫ��ɫ��������ߣ��־����ߣ��񣬳���ʱ��10�롣
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	//���������LookForRotation�ķ���ֵ����������һ��������Ŀ��㡣
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Roll = 0.0f;
	NewLookAt.Pitch = 0.0f;

	SetActorRotation(NewLookAt);

	//��ʱ��3��
	//����ɵļ�ʱ��,����ظ�������
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

