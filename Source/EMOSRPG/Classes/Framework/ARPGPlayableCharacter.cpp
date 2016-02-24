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
#include <UMG.h>
#include <UMGStyle.h>

#include <Framework/Enumerations/ERPGCharacterType.h>
#include <Framework/ARPGPlayableCharacter.h>

ARPGPlayableCharacter::ARPGPlayableCharacter(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void ARPGPlayableCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();	

	CalculateCombatStatsFromProgressionData();
}

void ARPGPlayableCharacter::Tick(float delta)
{
	Super::Tick(delta);

#if defined(UE_EDITOR) || defined (UE_SERVER)

	if (Role >= ROLE_Authority)
	{
		auto startingLevel = this->RPGCombatComponent->CurrentLevel;
		
		if (RPGCombatComponent->MaximumExperience != 0)
		{
			if (RPGCombatComponent->CurrentExperience > RPGCombatComponent->MaximumExperience)
			{
				if (startingLevel < RPGCombatComponent->MaximumLevel)
				{
					do
					{
						RPGCombatComponent->CurrentLevel += (uint8)1;
						RPGCombatComponent->CurrentExperience = RPGCombatComponent->CurrentExperience - RPGCombatComponent->MaximumExperience;

						CalculateCombatStatsFromProgressionData();

						if (RPGCombatComponent->CurrentLevel == RPGCombatComponent->MaximumLevel)
							break;

					} while (RPGCombatComponent->CurrentExperience > RPGCombatComponent->MaximumExperience);

					this->RPGCombatComponent->CurrentExperience = FMath::Clamp(RPGCombatComponent->CurrentExperience, 0.0f, RPGCombatComponent->MaximumExperience);

					if (startingLevel != RPGCombatComponent->CurrentLevel)
					{
						// We increased our level, so make sure that we recalculate the combat stats
						RPGCombatComponent->RecalculateStats();

						// now we need to set the current health / mana values to the maximum values for this level
						RPGCombatComponent->CurrentHealth = RPGCombatComponent->MaximumHealth;
						RPGCombatComponent->CurrentMana = RPGCombatComponent->MaximumMana;

						// Trigger Event Level Upgraded

						mLastLevelIndex = RPGCombatComponent->CurrentLevel;
					}
				}
				else this->RPGCombatComponent->CurrentExperience = FMath::Clamp(RPGCombatComponent->CurrentExperience, 0.0f, RPGCombatComponent->MaximumExperience);
			}
		}
		else this->RPGCombatComponent->CurrentExperience = FMath::Clamp(RPGCombatComponent->CurrentExperience, 0.0f, RPGCombatComponent->MaximumExperience);
	}

	if (mLastLevelIndex != RPGCombatComponent->CurrentLevel)
	{
		mLastLevelIndex = RPGCombatComponent->CurrentLevel;
		RPGCombatComponent->CurrentExperience = 0;

		CalculateCombatStatsFromProgressionData();
		RPGCombatComponent->RecalculateStats();
	}

#endif
}

