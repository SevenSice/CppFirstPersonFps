// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponents"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponents"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);
}



void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap with extraction zone !"));

	AFPSCharacter *MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		return;
	}
	//如果携带有物品，则触发事件，否则发出声音
	if (MyPawn->bIsCarryingObjective == true)
	{
		AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		//判断gamemode是否可用
		if (GM)
		{
			GM->CompleteMission(MyPawn,true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

}
