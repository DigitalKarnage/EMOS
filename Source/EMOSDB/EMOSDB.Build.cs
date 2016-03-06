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

using System.IO;
using UnrealBuildTool;

public class EMOSDB : ModuleRules
{
    public EMOSDB(TargetInfo Target)
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "EMOSDB/Public",
                "EMOSDB/Public/Framework"
            }
        );


        PrivateIncludePaths.AddRange(
            new string[] {
                "EMOSDB/Private",
                "EMOSDB/Private/Framework",
                "EMOSDB/Private/bsoncxx/v_noabi",
                "EMOSDB/Private/mongocxx/v_noabi"
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Json",
                "JsonUtilities",
            }
        );
        
        UEBuildConfiguration.bForceEnableExceptions = true;

        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Libraries", "Win64")));
            PublicAdditionalLibraries.Add("bsoncxx.lib");
            PublicAdditionalLibraries.Add("mongocxx.lib");
            PublicDelayLoadDLLs.Add("bsoncxx.dll");
            PublicDelayLoadDLLs.Add("mongocxx.dll");
            
            Definitions.Add("USE_WINDOWSPLATFORMTYPES=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // TODO Build MongoDB for linux
        }
    }
}
