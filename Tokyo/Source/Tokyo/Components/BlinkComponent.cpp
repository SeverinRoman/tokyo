#include "BlinkComponent.h"

#include "TweenContainer.h"
#include "TweenManagerComponent.h"
#include "Tweens/TweenFloat.h"


UBlinkComponent::UBlinkComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlinkComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UBlinkComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();

	if (Owner)
	{
		SkeletalMeshComponent = Owner->FindComponentByTag<USkeletalMeshComponent>(Tag);
	}
	ScheduleNextBlink();
}

void UBlinkComponent::ScheduleNextBlink()
{
	if (World)
	{
		float RandomDelay = FMath::FRandRange(Delay.X, Delay.Y);
		World->GetTimerManager().SetTimer(BlinkTimerHandle, this, &UBlinkComponent::Blink, RandomDelay, false);
	}
}

void UBlinkComponent::Blink()
{
	if (!SkeletalMeshComponent) return;
	
	UTweenContainer* Container = UTweenManagerComponent::CreateTweenContainerStatic();
	
	if (Container)
	{
		UTweenFloat* TweenStart = Container->AppendTweenCustomFloat(this, 0.f, 1.f, Speed, Easing);
		
		if (TweenStart)
		{
		    	TweenStart->OnTweenUpdateDelegate.BindLambda([this](UTweenFloat* TweenFloat)
            		{
            			float Value = TweenFloat->GetCurrentValue();
            			SkeletalMeshComponent->SetMorphTarget(Morph, Value);
            		});
		}
    
    	UTweenFloat* TweenEnd = Container->AppendTweenCustomFloat(this, 1.f, 0.f, Speed, Easing);
    	
    	if (TweenEnd)
    	{
    	    	TweenEnd->OnTweenUpdateDelegate.BindLambda([this](UTweenFloat* TweenFloat)
            		{
            			float Value = TweenFloat->GetCurrentValue();
            			SkeletalMeshComponent->SetMorphTarget(Morph, Value);
            		});
            	
            	TweenEnd->OnTweenEndDelegate.BindLambda([this](UTweenFloat* TweenFloat)
            	{
            		float Value = TweenFloat->GetCurrentValue();
            		ScheduleNextBlink();
            	});
    	}
	}
}

