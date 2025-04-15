#include "StateComponent.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "MoveComponent.h"


UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Update();
}

void UStateComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();
	
	if (Owner)
	{
		MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
		CharacterMovementComponent = Owner->GetComponentByClass<UCharacterMovementComponent>();
	}

	if (World)
	{
		World->GetTimerManager().SetTimerForNextTick([this](){ SetState(EStateType::IDLE); });
	}

	if (MoveComponent)
	{
		WalkSpeed = MoveComponent->GetWalkSpeed();
		RunSpeed = MoveComponent->GetRunSpeed();
	}
}

void UStateComponent::SetState(EStateType NewState)
{
	if (State == NewState) return;

	ChangeState();
	
	State = NewState;
	OnStateChange.Broadcast(NewState);
}

void UStateComponent::ChangeState()
{
	if (State == EStateType::NONE) return;
	if (!MoveComponent) return;

	if (State == EStateType::FALLING)
	{
		MoveComponent->ToggleRotation(true);
	}
}

void UStateComponent::Update()
{
	if (!Owner) return;
	if (!CharacterMovementComponent) return;
	
	UpdateData();
	UpdateState();
	Debug();
}

void UStateComponent::UpdateData()
{
	Velocity = CharacterMovementComponent->Velocity;
	Speed = Velocity.Length();
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Owner->GetActorRotation());
}

void UStateComponent::UpdateState()
{
	if (CharacterMovementComponent->IsFalling())
	{
		SetState(EStateType::FALLING);
		
		if (MoveComponent)
		{
			MoveComponent->ToggleRotation(false);
		}
		return;
	}

	if (State == EStateType::IDLE || State == EStateType::WALK || State == EStateType::RUN || State == EStateType::FALLING)
	{
		if (Speed == 0.f)
		{
			SetState(EStateType::IDLE);
		}
		else if (Speed > 0.f && Speed <= WalkSpeed)
		{
			SetState(EStateType::WALK);
		}
		else if (Speed > WalkSpeed && Speed <= RunSpeed)
		{
			SetState(EStateType::RUN);
		}
	}
}

void UStateComponent::Debug()
{
	if (!IsDebug) return;

	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Green, FString::Printf(TEXT("Velocity is: %s"), *Velocity.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Green, FString::Printf(TEXT("Direction is: %f"), Direction));
	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Green, FString::Printf(TEXT("Speed is:  %f"), Speed));
	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Green, FString::Printf(TEXT("State is %s"), *UEnum::GetValueAsString(State)));
}

