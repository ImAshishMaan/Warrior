#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 AWarriorWeaponBase* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon) {
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if(bRegisterAsEquippedWeapon) {
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const {
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet)) {
		if(AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet)) {
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const {
	if(!CurrentEquippedWeaponTag.IsValid()) {
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType) {
	if(ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon) {
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		
		check(WeaponToToggle);
		
		if(bShouldEnable) {
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Debug::Print(FString::Printf(TEXT("Setting collision for %s"), *WeaponToToggle->GetFName().ToString()));
		}else {
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Debug::Print(FString::Printf(TEXT("Setting no collision for %s"), *WeaponToToggle->GetFName().ToString()));
		}
	}
}
