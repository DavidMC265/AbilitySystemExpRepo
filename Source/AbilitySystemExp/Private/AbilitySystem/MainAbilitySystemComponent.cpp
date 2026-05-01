#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Gameplay Tags/MainTags.h"

void UMainAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    HandleAutoActivatedAbility(AbilitySpec);
}

void UMainAbilitySystemComponent::OnRep_ActivateAbilities()
{
    Super::OnRep_ActivateAbilities();

    FScopedAbilityListLock ActivateScopeLock(*this);
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        HandleAutoActivatedAbility(AbilitySpec);
    }
}

void UMainAbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
    if (!IsValid(AbilitySpec.Ability)) return;

    for (const FGameplayTag& Tag: AbilitySpec.Ability->GetAssetTags())
    {
        if (Tag.MatchesTagExact(MainTags::Abilities::ActivateOnGiven))
        {
            TryActivateAbility(AbilitySpec.Handle);
            return;
        }
    }
}