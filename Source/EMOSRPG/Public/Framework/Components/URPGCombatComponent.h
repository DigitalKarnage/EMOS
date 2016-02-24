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

#pragma once

#include <EMOSRPG.h>
#include <Classes/AIController.h>

#include <Components/ActorComponent.h>
#include <GameFramework/Controller.h>

#include <Framework/Enumerations/ERPGCharacterType.h>
#include <Framework/Enumerations/ERPGStatsUpdateType.h>
#include <Framework/Structures/FRPGCharacterStats.h>
#include <Framework/Structures/FRPGCombatStats.h>

#include "URPGCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerEvent, const FDateTime&, serverTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterStatsEvent, const FRPGCharacterStats&, result, const ERPGStatsUpdateType, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCharacterCombatEvent, const int32, index, const FRPGCharacterStats&, stats, const ERPGStatsUpdateType, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCharacterStatsEventExtended, class URPGCombatComponent*, component, FRPGCharacterStats&, stats, const ERPGStatsUpdateType, type);

UCLASS(BlueprintType, ClassGroup = ("EMOS RPG"), HideCategories = (Sockets, ComponentTick, "Component Tick", ComponentReplication, "Component Replication", Variable, "Components|Sockets", Tags, Activation, "Components|Activation"), META = (DisplayName = "RPG Combat Component", BlueprintSpawnableComponent))
class EMOSRPG_API URPGCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		/** Indicates the Maximum range for the reputation system */
		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Component Settings", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumReputation = 51200;

		/** Indicates the maximum distance in unreal units in which to target, or keep a character targeted */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component Settings", META = (ClampMin = -1.0f, UIMin = -1.0f))
		float MaximumCharacterTargetDistance = 1750.0f;

		/** Indicates whether this object can target multiple characters at the same time */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component Settings" )
		bool bAllowMultipleTargets = false;

		/** Indicates the current server time */
		UPROPERTY(BlueprintReadWrite, Category = "Component Settings")
		FDateTime CurrentServerTime;

		/** The name given to the character which owns these stats */
		UPROPERTY(Replicated, BlueprintReadWrite, EditDefaultsOnly, Category = "Component Stats")
		FString Name = FString("Default Character");

		/** The type of character */
		UPROPERTY(Replicated, BlueprintReadWrite, EditDefaultsOnly, Category = "Component Stats")
		ERPGCharacterType CharacterType = ERPGCharacterType::None;

		/** The amount of progression */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CurrentExperience = 0.0f;

		UPROPERTY(Replicated, BlueprintReadWrite, VisibleDefaultsOnly, Category = "Component Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float MaximumExperience = 0.0f;

		/** The amount of progression within the game */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0) )
		uint8 CurrentLevel = 1;

		/** The maximum level progression within the game*/
		UPROPERTY(Replicated, BlueprintReadOnly, EditDefaultsOnly, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0))
		uint8 MaximumLevel = 255;

		/** The amount of health */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentHealth = 0;

		/** The maximum allowable health */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumHealth = 0;

		/** The amount of magical consumption available */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentMana = 0;

		/** The maximum allowable magic consumption available */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMana = 0;

		/** The value given to the player for good and bad choices */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats")
		int32 Reputation = 0;

		/** The value given to the player for doing reputable actions */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (ClampMin = 0.0f, UIMin = 0.0f))
		float DivinePower;
		
		/** Do we want players to be able to inspect this characters equipment stats */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Allows Inspection?") )
		bool bAllowsInspection = false;

		/** Are we targeting ourselves */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Is Targeting Self?") )
		bool bIsTargetingSelf = false;
				
		/** Are we in PK Mode */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Is In PK Mode?") )
		bool bIsInPKMode = false;

		/** Are we flagged for pk, but not immoral in our reputation */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Is Flagged?") )
		bool bIsFlagged = false;

		/** Are we currently in combat mode */
		UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Is In Combat?"))
		bool bIsInCombat = false;

		/** A value indicating whether we can be inspected */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component Stats")
		bool bCanBeInspected = false;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component Stats", META = (DisplayName = "Character Stats", ShowOnlyInnerProperties = true) )
		FRPGCombatStats CombatStats;

		UPROPERTY(BlueprintAssignable, Category = "Server Events")
		FServerEvent EventOnServerGameTimeUpdated;

		UPROPERTY(BlueprintAssignable, Category = "Server Events")
		FCharacterStatsEvent EventOnCharacterStatsChanged;

		UPROPERTY(BlueprintAssignable, Category = "Server Events")
		FCharacterCombatEvent EventOnTargetCharacterStatsChanged;

		UPROPERTY()
		FCharacterStatsEventExtended DelegateOnCharacterStatsChanged;

	private:
		float mCurrentTime = 0.0f;
		float mLastHPRegenTime = 0.0f;
		float mLastMPRegenTime = 0.0f;
		float mLastServerTimeUpdate = 0.0f;
		float mServerUpdateTimeRate = 7.5f;
		int64 mLastServerTimeSeconds = 0;
		bool bShouldWaitOneframe = false;
		ERPGStatsUpdateType mLastUpdateType = ERPGStatsUpdateType::None;

		mutable TSharedPtr < FRPGCharacterStats > mCharacterStats;		

	public:
		URPGCombatComponent(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

		virtual void InitializeComponent() override;
		virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;		
		virtual void TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction) override;

		UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Combat")
		void GetCharacterStats(FRPGCharacterStats& result) const;

		UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Combat")
		void TriggerOnTargetCharacterStatsChanged(const int32& index, FRPGCharacterStats& result, const ERPGStatsUpdateType type);

		/** 
			Recalculate the stats based on Equiped Items, and Consumed Items which are affecting this component
		*/
		UFUNCTION(BlueprintCallable, Category = "Combat")
		void RecalculateStats();

	private:
		UFUNCTION(Client, Reliable)
		void Client_UpdateServerTime(const int64& time);

		const ERPGStatsUpdateType CheckForUpdates();
};