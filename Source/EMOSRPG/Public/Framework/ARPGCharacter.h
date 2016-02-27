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

#include <Core.h>
#include <Engine.h>
#include <Object.h>
#include <UnrealNetwork.h>
#include <GameFramework/Pawn.h>
#include <GameFramework/Character.h>
#include <Components/WidgetComponent.h>

#include <Framework/Components/URPGCombatComponent.h>
#include <Framework/Interfaces/IRPGCombatInterface.h>
#include <Framework/Structures/FRPGCharacterStats.h>
#include <Framework/Structures/FRPGCombatStats.h>
#include <Framework/Data/DataAssets/URPGCharacterData.h>

#include "ARPGCharacter.generated.h"

UCLASS(abstract, Blueprintable, META = (DisplayName = "RPG Character"))
class EMOSRPG_API ARPGCharacter : public ACharacter, public IRPGCombatInterface
{
	GENERATED_BODY()

	public:
		/** Gets or sets a value indicating the maximum distance from the camera view to draw the character name widget */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		float MaxNameDrawDistance = 2450.0f;
		
	protected:
		UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere, Category = "Components", META = (DisplayName = "RPG Combat Component", AllowPrivateAccess = "true"))
		URPGCombatComponent* RPGCombatComponent;

		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Assets", META = (DisplayName = "Base Character Data", AllowPrivateAccess = "true") )
		class URPGCharacterData* BaseCharacterData;
		
	private:
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components", META = (DisplayName = "Character Name Widget Component", AllowPrivateAccess = "true") )
		class UWidgetComponent* CharacterNameWidget;
		
		FScriptDelegate OnTargetOpponentStatsChangedBinding;
		
		TMap<APawn*, URPGCombatComponent*> CharacterTargets;
		FCharacterCombatEvent EventTargetOpponentStatsChanged;

	public:
		ARPGCharacter(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

		virtual void PostInitializeComponents() override;
		virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
		virtual void Tick(float delta) override;

		virtual void GetCharacterStats_Implementation(FRPGCharacterStats& result) override;
		virtual void GetCombatStats_Implementation(FRPGCombatStats& result) override;
		virtual void GetTargetStatsAtIndex_Implementation(const int32 index, FRPGCharacterStats& result) override;
		virtual URPGCombatComponent* GetCombatComponent_Implementation() override;		

		UFUNCTION(BlueprintCallable, Category = "Combat")
		void TargetOpponent(APawn* target);

		UFUNCTION(BlueprintCallable, Category = "Combat")
		void ClearTargets();

		UFUNCTION(BlueprintCallable, Category = "Combat")
		void ClearTarget(APawn* target);

		UFUNCTION(BlueprintCallable, Category = "Combat")
		void ClearTargetAtIndex(const int32& index);

private:
		UFUNCTION()
		void OnTargetOpponentStatsChanged(URPGCombatComponent* combatComponent, FRPGCharacterStats& result, const ERPGStatsUpdateType type);
		
		UFUNCTION(Server, Reliable, WithValidation)
		void Server_TargetOpponent(APawn* target);

		UFUNCTION(Client, Reliable)
		void Client_TargetLost(APawn* pawn);
};