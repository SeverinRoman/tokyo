#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCSkinComponent.generated.h"


UENUM(BlueprintType)
enum class ESkinsType : uint8
{
	NONE = 0,

	SKIN_0 = 1,
	SKIN_1 = 2,
	SKIN_2 = 3,
	SKIN_3 = 4,
	SKIN_4 = 5,
	SKIN_5 = 6,
	SKIN_6 = 7,
	SKIN_7 = 8,
};


USTRUCT(BlueprintType)
struct FSkinConfig
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	bool IsRandom = true;
	
};


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKYO_API UNPCSkinComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNPCSkinComponent();
	
private:
	UPROPERTY(EditAnywhere)
	TMap<ESkinsType, FSkinConfig> SkinConfigs;

	UPROPERTY(EditDefaultsOnly)
	ESkinsType Skin = ESkinsType::NONE;

private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void SetSkin(ESkinsType SkinsType);
	
	UFUNCTION()
	ESkinsType GetRandomSkin();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
