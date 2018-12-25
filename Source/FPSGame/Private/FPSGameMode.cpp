// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn *InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpactatingViewPointClass != nullptr)
		{
			TArray<AActor*> ReturnedActors;
			//��ȡ�����е����������
			UGameplayStatics::GetAllActorsOfClass(this, SpactatingViewPointClass, ReturnedActors);

			//������Ч��actor���͸ı��ӽ�
			if (ReturnedActors.Num() > 0)
			{
				AActor *NewViewTarget = ReturnedActors[0];

				//�����ҿ�����
				APlayerController *PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC != nullptr)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("SpactatingViewPointClass is nullptr. Please update GameMode class valid subclass. can not change spectating view target."))
		}

	}
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);

	
}

	