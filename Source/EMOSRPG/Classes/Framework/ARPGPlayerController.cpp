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
#include <Framework/ARPGPlayerController.h>

ARPGPlayerController::ARPGPlayerController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	this->bReplicates = true;
	this->bReplicateMovement = true;
	this->bRelevantForNetworkReplays = true;

	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

void ARPGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ARPGPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void ARPGPlayerController::Tick(float delta)
{
	Super::Tick(delta);


}

void ARPGPlayerController::GetCharacterStats_Implementation(FRPGCharacterStats& result)
{ 
	auto pawn = GetPawn();

	if (EnsurePawn(pawn) && this->RPGCharacter != NULL)
		this->RPGCharacter->Execute_GetCharacterStats(pawn, result);
}

void ARPGPlayerController::GetTargetStatsAtIndex_Implementation(const int32 index, FRPGCharacterStats& result)
{
	auto pawn = GetPawn();

	if (EnsurePawn(pawn) && this->RPGCharacter != NULL)
		return RPGCharacter->Execute_GetTargetStatsAtIndex(pawn, index, result);
}

void ARPGPlayerController::GetCombatStats_Implementation(FRPGCombatStats& result)
{ 
	auto pawn = GetPawn();

	if (EnsurePawn(pawn) && this->RPGCharacter != NULL)
		this->RPGCharacter->Execute_GetCombatStats(pawn, result);
}

URPGCombatComponent* ARPGPlayerController::GetCombatComponent_Implementation()  
{ 
	auto pawn = GetPawn();

	if (EnsurePawn(pawn) && this->RPGCharacter != NULL)
		return RPGCharacter->Execute_GetCombatComponent(pawn);

	return NULL;
}

void ARPGPlayerController::OnRep_Pawn()
{
	EnsurePawn(this->GetPawn());
}

bool ARPGPlayerController::EnsurePawn(APawn* pawn) const
{
	if (pawn != NULL)
	{
		if (this->RPGCharacter == NULL)
		{
			if (pawn->GetClass()->ImplementsInterface(URPGCombatInterface::StaticClass()))
				this->RPGCharacter = Cast<IRPGCombatInterface>(pawn);
		}
	}		

	return pawn != NULL;
}
