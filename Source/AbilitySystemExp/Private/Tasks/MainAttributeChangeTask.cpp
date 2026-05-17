#include "Tasks/MainAttributeChangeTask.h"
#include "AbilitySystemComponent.h"

UMainAttributeChangeTask* UMainAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
    UMainAttributeChangeTask* WaitForAttributeChangeTask = NewObject<UMainAttributeChangeTask>();
    WaitForAttributeChangeTask->ASC = AbilitySystemComponent;
    WaitForAttributeChangeTask->AttributeToListenFor = Attribute;

    if (!IsValid(AbilitySystemComponent))
    {
        WaitForAttributeChangeTask->RemoveFromRoot();
        return nullptr;
    }

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &UMainAttributeChangeTask::AttributeChanged);

    return WaitForAttributeChangeTask;
}

void UMainAttributeChangeTask::EndTask()
{
    if (ASC.IsValid())
    {
        ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
    }

    SetReadyToDestroy();
    MarkAsGarbage();
}

void UMainAttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
    OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}