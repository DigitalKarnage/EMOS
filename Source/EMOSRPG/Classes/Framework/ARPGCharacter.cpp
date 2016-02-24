/* 
	All rights reserved. Copyright (c) 2015-2016, DigitalKarnage	

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <EMOSRPG.h>

#include <Framework/Enumerations/ERPGCharacterType.h>
#include <Framework/ARPGCharacter.h>

ARPGCharacter::ARPGCharacter(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	this->bReplicates = true;
	this->bReplicateMovement = true;
	this->bRelevantForNetworkReplays = true;

	this->PrimaryActorTick.bCanEverTick = true;	
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.0f;

	this->RPGCombatComponent = objectInitializer.CreateDefaultSubobject<URPGCombatComponent>(this, "RPG Combat Component");
	this->RPGCombatComponent->Name = FString("Default Character");
	this->RPGCombatComponent->CharacterType = ERPGCharacterType::NPC;	

	this->CharacterNameWidget = objectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, "Character Name Widget Compoennt");
	this->CharacterNameWidget->CreationMethod = EComponentCreationMethod::Native;
	this->CharacterNameWidget->AttachTo(GetCapsuleComponent(), NAME_None, EAttachLocation::KeepRelativeOffset, false);
	this->CharacterNameWidget->SetMaxInteractionDistance(0.0f);	
	
	OnTargetOpponentStatsChangedBinding = FScriptDelegate();
	OnTargetOpponentStatsChangedBinding.BindUFunction(this, "OnTargetOpponentStatsChanged");
}

void ARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (this->GetMesh() != NULL)
	{
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	}		

	// Make sure that we have enough time to get replicated data from the server ...
	this->NetCullDistanceSquared = FMath::Pow(this->RPGCombatComponent->MaximumCharacterTargetDistance * 1.5f, 2.0f);
	
	if (this->BaseCharacterData != NULL)
	{
		RPGCombatComponent->CharacterType = BaseCharacterData->CharacterType;
		RPGCombatComponent->bCanBeInspected = BaseCharacterData->bCanBeInspected;
		RPGCombatComponent->CurrentLevel = BaseCharacterData->CurrentLevel;
		RPGCombatComponent->CurrentHealth = BaseCharacterData->CurrentHealth;
		RPGCombatComponent->MaximumHealth = BaseCharacterData->MaximumHealth;
		RPGCombatComponent->CurrentMana = BaseCharacterData->CurrentMana;
		RPGCombatComponent->MaximumMana = BaseCharacterData->MaximumMana;
		RPGCombatComponent->CombatStats.AttackAgility = BaseCharacterData->AttackAgility;
		RPGCombatComponent->CombatStats.AttackRating = BaseCharacterData->AttackRating;
		RPGCombatComponent->CombatStats.BlockRate = BaseCharacterData->BlockRate;
		RPGCombatComponent->CombatStats.CastingAgility = BaseCharacterData->CastingAgility;
		RPGCombatComponent->CombatStats.CriticalChance = BaseCharacterData->CriticalChance;
		RPGCombatComponent->CombatStats.CriticalMultiplier = BaseCharacterData->CriticalMultiplier;
		RPGCombatComponent->CombatStats.CriticalReduction = BaseCharacterData->CriticalReduction;
		RPGCombatComponent->CombatStats.CriticalResistance = BaseCharacterData->CriticalResistance;
		RPGCombatComponent->CombatStats.DefenseRating = BaseCharacterData->DefenseRating;
		RPGCombatComponent->CombatStats.EvadeRate = BaseCharacterData->EvadeRate;
		RPGCombatComponent->CombatStats.HPRegenRate = BaseCharacterData->HPRegenRate;
		RPGCombatComponent->CombatStats.HPRegenRateAmount = BaseCharacterData->HPRegenRateAmount;
		RPGCombatComponent->CombatStats.MagicalDefense = BaseCharacterData->MagicalDefense;
		RPGCombatComponent->CombatStats.MaximumMagicalAttack = BaseCharacterData->MaximumMagicalAttack;
		RPGCombatComponent->CombatStats.MaximumPhysicalAttack = BaseCharacterData->MaximumPhysicalAttack;
		RPGCombatComponent->CombatStats.MinimumMagicalAttack = BaseCharacterData->MinimumMagicalAttack;
		RPGCombatComponent->CombatStats.MinimumPhysicalAttack = BaseCharacterData->MinimumPhysicalAttack;
		RPGCombatComponent->CombatStats.MovementAgility = BaseCharacterData->MovementAgility;
		RPGCombatComponent->CombatStats.MPRegenRate = BaseCharacterData->MPRegenRate;
		RPGCombatComponent->CombatStats.MPRegenRateAmount = BaseCharacterData->MPRegenRateAmount;
		RPGCombatComponent->CombatStats.PhysicalDefense = BaseCharacterData->PhysicalDefense;
		RPGCombatComponent->CombatStats.Strength = BaseCharacterData->Strength;
	}
}

void ARPGCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ARPGCharacter, RPGCombatComponent, COND_OwnerOnly);
}

void ARPGCharacter::Tick(float delta)
{
	Super::Tick(delta);

#if defined(UE_EDITOR) || defined (UE_SERVER)

	if (Role >= ROLE_Authority && CharacterTargets.Num() > 0)
	{
		static FVector targetLocation;
		static FVector currentLocation;

		TArray<APawn*> keys;
		CharacterTargets.GetKeys(keys);

		for (int i = keys.Num() - 1; i >= 0; i--)
		{
			targetLocation = keys[i]->GetActorLocation();
			currentLocation = GetActorLocation();

			if (FMath::Abs((targetLocation - currentLocation).Size()) >= this->RPGCombatComponent->MaximumCharacterTargetDistance)
				ClearTargetAtIndex(i);
		}
	}

#endif

#if defined(UE_EDITOR) || defined(UE_GAME)
	
	if (this->CharacterNameWidget != NULL && CharacterNameWidget->GetUserWidgetObject() != NULL && (this->RPGCombatComponent != NULL && RPGCombatComponent->MaximumCharacterTargetDistance > 0))
	{
		static UUserWidget* nameWidget = nullptr;
		static APlayerController* localPlayer = nullptr;

		nameWidget = CharacterNameWidget->GetUserWidgetObject();
		localPlayer = GWorld->GetFirstPlayerController();

		if (localPlayer != NULL && localPlayer->PlayerCameraManager != NULL)
		{
			FVector cameraLocation = FVector::ZeroVector;
			FRotator cameraRotation = FRotator();

			localPlayer->PlayerCameraManager->GetCameraViewPoint(cameraLocation, cameraRotation);

			auto characterNameLocation = CharacterNameWidget->GetComponentLocation();
			auto nameDrawDistance = (characterNameLocation - cameraLocation).Size();

			if (nameDrawDistance <= MaxNameDrawDistance)
			{
				auto queryParams = FCollisionQueryParams::DefaultQueryParam;
				FHitResult actorHitResult;

				queryParams.AddIgnoredActor(this);
				queryParams.bTraceComplex = true;

				auto bIsHit = GWorld->LineTraceSingleByChannel(actorHitResult, cameraLocation, characterNameLocation, ECollisionChannel::ECC_Visibility, queryParams);

				CharacterNameWidget->SetVisibility(!bIsHit, false);
			}
			else CharacterNameWidget->SetVisibility(false, false);
		}
	}

#endif

}

void ARPGCharacter::GetCharacterStats_Implementation(FRPGCharacterStats& result)
{
	if (this->RPGCombatComponent)
		this->RPGCombatComponent->GetCharacterStats(result);
}

void ARPGCharacter::GetCombatStats_Implementation(FRPGCombatStats& result)
{
	if (this->RPGCombatComponent)
		result = this->RPGCombatComponent->CombatStats;
}

void ARPGCharacter::GetTargetStatsAtIndex_Implementation(const int32 index, FRPGCharacterStats& result)
{
	TArray<APawn*> keys;
	CharacterTargets.GetKeys(keys);

	if (keys.Num() > index)
		CharacterTargets.FindRef(keys[index])->GetCharacterStats(result);

	else if (keys.Num() > 0)
		CharacterTargets.FindRef(keys.Last())->GetCharacterStats(result);
}

void ARPGCharacter::TargetOpponent(APawn* target)
{
	if (target != NULL && !CharacterTargets.Contains(target))
	{
		if (target->GetClass()->ImplementsInterface(URPGCombatInterface::StaticClass()))
		{
			if (CharacterTargets.Num() != 0 && !this->RPGCombatComponent->bAllowMultipleTargets)
			{
				TArray<APawn*> keys;

				CharacterTargets.GetKeys(keys);
				CharacterTargets.FindRef(keys[0])->DelegateOnCharacterStatsChanged.Remove(OnTargetOpponentStatsChangedBinding);
				CharacterTargets.Remove(keys[0]);
			}

			CharacterTargets.Add(target, Cast<IRPGCombatInterface>(target)->Execute_GetCombatComponent(target));

			FRPGCharacterStats targetCharacterStats;
			auto targetCombatComponent = CharacterTargets.FindRef(target);

			targetCombatComponent->DelegateOnCharacterStatsChanged.Add(OnTargetOpponentStatsChangedBinding);
			targetCombatComponent->GetCharacterStats(targetCharacterStats);

			if (Role < ROLE_Authority || !IsRunningDedicatedServer())
				OnTargetOpponentStatsChanged(targetCombatComponent, targetCharacterStats, ERPGStatsUpdateType::All);

#if defined (UE_EDITOR) || defined(UE_GAME)
			
				// Update the servers version of character targets based on the clients say so, but re-verify that the target is within the exceptable range
				if (Role < ROLE_Authority)
					Server_TargetOpponent(target);
#endif

		}
	}
}

void ARPGCharacter::ClearTargets()
{
	if (CharacterTargets.Num() != 0)
	{
		TArray<APawn*> keys;
		CharacterTargets.GetKeys(keys);

		for (int i = keys.Num() - 1; i >= 0; i--)
			ClearTarget(keys[i]);
	}
}

void ARPGCharacter::ClearTarget(APawn* pawn)
{
	if (pawn != NULL && CharacterTargets.Contains(pawn))
	{
		TArray<APawn*> keys;
		CharacterTargets.GetKeys(keys);

		for (int i = 0; i < keys.Num(); i++)
		{
			if (keys[i] == pawn)
			{
				ClearTargetAtIndex(i);
				break;
			}
		}
	}
}

void ARPGCharacter::ClearTargetAtIndex(const int32& index)
{
	TArray<APawn*> keys;
	CharacterTargets.GetKeys(keys);

	if (keys.Num() > index)
	{
		CharacterTargets.FindRef(keys[index])->DelegateOnCharacterStatsChanged.Remove(OnTargetOpponentStatsChangedBinding);
		CharacterTargets.Remove(keys[index]);

		FRPGCharacterStats characterStats;
		this->RPGCombatComponent->TriggerOnTargetCharacterStatsChanged(index, characterStats, ERPGStatsUpdateType::All);

#if defined(UE_EDITOR) || defined(UE_SERVER)

		if (Role >= ROLE_Authority)
			Client_TargetLost(keys[index]);	
#endif

	}
}

void ARPGCharacter::OnTargetOpponentStatsChanged(URPGCombatComponent* combatComponent, FRPGCharacterStats& result, const ERPGStatsUpdateType type)
{
	if (this->RPGCombatComponent != NULL)
	{
		if (this->RPGCombatComponent->bAllowMultipleTargets)
		{
			TArray<APawn*> keys;
			CharacterTargets.GetKeys(keys);

			for (int i = 0; i < keys.Num(); i++)
			{
				if (CharacterTargets.FindRef(keys[i]) == combatComponent)
				{
					this->RPGCombatComponent->TriggerOnTargetCharacterStatsChanged(i, result, type);
					break;
				}
			}
		}
		else if (CharacterTargets.Num() > 0)
			this->RPGCombatComponent->TriggerOnTargetCharacterStatsChanged(0, result, type);
	}
}

bool ARPGCharacter::Server_TargetOpponent_Validate(APawn* target)
{

	return true;
}

void ARPGCharacter::Server_TargetOpponent_Implementation(APawn* target)
{
	this->TargetOpponent(target);
}

void ARPGCharacter::Client_TargetLost_Implementation(APawn* pawn)
{
	this->ClearTarget(pawn);
}

URPGCombatComponent* ARPGCharacter::GetCombatComponent_Implementation() { return this->RPGCombatComponent; }
