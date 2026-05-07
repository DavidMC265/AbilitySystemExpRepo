#include "UI/MainWidgetComponent.h"
#include "Characters/BaseCharacter.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "UI/AttributeWidget.h"
#include "Blueprint/WidgetTree.h"

void UMainWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    InitAbilitySystemData();
    
    if (!IsASCInitialized())
    {
        if (OwnerCharacter.IsValid())
        {
            OwnerCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
            return;
        }
    }

    InitializeAttributeDelegate();
}

void UMainWidgetComponent::InitAbilitySystemData()
{
    OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
    AttributeSet = Cast<UMainAttributeSet>(OwnerCharacter->GetAttributeSet());
    AbilitySystemComponent = Cast<UMainAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
}

bool UMainWidgetComponent::IsASCInitialized() const
{
    return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UMainWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    AbilitySystemComponent = Cast<UMainAbilitySystemComponent>(ASC);
    AttributeSet = Cast<UMainAttributeSet>(AS);

    if (!IsASCInitialized()) return;
    InitializeAttributeDelegate();
}

void UMainWidgetComponent::InitializeAttributeDelegate()
{
    if (!AttributeSet->bAttributeInitialized)
    {
        AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
    }
    else
    {
        BindToAttributeChanges();
    }
}

void UMainWidgetComponent::BindToAttributeChanges()
{
    for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
    {
        BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object
        GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
        {
            BindWidgetToAttributeChanges(ChildWidget, Pair);
        });
    }
}

void UMainWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
    UAttributeWidget* AttributeWidget = Cast<UAttributeWidget>(WidgetObject);
    if (!IsValid(AttributeWidget)) return; // We only care about AttributeWidgets
    if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only Subscribe to matching attributes

    AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get()); // for initial values

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangedData)
    {
        AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get()); // For changes during the game
    });
}