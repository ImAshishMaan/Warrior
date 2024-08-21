#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent {
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, const CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc> void UWarriorInputComponent::BindNativeInputAction(
	const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	UserObject* ContextObject, const CallbackFunc Func) {
	
	checkf(InInputConfig, TEXT("Input config is null"));
	if(UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag)) {
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
	
}

template <class UserObject, typename CallbackFunc> void UWarriorInputComponent::BindAbilityInputAction(
	const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc,
	CallbackFunc InputReleasedFunc) {
	
	checkf(InInputConfig, TEXT("Input config is null"));
	
	for(const FWarriorInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions) {
		if(!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
	
}
