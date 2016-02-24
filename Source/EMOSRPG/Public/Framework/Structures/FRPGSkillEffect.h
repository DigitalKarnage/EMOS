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
#include <Enumerations/ERPGSkillType.h>
#include <Enumerations/ERPGTargetAttribute.h>
#include <Structures/FRPGStatusEffect.h>

#include "FRPGSkillEffect.generated.h"

USTRUCT(BlueprintType, META = (DisplayName = "RPG Skill Effect"))
struct EMOSRPG_API FRPGSkillEffect
{
	GENERATED_USTRUCT_BODY()

	public:
		/** A value indicating the amount of time in seconds the status remains */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		float StatusDuration = 0.0f;

		/** A value indicating a status description and it should override the base status description */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		FString StatusDescriptionOverride;

		/** A value indicting the minimum amount to affect the 'target attribute' */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		float MinValue = 0.0f;

		/** A value indicting the maximum amount to affect the 'target attribute' */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		float MaxValue = 0.0f;

		/** A value indicating the rate in seconds at which to trigger this effect, if the duration > 0 */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		float EffectRate = 0.0f;
		
		/** A value indicating a percentage of the time that we want to trigger this effect */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties", META = (ClampMin = 0, ClampMax = 100, UIMin = 0, UIMax = 100))
		float TriggerRate = 100.0f;

		/** A value indicating whether to affect the attribute based on a percentage */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		bool IsPercentageBased = false;

		/** A value indicating whether the effect on the target attribute should falloff with distance between the instigator and the opponent */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		bool ShouldFalloffWithDistance = false;

		/** A value indicating the attribute to target for skill types that affect attributes */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect Properties")
		ERPGTargetAttribute TargetAttribute = ERPGTargetAttribute::HealthPoints;

		/** A particle system used when this object is applied */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Usage Properties")
		UParticleSystem* ParticleFX;
};