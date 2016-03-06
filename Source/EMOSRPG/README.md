It's important to know, that for this plugin to work in shipping builds, you need to do a couple of things.

1) You need to add the plugin modules as Precompiled in your game project.

foreach target add the following line:

'''c++
public override void GetModulesToPrecompile(TargetInfo Target, List<string> ModuleNames)
{
    ModuleNames.Add("EMOSRPG");                
}
'''

2) You also need to add a few PathIncludes and DependencyModuleNames to your build.cs file.

Although for game projects it doesn't matter whether you add THe DependencyModule as private or public, it does
however still need to be added to the ModuleNames collection

Add the following line to your Build.cs file within the constructor, DO NOT OVERWRITE THE EXISITING ONE

'''c#
PublicDependencyModuleNames.AddRange(
    new string[] {
        "EMOSRPG"
    }
);

PublicIncludePaths.AddRange(
    new string[] {
        "EMOSRPG/Public",
        "EMOSRPG/Public/Framework"
    }
);
'''