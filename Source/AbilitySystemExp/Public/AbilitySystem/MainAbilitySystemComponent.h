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

private:
    void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};