// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/SYDataAsset_InputConfig.h"

UInputAction* USYDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSYInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
