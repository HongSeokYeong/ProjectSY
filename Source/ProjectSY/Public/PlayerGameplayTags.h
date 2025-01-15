// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace PlayerGamePlayTags
{
	// �Է� �±�
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);
	
	// �ɷ� �±�
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);

	// ������ �±�
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	// �̺�Ʈ �±�
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	PROJECTSY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}