void ARPGPlayableCharacter::CalculateCombatStatsFromProgressionData()
{
	if (ProgressionData != NULL)
	{
		if (ProgressionData->ProgressionTable.Num() > 0)
		{
			auto levelIndex = FMath::Clamp((int32)RPGCombatComponent->CurrentLevel - 1, 0, ProgressionData->ProgressionTable.Num() - 1);
			auto progressionStats = ProgressionData->ProgressionTable[levelIndex];

			RPGCombatComponent->MaximumHealth = progressionStats.MaximumHealth;
			RPGCombatComponent->MaximumMana = progressionStats.MaximumMana;
			RPGCombatComponent->MaximumExperience = progressionStats.XPToLevel;
			RPGCombatComponent->CombatStats.AttackAgility = progressionStats.AttackAgility;
			RPGCombatComponent->CombatStats.AttackRating = progressionStats.AttackRating;
			RPGCombatComponent->CombatStats.BlockRate = progressionStats.BlockRate;
			RPGCombatComponent->CombatStats.CastingAgility = progressionStats.CastingAgility;
			RPGCombatComponent->CombatStats.CriticalChance = progressionStats.CriticalChance;
			RPGCombatComponent->CombatStats.CriticalMultiplier = progressionStats.CriticalMultiplier;
			RPGCombatComponent->CombatStats.CriticalReduction = progressionStats.CriticalReduction;
			RPGCombatComponent->CombatStats.CriticalResistance = progressionStats.CriticalResistance;
			RPGCombatComponent->CombatStats.DefenseRating = progressionStats.DefenseRating;
			RPGCombatComponent->CombatStats.Dexterity = progressionStats.Dexterity;
			RPGCombatComponent->CombatStats.EvadeRate = progressionStats.EvadeRate;
			RPGCombatComponent->CombatStats.HPRegenRate = progressionStats.HPRegenRate;
			RPGCombatComponent->CombatStats.HPRegenRateAmount = progressionStats.HPRegenRateAmount;
			RPGCombatComponent->CombatStats.Intelligence = progressionStats.Intelligence;
			RPGCombatComponent->CombatStats.MagicalDefense = progressionStats.MagicalDefense;
			RPGCombatComponent->CombatStats.MaximumMagicalAttack = progressionStats.MaximumMagicalAttack;
			RPGCombatComponent->CombatStats.MaximumPhysicalAttack = progressionStats.MaximumPhysicalAttack;
			RPGCombatComponent->CombatStats.Mentality = progressionStats.Mentality;
			RPGCombatComponent->CombatStats.MinimumMagicalAttack = progressionStats.MinimumMagicalAttack;
			RPGCombatComponent->CombatStats.MinimumPhysicalAttack = progressionStats.MinimumPhysicalAttack;
			RPGCombatComponent->CombatStats.MovementAgility = progressionStats.MovementAgility;
			RPGCombatComponent->CombatStats.MPRegenRate = progressionStats.MPRegenRate;
			RPGCombatComponent->CombatStats.MPRegenRateAmount = progressionStats.MPRegenRateAmount;
			RPGCombatComponent->CombatStats.PhysicalDefense = progressionStats.PhysicalDefense;
			RPGCombatComponent->CombatStats.Strength = progressionStats.Strength;
			RPGCombatComponent->CombatStats.Vitality = progressionStats.Vitality;

			if (progressionStats.Dexterity > 0)
			{
				// Improve BlockRate at 1:1
				RPGCombatComponent->CombatStats.BlockRate += progressionStats.Dexterity;

				// Improve EvadeRate at 1:2
				RPGCombatComponent->CombatStats.EvadeRate += FMath::FloorToInt(progressionStats.Dexterity * 0.5f);

				// Improve Critical Chance at 1:4
				RPGCombatComponent->CombatStats.CriticalChance += progressionStats.Dexterity * 0.25f;
			}

			if (progressionStats.Intelligence > 0)
			{
				// Improve AttackRating at 1:6
				RPGCombatComponent->CombatStats.AttackRating += FMath::FloorToInt(progressionStats.Intelligence * 0.1667f);

				// Improve DefenseRating at 1:5
				RPGCombatComponent->CombatStats.DefenseRating += FMath::FloorToInt(progressionStats.Intelligence * 0.2f);

				// Improve AttackAgility at 1:16
				RPGCombatComponent->CombatStats.AttackAgility += progressionStats.Intelligence * 0.0625f;

				// Improve CastingAgility at 1:12
				RPGCombatComponent->CombatStats.CastingAgility += progressionStats.Intelligence * 0.0833f;
			}

			if (progressionStats.Mentality > 0)
			{
				// Improve MaximumMana at 8:1
				RPGCombatComponent->MaximumMana += FMath::FloorToInt(progressionStats.Mentality * 8.0f);

				// Improve MagicalAttackPower at 1:4
				RPGCombatComponent->CombatStats.MaximumMagicalAttack += FMath::FloorToInt(progressionStats.Mentality * 0.25f);
				RPGCombatComponent->CombatStats.MinimumMagicalAttack += FMath::FloorToInt(progressionStats.Mentality * 0.25f);

				// Improve CastingAgility at 1:16
				RPGCombatComponent->CombatStats.CastingAgility += progressionStats.Mentality * 0.0625f;
			}

			if (progressionStats.Vitality > 0)
			{
				// Improve MaximumHealth at 16:1
				RPGCombatComponent->MaximumHealth += FMath::FloorToInt(progressionStats.Vitality * 16.0f);
			}
		}
	}
}
