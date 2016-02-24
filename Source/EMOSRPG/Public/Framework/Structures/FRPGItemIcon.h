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
#include <Enumerations/ERPGItemRarity.h>

#include "FRPGItemIcon.generated.h"

USTRUCT(BlueprintType, META = (DisplayName = "RPG Item Icon") )
struct EMOSRPG_API FRPGItemIcon
{
	GENERATED_USTRUCT_BODY()

	public:
		/** A value representing the base texture used for this object */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals")
		UTexture2D* Texture;

		/** A value representing the size of the icon */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals")
		FVector2D Size;

		/** A value representing the column offset from the top left of the texture */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals", META = (ClampMin = 0, UIMin = 0))
		int32 ColumnOffset;

		/** A value representing the row offset from the top left of the texture */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals", META = (ClampMin = 0, UIMin = 0))
		int32 RowOffset;
};