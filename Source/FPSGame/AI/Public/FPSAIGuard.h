// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;


UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent *PawnSensingComp;

	FRotator OriginalRotation = FRotator(0, 0, 0);

	FTimerHandle TimerHandle_ResetOrientation;

	UFUNCTION()
	void OnPawnSeen(APawn *SeenPawn);

	//Instigator命名为NoiseInstigator，不然会与Actor里面的Instigator属性冲突。
	UFUNCTION()
	void OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume);

	//重置角色朝向
	UFUNCTION()
	void ResetOrientation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
