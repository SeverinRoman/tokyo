#include "InteractComponent.h"

#include "Camera/CameraComponent.h"

#include "InteractInterface.h"
#include "Interfaces/InteractInterface.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UInteractComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteract();
}

void UInteractComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();

	if (!Owner) return;

	CameraComponent = Owner->GetComponentByClass<UCameraComponent>();
}

void UInteractComponent::CheckInteract()
{
	if (!World || !Owner || !CameraComponent) return;

	FHitResult OutHit;
	
	FVector Start =  Owner->GetActorLocation() + Owner->GetActorForwardVector() * Distance;

	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Owner);
	
	World->SweepSingleByChannel(OutHit, Start, Start, FQuat::Identity, CollisionChannel, CollisionShape, CollisionParams);
	
	if (IsDebug)
	{
		DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, FColor::Yellow, false, 0.05f);
	}

	AActor* Actor = OutHit.GetActor();

	if (!Actor) return;
	if (!Actor->Implements<UInteractInterface>()) return;

	IInteractInterface::Execute_CheckInteract(Actor);
}

void UInteractComponent::Interact()
{
	if (!World || !Owner || !CameraComponent) return;

	FHitResult OutHit;
	
	FVector Start =  Owner->GetActorLocation() + Owner->GetActorForwardVector() * Distance;

	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Owner);
	
	World->SweepSingleByChannel(OutHit, Start, Start, FQuat::Identity, CollisionChannel, CollisionShape, CollisionParams);
	
	if (IsDebug)
	{
		DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, FColor::Green, false, 0.05f);
	}

	AActor* Actor = OutHit.GetActor();

	if (!Actor) return;
	if (!Actor->Implements<UInteractInterface>()) return;

	IInteractInterface::Execute_Interact(Actor, Owner);
}
