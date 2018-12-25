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

	//���¼�
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

	//��otherActorȫ��ת��ΪAcharacter�����䡣
	ACharacter *OtherCharactor = Cast<ACharacter>(OtherActor);
	if (OtherCharactor!=nullptr)
	{
		//ʹ��ת�Ƕ�ת��Ϊ����ʸ��ǿ��.���۴��ĸ��������뷢��ƽ̨������ȷ������һ�¡�
		OtherCharactor->LaunchCharacter(LaunchVelocity, true, true);
		//������Ч��
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	//����Ӵ��Ĳ�����ң����Ӵ�������ǿջ�������ģ��������ͬ��������������������
	else if(OtherComp!=nullptr && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		//������Ч
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}


