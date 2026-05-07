#include "UI/AttributeWidget.h"

bool UAttributeWidget::MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
    return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}

void UAttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UMainAttributeSet* AttributeSet)
{
    const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet);
    const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);

    BP_OnAttributeChanged(AttributeValue, MaxAttributeValue);
}