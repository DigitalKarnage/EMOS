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

#include <Engine.h>
#include <Particles/ParticleSystem.h>
#include <Structures/FRPGSkillEffect.h>

#include "FRPGSkillUsage.generated.h"

USTRUCT(BlueprintType, META = (DisplayName = "RPG Skill Usage") )
struct EMOSRPG_API FRPGSkillUsage
{
	GENERATED_USTRUCT_BODY()

	public:
		/** A value indicating the amount of divine power needed to unlock this object */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect Properties")
		int32 DivinePowerCost;

		/** A value indicating whether this skill has been unlocked and is available for use */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect Properties")
		bool IsUnlocked;

		/** A value indicating the amount of time in second before this object can be used again */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		float Cooldown;

		/** A value indicating the amount of time in seconds before another skill can be used */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		float CastingDuration;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		int32 ManaCost;

		/** A value which indicates whether this object can be targeted on the user of this object */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		bool CanTargetSelf;

		/** A value which indicates whether this object can be targeted on friendlies of the user of thsi object */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		bool CanTargetFriendly;

		/** A collection of target affecting effects to modify on the target, of the user of this object */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		TArray<FRPGSkillEffect> TargetEffects;

		/** A collection of 'self' affecting effects to modify on the user of this object */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		TArray<FRPGSkillEffect> SelfTargetingEffects;

		/** A particle system used when this object is cast */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		UParticleSystem* ParticleFX;
};