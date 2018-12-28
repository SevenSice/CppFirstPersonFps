// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "FPSGameState.h"
AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn *InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{

		if (SpactatingViewPointClass != nullptr)
		{
			TArray<AActor*> ReturnedActors;
			//获取世界中的摄像机对象
			UGameplayStatics::GetAllActorsOfClass(this, SpactatingViewPointClass, ReturnedActors);

			// //发现有效的actor，就改变视角
			//if (ReturnedActors.Num() > 0)
			//{
			//	AActor *NewViewTarget = ReturnedActors[0];

			//	//获得玩家控制器
			//	APlayerController *PC = Cast<APlayerController>(InstigatorPawn->GetController());
			//	if (PC != nullptr)
			//	{
			//		PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			//	}
			//}

			//与上面的代码功能相似，不同的是一个玩家触发转移视角，其他玩家也会强制转移，包括任务成功与失败。
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("SpactatingViewPointClass is nullptr. Please update GameMode class valid subclass. can not change spectating view target."))
		}

	}
	AFPSGameState *GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MultiCastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}
	 
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);

}

	