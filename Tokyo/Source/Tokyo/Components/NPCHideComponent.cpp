#include "NPCHideComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UNPCHideComponent::UNPCHideComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPCHideComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}



void UNPCHideComponent::Init()
{
	Owner = GetOwner();

	if (Owner)
	{
		SkeletalMeshComponent = Owner->FindComponentByTag<USkeletalMeshComponent>(Tag);

		CapsuleComponent = Owner->GetComponentByClass<UCapsuleComponent>();

		if (CapsuleComponent)
		{
			CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UNPCHideComponent::OnComponentBeginOverlap);
			CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UNPCHideComponent::OnComponentEndOverlap);
		}
	}
}

void UNPCHideComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Check(OtherActor, false);
}

void UNPCHideComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Check(OtherActor, true);
}

void UNPCHideComponent::Check(AActor* OtherActor , bool IsVisibility)
{
	if (!OtherActor) return;

	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character && SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetVisibility(IsVisibility);
	}
}

