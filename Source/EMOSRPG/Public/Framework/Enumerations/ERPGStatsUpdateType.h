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
#include "ERPGStatsUpdateType.generated.h"

UENUM(BlueprintType, Blueprintable, META = (DisplayName = "E RPG Stats Update Type") )
enum class ERPGStatsUpdateType : uint8
{
	/** A value which represents nothing */
	None = 0x00,

	/** All stats have been updated, should take action accordingly */
	All = 0x01,

	/** Only the combat mode has changed */
	Combat = 0x02,

	/** Only the divine power stat has changed */
	Divine = 0x03,

	/** Only the experience has changed */
	Experience = 0x04,

	/** Only the flagged for pk state has changed */
	Flagged = 0x05,

	/** The general stats have been updated, (Health, Mana, Level, Reputation, Flagged, and Inspection States) */
	General = 0x06,

	/** Only the health states have changed */
	Health = 0x07,

	/** Only the Inspection state has changed */
	Inspection = 0x08,

	/** The Level state has changed, should take action accordingly */
	Level = 0x09,

	/** Only the mana states have changed */
	Mana = 0x0A,

	/** Only the reputation state has changed */
	Reputation	= 0x0B
};