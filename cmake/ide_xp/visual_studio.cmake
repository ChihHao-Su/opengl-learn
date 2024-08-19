# Config Visual Studio for better experience.
function(enable_vs_guideline_checker target)
	set_target_properties(app PROPERTIES
		VS_GLOBAL_EnableCppCoreCheck true
		VS_GLOBAL_CodeAnalysisRuleSet CppCoreCheckRules.ruleset
		VS_GLOBAL_RunCodeAnalysis true)
endfunction()