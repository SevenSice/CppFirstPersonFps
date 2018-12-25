// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxOverlapComponent"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComp;

	//绑定事件
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OverlapLaunchPad);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComp->SetupAttachment(OverlapComp);

	LaunchStrength = 1500.0f;
	LaunchPitchAngle = 35.0f;
}

void AFPSLaunchPad::OverlapLaunchPad(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector()*LaunchStrength;

	//将otherActor全部转化为Acharacter，弹射。
	ACharacter *OtherCharactor = Cast<ACharacter>(OtherActor);
	if (OtherCharactor!=nullptr)
	{
		//使旋转角度转换为方向矢量强度.无论从哪个方向走入发射平台，都能确保速率一致。
		OtherCharactor->LaunchCharacter(LaunchVelocity, true, true);
		//产生特效。
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	//如果接触的不是玩家，所接触的组件非空或者正在模拟物理，则同样给个弹力（推力）。
	else if(OtherComp!=nullptr && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		//产生特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}


