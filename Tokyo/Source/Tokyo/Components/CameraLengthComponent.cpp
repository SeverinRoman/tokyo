#include "CameraLengthComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "TweenContainer.h"
#include "Tweens/TweenFloat.h"


UCameraLengthComponent::UCameraLengthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCameraLengthComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UCameraLengthComponent::Init()
{
	Owner = GetOwner();

	if (Owner)
	{
		SpringArmComponent = Owner->GetComponentByClass<USpringArmComponent>();

		if (SpringArmComponent)
		{
			if (TargetArmLengths.Num() == 0) return;
			
			if (CurrentLengths >= TargetArmLengths.Num()) CurrentLengths = 0;
			
			SpringArmComponent->TargetArmLength = TargetArmLengths[StartLengths];
			CurrentLengths = StartLengths;
			CurrentLengths++;
		}
	}
}

void UCameraLengthComponent::Change()
{
	if (!SpringArmComponent) return;
	if (TargetArmLengths.Num() == 0) return;
	if (CurrentLengths >= TargetArmLengths.Num()) CurrentLengths = 0;
	
	TweenChange(TargetArmLengths[CurrentLengths]);
	CurrentLengths++;
}

void UCameraLengthComponent::TweenChange(float Value)
{
	if (!SpringArmComponent) return;
	
	float StartValue = SpringArmComponent->TargetArmLength;
	float EndValue = Value;

	if (TweenFloat)
	{
		TweenFloat->DeleteTween();
	}

	UTweenContainer* Container = UTweenManagerComponent::CreateTweenContainerStatic();
	if (!Container) return;
	
	TweenFloat = Container->AppendTweenCustomFloat(this, StartValue, EndValue, Duration, TweenEase);

	TweenFloat->OnTweenUpdateDelegate.BindLambda([this](UTweenFloat* TweenFloat)
	{
		float CurrentValue = TweenFloat->GetCurrentValue();

		SpringArmComponent->TargetArmLength = CurrentValue;
	});
}
