// Copyright Pamor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EEffectDurationType
{
	Instant,
	Duration,
	Infinite
};

USTRUCT(BlueprintType)
struct FGameplayEffectLayer
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectDurationType EffectDurationType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	int32 EffectLevel = 1;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FGameplayEffectLayer> GameplayEffects;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, int32 GameplayEffectIndex);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor, int32 GameplayEffectIndex);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor, int32 GameplayEffectIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;



};
