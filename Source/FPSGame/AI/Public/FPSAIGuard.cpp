// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnPawnSeen(APawn *SeenPawn)
{
	if (SeenPawn==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SeenPawn is null !"));
		return;
	}
	//����Բ�����򣬰뾶32������12����ɫ��ɫ��������ߣ��־����ߣ��񣬳���ʱ��10�롣
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Blue, false, 10.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

