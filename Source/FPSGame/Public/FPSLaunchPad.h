// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;


UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent *MeshComp = nullptr;

	//��������
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent *OverlapComp = nullptr;

	//���������
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength = 0;

	//����ĽǶ�
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle = 0;
	//EditInstanceOnly ��Ϊ�����������е�����
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		UParticleSystem *ActivateLaunchPadEffect = nullptr;

	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
