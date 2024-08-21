#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag) {
	if(!InputTag.IsValid()) return;
	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		TryActivateAbility(AbilitySpec.Handle);
	}
}
void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag) {
	
	
}
