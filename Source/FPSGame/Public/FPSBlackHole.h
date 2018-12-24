// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent *MeshComp = nullptr;

	/*内圈，用来销毁物体*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent *InnerSphereComponent = nullptr;

	/*外圈用于施加一个向心力*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent *OuterSphereComponent = nullptr;

	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent *OverlappedComponent,AActor *OtherActor, UPrimitiveComponent *OtherComp,
			int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
