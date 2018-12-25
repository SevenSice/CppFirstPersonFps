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

	//弹射区域
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent *OverlapComp = nullptr;

	//弹射的力度
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength = 0;

	//弹射的角度
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle = 0;
	//EditInstanceOnly 是为了让在世界中调整。
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		UParticleSystem *ActivateLaunchPadEffect = nullptr;

	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
