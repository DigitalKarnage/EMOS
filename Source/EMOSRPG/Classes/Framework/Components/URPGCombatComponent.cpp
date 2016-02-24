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
#include <Framework/Components/URPGCombatComponent.h>

URPGCombatComponent::URPGCombatComponent(const FObjectInitializer& objectInitializer)
{
	this->bReplicates = true;
	this->bNetAddressable = true;
	this->bAutoActivate = false;
	this->bEditableWhenInherited = true;	
	this->CreationMethod = EComponentCreationMethod::Native;
	
	this->bWantsInitializeComponent = true;

	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bRunOnAnyThread = false;
	this->PrimaryComponentTick.bTickEvenWhenPaused = true;	
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
		
	this->mCharacterStats = MakeShareable<FRPGCharacterStats>(new FRPGCharacterStats());	
}

void URPGCombatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	this->mCharacterStats->bAllowsInspection = this->bAllowsInspection;
	this->mCharacterStats->bCanBeInspected = this->bCanBeInspected;
	this->mCharacterStats->bIsFlagged = this->bIsFlagged;
	this->mCharacterStats->bIsInCombat = this->bIsInCombat;
	this->mCharacterStats->bIsInPKMode = this->bIsInPKMode;
	this->mCharacterStats->bIsTargetingSelf = this->bIsTargetingSelf;
	this->mCharacterStats->CharacterType = this->CharacterType;
	this->mCharacterStats->CurrentExperience = this->CurrentExperience;
	this->mCharacterStats->CurrentHealth = this->CurrentHealth;
	this->mCharacterStats->CurrentLevel = this->CurrentLevel;
	this->mCharacterStats->CurrentMana = this->CurrentMana;
	this->mCharacterStats->DivinePower = this->DivinePower;
	this->mCharacterStats->MaximumHealth = this->MaximumHealth;
	this->mCharacterStats->MaximumMana = this->MaximumMana;
	this->mCharacterStats->MaximumExperience = this->MaximumExperience;
	this->mCharacterStats->Name = this->Name;
	this->mCharacterStats->Reputation = this->Reputation;

#if defined(UE_EDITOR) || defined(UE_SERVER)

	mLastHPRegenTime -= CombatStats.HPRegenRate;
	mLastMPRegenTime -= CombatStats.MPRegenRate;
	mLastServerTimeUpdate -= mServerUpdateTimeRate;

	this->CurrentServerTime = FDateTime::Now();

#endif

}

void URPGCombatComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGCombatComponent, bAllowsInspection)
	DOREPLIFETIME(URPGCombatComponent, bIsFlagged);
	DOREPLIFETIME(URPGCombatComponent, bIsInCombat);
	DOREPLIFETIME_CONDITION(URPGCombatComponent, bIsInPKMode, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(URPGCombatComponent, bIsTargetingSelf, COND_OwnerOnly);	
	DOREPLIFETIME(URPGCombatComponent, CharacterType);
	DOREPLIFETIME_CONDITION(URPGCombatComponent, CurrentExperience, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(URPGCombatComponent, MaximumExperience, COND_OwnerOnly);
	DOREPLIFETIME(URPGCombatComponent, CurrentHealth);
	DOREPLIFETIME(URPGCombatComponent, CurrentLevel);
	DOREPLIFETIME(URPGCombatComponent, CurrentMana);
	DOREPLIFETIME_CONDITION(URPGCombatComponent, DivinePower, COND_OwnerOnly);
	DOREPLIFETIME(URPGCombatComponent, MaximumHealth);
	DOREPLIFETIME(URPGCombatComponent, MaximumMana);
	DOREPLIFETIME(URPGCombatComponent, Name);
	DOREPLIFETIME(URPGCombatComponent, Reputation);
}

void URPGCombatComponent::TickComponent(float delta, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(delta, tickType, thisTickFunction);
	
	static ERPGStatsUpdateType updateStatsType = ERPGStatsUpdateType::None;	

#if defined(UE_EDITOR) || defined(UE_SERVER)	

	// Gaurded statement for Server only related tick tasks
	if (GetOwnerRole() >= ROLE_Authority)
	{
		static int32 tempResult = 0;		

		this->mCurrentTime += delta;

		if (!bIsInCombat)
		{			
			if (CombatStats.HPRegenRate > 0 && CombatStats.HPRegenRateAmount > 0)
			{
				if (mCurrentTime - mLastHPRegenTime >= CombatStats.HPRegenRate)
				{
					tempResult = FMath::Clamp(this->CurrentHealth + CombatStats.HPRegenRateAmount, 0, this->MaximumHealth);

					// Only update the health if it has changed, this is for optimatizations for the replication system
					if (this->CurrentHealth != tempResult)
						this->CurrentHealth = tempResult;

					mLastHPRegenTime = mCurrentTime;
				}
			}
			else mLastHPRegenTime = mCurrentTime;

			if (CombatStats.MPRegenRate > 0 && CombatStats.MPRegenRateAmount > 0)
			{
				if (mCurrentTime - mLastMPRegenTime >= CombatStats.MPRegenRate)
				{
					tempResult = FMath::Clamp(this->CurrentMana + CombatStats.MPRegenRateAmount, 0, this->MaximumMana);

					// Only update the health if it has changed, this is for optimatizations for the replication system
					if (this->CurrentMana != tempResult)
						this->CurrentMana = tempResult;

					mLastMPRegenTime = mCurrentTime;
				}
			}
			else mLastMPRegenTime = mCurrentTime;
		}
		else mLastHPRegenTime = mLastMPRegenTime = mCurrentTime;

		if (mServerUpdateTimeRate > 0)
		{
			if (mCurrentTime - mLastServerTimeUpdate >= mServerUpdateTimeRate)
			{
				mServerUpdateTimeRate = FMath::Clamp(mServerUpdateTimeRate * 2.0f, 0.0f, (float)FTimespan::FromMinutes(5.0f).GetTotalSeconds());
				mLastServerTimeUpdate = mCurrentTime;

				Client_UpdateServerTime(FDateTime::Now().GetTicks());
			}
		}
		else mLastServerTimeUpdate = mCurrentTime;
	}

#endif

#if defined(UE_EDITOR) || defined(UE_GAME)

	// Gaurded statement for game client only related tick tasks
	if (GetOwnerRole() < ROLE_Authority)
	{

	}

	// we need to tick this, if we are in the editor, even for 'Server' PIE instances, but we don't build this
	// on NON UE_SERVER instances for shipping
	this->CurrentServerTime += FTimespan::FromSeconds(delta);

	if (EventOnServerGameTimeUpdated.IsBound() && this->CurrentServerTime.GetTicks() >= (mLastServerTimeSeconds + ETimespan::TicksPerSecond) )
	{
		EventOnServerGameTimeUpdated.Broadcast(this->CurrentServerTime.GetTicks());
		this->mLastServerTimeSeconds = this->CurrentServerTime.GetTicks();
	}

#endif

	updateStatsType = CheckForUpdates();

	if (updateStatsType != ERPGStatsUpdateType::None)
	{
		// Set all of the property values
		this->mCharacterStats->bAllowsInspection = this->bAllowsInspection;
		this->mCharacterStats->bCanBeInspected = this->bCanBeInspected;
		this->mCharacterStats->bIsFlagged = this->bIsFlagged;
		this->mCharacterStats->bIsInPKMode = this->bIsInPKMode;
		this->mCharacterStats->bIsTargetingSelf = this->bIsTargetingSelf;
		this->mCharacterStats->CharacterType = this->CharacterType;
		this->mCharacterStats->CurrentExperience = this->CurrentExperience;
		this->mCharacterStats->CurrentHealth = this->CurrentHealth;
		this->mCharacterStats->CurrentLevel = this->CurrentLevel;
		this->mCharacterStats->CurrentMana = this->CurrentMana;
		this->mCharacterStats->DivinePower = this->DivinePower;
		this->mCharacterStats->MaximumExperience = this->MaximumExperience;
		this->mCharacterStats->MaximumHealth = this->MaximumHealth;
		this->mCharacterStats->MaximumMana = this->MaximumMana;
		this->mCharacterStats->Name = this->Name;
		this->mCharacterStats->Reputation = this->Reputation;

		if (mLastUpdateType != ERPGStatsUpdateType::None && mLastUpdateType != updateStatsType)
			mLastUpdateType = ERPGStatsUpdateType::General;

		else mLastUpdateType = updateStatsType;
	}

	bShouldWaitOneframe = updateStatsType != ERPGStatsUpdateType::None;

	if (mLastUpdateType != ERPGStatsUpdateType::None && !bShouldWaitOneframe)
	{
		if (EventOnCharacterStatsChanged.IsBound())
			this->EventOnCharacterStatsChanged.Broadcast(*mCharacterStats, mLastUpdateType);

		if (DelegateOnCharacterStatsChanged.IsBound())
			DelegateOnCharacterStatsChanged.Broadcast(this, *mCharacterStats, mLastUpdateType);

		mLastUpdateType = ERPGStatsUpdateType::None;
		bShouldWaitOneframe = false;
	}
}

 void URPGCombatComponent::GetCharacterStats(FRPGCharacterStats& result) const 
 { 
	 result = *mCharacterStats;
 }
 
const ERPGStatsUpdateType URPGCombatComponent::CheckForUpdates()
{
	// Static variable table
	static int32 tIntResult = 0;
	static float tFloatResult = 0.0f;
	static uint8 tByteResult = (uint8)0;

	static bool nuName = false;
	static bool nuCharacterType = false;
	static bool nuExperience = false;
	static bool nuLevel = false;
	static bool nuHealth = false;
	static bool nuMana = false;
	static bool nuReputation = false;
	static bool nuDivinePower = false;
	static bool nuAllowsInspection = false;
	static bool nuIsFlagged = false;
	static bool nuIsInCombat = false;
	static bool nuIsInPKMode = false;

	auto result = ERPGStatsUpdateType::None;
	
	// Micro opitimization, clamp out the values for the component, and only set if a change has occurred
	{ 
		tIntResult = FMath::Clamp(this->CurrentHealth, 0, this->MaximumHealth);
		tByteResult = FMath::Clamp(this->CurrentLevel, (uint8)0, this->MaximumLevel);
		tFloatResult = FMath::Clamp(this->DivinePower, 0.0f, (int)(this->CurrentLevel) + .9999f);

		if (this->CurrentHealth != tIntResult)
			this->CurrentHealth = tIntResult;

		tIntResult = FMath::Clamp(this->CurrentMana, 0, this->MaximumMana);

		if (this->CurrentMana != tIntResult)
			this->CurrentMana = tIntResult;

		tIntResult = FMath::Clamp(this->Reputation, -MaximumReputation, MaximumReputation);

		if (this->Reputation != tIntResult)
			this->Reputation = tIntResult;
		
		if (CurrentLevel > tByteResult)
			this->CurrentLevel = tByteResult;

		if (this->DivinePower != tFloatResult)
			this->DivinePower = tFloatResult;
	}

	nuName = Name != mCharacterStats->Name;
	nuCharacterType = CharacterType != mCharacterStats->CharacterType;
	nuExperience = CurrentExperience != mCharacterStats->CurrentExperience || MaximumExperience != mCharacterStats->MaximumExperience;
	nuLevel = CurrentLevel != mCharacterStats->CurrentLevel;
	nuHealth = CurrentHealth != mCharacterStats->CurrentHealth || MaximumHealth != mCharacterStats->MaximumHealth;
	nuMana = CurrentMana != mCharacterStats->CurrentMana || MaximumMana != mCharacterStats->MaximumMana;
	nuReputation = Reputation != mCharacterStats->Reputation;
	nuDivinePower = DivinePower != mCharacterStats->DivinePower;
	nuAllowsInspection = bAllowsInspection != mCharacterStats->bAllowsInspection;
	nuIsFlagged = bIsFlagged != mCharacterStats->bIsFlagged;
	nuIsInCombat = bIsInCombat != mCharacterStats->bIsInCombat;
	nuIsInPKMode = bIsInPKMode != mCharacterStats->bIsInPKMode;

	if (nuName || nuCharacterType)
		result = ERPGStatsUpdateType::All;
	
	else if (nuExperience && (nuLevel | nuHealth | nuMana | nuReputation | nuDivinePower | nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuLevel & (nuHealth | nuMana | nuReputation | nuDivinePower | nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuHealth & (nuMana | nuReputation | nuDivinePower | nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuMana & (nuReputation | nuDivinePower | nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuReputation & (nuDivinePower | nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuDivinePower & (nuAllowsInspection | nuIsFlagged | nuIsInCombat | nuIsInPKMode) ||
		nuAllowsInspection & (nuIsFlagged | nuIsInCombat | nuIsInPKMode) || 
		nuIsFlagged && (nuIsInCombat | nuIsInPKMode) || 
		nuIsInCombat && nuIsInPKMode) { result = ERPGStatsUpdateType::General; }

	if (result == ERPGStatsUpdateType::None)
	{
		 if (nuLevel)
			result = ERPGStatsUpdateType::Level;

		else if (nuHealth)
			result = ERPGStatsUpdateType::Health;

		else if (nuReputation)
			result = ERPGStatsUpdateType::Reputation;

		else if (nuIsFlagged)
			result = ERPGStatsUpdateType::Flagged;

		else if (nuIsInCombat)
			result = ERPGStatsUpdateType::Combat;

		else if (nuMana)
			result = ERPGStatsUpdateType::Mana;

		else if (nuDivinePower)
			result = ERPGStatsUpdateType::Divine;
	}

	return result;
}

void URPGCombatComponent::TriggerOnTargetCharacterStatsChanged(const int32& index, FRPGCharacterStats& result, const ERPGStatsUpdateType type)
{
	if (EventOnTargetCharacterStatsChanged.IsBound())
		EventOnTargetCharacterStatsChanged.Broadcast(index, result, type);
}

void URPGCombatComponent::Client_UpdateServerTime_Implementation(const int64& time) 
{ 
	this->CurrentServerTime = FDateTime(time); 
}

void URPGCombatComponent::RecalculateStats()
{
	// Recalculate the stats based on Equiped Items, and Consumed Items which are still effecting this component

	// Since we don't support Equipment or Stats Effects yet, this function doesn't do anything
}