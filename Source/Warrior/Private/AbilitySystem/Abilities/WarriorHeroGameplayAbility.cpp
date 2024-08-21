#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/HeroController.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo() {
	if(!CachedWarriorHeroCharacter.IsValid()) {
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(GetAvatarActorFromActorInfo());
	}
	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

AHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo() {
	if(!CachedWarriorHeroController.IsValid()) {
		CachedWarriorHeroController = GetHeroCharacterFromActorInfo() ? Cast<AHeroController>(GetHeroCharacterFromActorInfo()->GetController()) : nullptr;
	}
	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo() {
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
