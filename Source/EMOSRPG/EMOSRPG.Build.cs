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

using UnrealBuildTool;

public class EMOSRPG : ModuleRules
{
	public EMOSRPG(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
                "Networking",
                "Sockets",
                "Http",
                "Json",
                "JsonUtilities",
                "UMG"
            }
        );

        PublicIncludePaths.AddRange(
            new string[]
            {
                "EMOSRPG/Public",
                "EMOSRPG/Public/Framework",
            }
        );

        // Hide the Abstraction layer for this module
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Websockets"
            }
        );

        PublicIncludePaths.AddRange(
            new string[]
            {
                "Websockets",
                "Websockets/Public",
                "Websockets/Public/Framework"
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Win32 ||
            Target.Platform == UnrealTargetPlatform.Win64 ||
            Target.Platform == UnrealTargetPlatform.Linux && 
            (UEBuildConfiguration.bWithServerCode || UEBuildConfiguration.bBuildEditor) )
        {
            // We only link the MongoDB Module, if we building for windows or linux servers/editors

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "MongoDB",
                }
            );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "MongoDB",
                    "MongoDB/Public",
                    "MongoDB/Public/Framework"
                }
            );

            // This allows the headers / classes to be compiled for these specific builds
            Definitions.Add("WITH_MONGODB=1");
        }
	}
}
