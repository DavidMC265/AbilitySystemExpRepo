#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MainAbilitySystemComponent.generated.h"

UCLASS()
class ABILITYSYSTEMEXP_API UMainAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
    virtual void OnRep_ActivateAbilities() override;

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level);

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);

private:
    void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};