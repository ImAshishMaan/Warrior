#include "Characters/WarriorEnemyCharacter.h"

#include "WarriorDebugHelper.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter() {
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 180, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const {
	return EnemyCombatComponent;
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	InitEnemyStartData();
}

void AWarriorEnemyCharacter::InitEnemyStartData() {
	if(CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]() {
			if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get()) {
				LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);

			}
		})
	);
}
