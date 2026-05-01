#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MainGameplayAbility.generated.h"


UCLASS()
class ABILITYSYSTEMEXP_API UMainGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bDrawDebugs = false;
};
