#include "NPCSkinComponent.h"

#include "GameFramework/Character.h"


UNPCSkinComponent::UNPCSkinComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPCSkinComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UNPCSkinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNPCSkinComponent::Init()
{
	Owner = GetOwner();

	if (Owner)
	{
		// Character = Cast<ACharacter>(Owner);
		//
		// if (Character)
		// {
		// 	SkeletalMeshComponent = Character->GetMesh();
		// }

		SkeletalMeshComponent = Owner->FindComponentByTag<USkeletalMeshComponent>(Tag);
	}

	if (Skin != ESkinsType::NONE)
	{
		SetSkin(Skin);
	}
	else
	{
		SetSkin(GetRandomSkin());
	}
}

void UNPCSkinComponent::SetSkin(ESkinsType SkinsType)
{
	if (SkinsType == ESkinsType::NONE) return;
	if (!SkeletalMeshComponent) return;
	if (!SkinConfigs.Contains(SkinsType)) return;

	SkeletalMeshComponent->SetSkeletalMesh(SkinConfigs[SkinsType].SkeletalMesh);
}

ESkinsType UNPCSkinComponent::GetRandomSkin()
{
	TArray<ESkinsType> RandomSkins;
	
	for (const TPair<ESkinsType, FSkinConfig>& Pair : SkinConfigs)
	{
		const ESkinsType SkinType = Pair.Key;
		const FSkinConfig& Config = Pair.Value;

		if (Config.IsRandom)
		{
			RandomSkins.Add(SkinType);
		}
	}

	if (RandomSkins.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, RandomSkins.Num() - 1);
		return RandomSkins[RandomIndex];
	}

	return ESkinsType::NONE;
}

