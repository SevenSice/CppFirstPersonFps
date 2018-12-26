// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState :uint8
{
	Idle,
	Suspicious,
	Alerted
};

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

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent *PawnSensingComp;

	FRotator OriginalRotation = FRotator(0, 0, 0);

	FTimerHandle TimerHandle_ResetOrientation;

	UFUNCTION()
		void OnPawnSeen(APawn *SeenPawn);

	//Instigator����ΪNoiseInstigator����Ȼ����Actor�����Instigator���Գ�ͻ��
	UFUNCTION()
		void OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume);

	//���ý�ɫ����
	UFUNCTION()
		void ResetOrientation();

	EAIState GuardState = EAIState::Idle;
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol = false;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor *FirstPatrolPoint = nullptr;
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor *SecondPatrolPoint = nullptr;
	//��ɫ�����ƶ�����ֹͣ�ĵ�ǰ�ĵ�
	UPROPERTY()
		AActor *CurrentPatrolPoint = nullptr;
	
	void MoveToNextPatrolPoint();
};
