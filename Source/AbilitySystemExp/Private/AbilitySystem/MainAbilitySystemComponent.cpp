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

void UMainAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
    if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

    if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
    {
        AbilitySpec->Level = Level;
        MarkAbilitySpecDirty(*AbilitySpec);
    }
}

void UMainAbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
    if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

    if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
    {
        AbilitySpec->Level += Level;
        MarkAbilitySpecDirty(*AbilitySpec);
    }
}