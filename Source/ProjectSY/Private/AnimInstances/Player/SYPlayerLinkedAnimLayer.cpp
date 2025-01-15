// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/SYPlayerLinkedAnimLayer.h"
#include "AnimInstances/Player/SYPlayerAnimInstance.h"

USYPlayerAnimInstance* USYPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
    return Cast<USYPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
