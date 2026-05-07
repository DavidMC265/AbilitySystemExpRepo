#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AttributeWidget.generated.h"

UCLASS()
class ABILITYSYSTEMEXP_API UAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttribute Attribute;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UMainAttributeSet* AttributeSet);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Changed"))
	void BP_OnAttributeChanged(float AttributeValue, float MaxAttributeValue);
	
};