#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCHideComponent.generated.h"


class UCapsuleComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UNPCHideComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNPCHideComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	FName Tag = "skeletal_mesh_component";

private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								 const FHitResult& SweepResult);

	UFUNCTION()
	void Check(AActor* OtherActor , bool IsVisibility);

private:	
	virtual void BeginPlay() override;

};
