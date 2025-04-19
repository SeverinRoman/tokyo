#include "MoveComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "StateComponent.h"
#include "AnimationComponent.h"

#include "TweenContainer.h"
#include "TweenManagerComponent.h"
#include "Tweens/TweenFloat.h"


class UTweenContainer;

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckMoveToLocationComplete();
}

void UMoveComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	Character = Cast<ACharacter>(Owner);
	
	if (Character)
	{
		Controller = Character->GetController();
	}
	
	CharacterMovementComponent = Owner->GetComponentByClass<UCharacterMovementComponent>();
	StateComponent = Owner->GetComponentByClass<UStateComponent>();
	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
	
	switch (StartMove) {
	case EMoveType::NONE:
		break;
	case EMoveType::WALK:
		Walk();
		break;
	case EMoveType::RUN:
		Run();
		break;
	}

	if (CharacterMovementComponent)
	{
		SaveRotationRate = CharacterMovementComponent->RotationRate;
	}
}

void UMoveComponent::Run()
{
	if(CharacterMovementComponent)
	{
		SmoothChangeMaxWalkSpeed(RunSpeed);
	}

	CurrentMove = EMoveType::RUN;
	OnChangeMove.Broadcast(EMoveType::RUN);
}

void UMoveComponent::Walk()
{
	if(CharacterMovementComponent)
	{
		SmoothChangeMaxWalkSpeed(WalkSpeed);
	}
	
	CurrentMove = EMoveType::WALK;
	OnChangeMove.Broadcast(EMoveType::WALK);
}

void UMoveComponent::ToggleRotation(bool bIsEnable)
{
	if (bIsEnable == IsEnableRotation) return;

	if (bIsEnable)
	{
		CharacterMovementComponent->RotationRate = SaveRotationRate;
	}
	else
	{
		CharacterMovementComponent->RotationRate = FRotator::ZeroRotator;
	}
	
	IsEnableRotation = bIsEnable;
}

void UMoveComponent::ToggleMontageRotation(bool bIsEnable)
{
	if (!CharacterMovementComponent) return;
	
	CharacterMovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = bIsEnable;
}

void UMoveComponent::Move(float X, float Y)
{
	if (StateComponent)
	{
		EStateType State = StateComponent->GetState();

		if (State != EStateType::IDLE && State != EStateType::WALK && State != EStateType::RUN && State != EStateType::STANDBY) return;
	}
	
	if (Character)
	{
		FRotator RotatorX = Character->GetControlRotation();
		RotatorX.Pitch = 0.f;
		RotatorX.Roll = 0.f;
		
		FVector DirectionX = UKismetMathLibrary::GetForwardVector(RotatorX);

		
		FRotator RotatorY = Character->GetControlRotation();
		RotatorY.Pitch = 0.f;
		
		FVector DirectionY = UKismetMathLibrary::GetRightVector(RotatorY);


		Character->AddMovementInput(DirectionX, X);
		Character->AddMovementInput(DirectionY, Y);
	}

	StopMoveToLocation();
	StopStandBy();
}

void UMoveComponent::StopMoveToLocation()
{
	if (!IsMoveToLocation) return;
	IsMoveToLocation = false;
	
	Controller->StopMovement();
	OnMoveToLocationFailed.Broadcast();
}

void UMoveComponent::SmoothChangeMaxWalkSpeed(float Value)
{
	if (!CharacterMovementComponent) return;
	
	if (SmoothTween)
	{
		SmoothTween->DeleteTween();
	}

	float Current = CharacterMovementComponent->MaxWalkSpeed;

	UTweenContainer* Container = UTweenManagerComponent::CreateTweenContainerStatic();
	if (!Container) return;
	
	SmoothTween = Container->AppendTweenCustomFloat(this, Current, Value, SmoothDuration, SmoothEase);

	SmoothTween->OnTweenUpdateDelegate.BindLambda([this](UTweenFloat* TweenFloat)
	{
		float CurrentValue = TweenFloat->GetCurrentValue();

		CharacterMovementComponent->MaxWalkSpeed = CurrentValue;
	});
}

void UMoveComponent::MoveToLocation(FVector Location)
{
	if (IsMoveToLocation) return;
	IsMoveToLocation = true;

	LocationToMove = Location;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Location);
}

void UMoveComponent::MoveToActor(AActor* Actor)
{
	if (IsMoveToLocation) return;
	if (!Actor) return;
	MoveActor = Actor;

	IsMoveToLocation = true;
	
	LocationToMove = Actor->GetActorLocation();
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Actor);
}

void UMoveComponent::CheckMoveToLocationComplete()
{
	if (!IsMoveToLocation) return;
	if (!Owner) return;

	if (MoveActor)
	{
		LocationToMove = MoveActor->GetActorLocation();
	}

	float Distance = FVector::Distance(Owner->GetActorLocation(), LocationToMove);
	
	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("My Location is: %f"), Distance));
	}
	
	if (Distance <= DistanceMoveToLocationComplete)
	{
		IsMoveToLocation = false;
		MoveActor = nullptr;
		OnMoveToLocationComplete.Broadcast();

		if (IsDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("UMoveComponent::CheckMoveToLocationComplete MoveToLocationComplete "));
		}
	}
}

void UMoveComponent::StopStandBy()
{
	if (!AnimationComponent || !StateComponent) return;

	if (StateComponent->GetState() == EStateType::STANDBY)
	{
		AnimationComponent->Stop();
		StateComponent->SetState(EStateType::IDLE);
	}
}

void UMoveComponent::StopAnimation()
{
	if (!AnimationComponent || !StateComponent) return;

	EStateType State = StateComponent->GetState();
	if (State == EStateType::IDLE)
	{
		AnimationComponent->Stop();
	}
}

FVector UMoveComponent::GetVelocity()
{
	if (CharacterMovementComponent)
	{
		return  CharacterMovementComponent->Velocity;
	}
	return FVector::ZeroVector;
}
