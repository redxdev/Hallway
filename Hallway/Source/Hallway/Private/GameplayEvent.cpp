// Fill out your copyright notice in the Description page of Project Settings.

#include "Hallway.h"
#include "GameplayEvent.h"

UGameplayEvent::UGameplayEvent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void IGameplayEvent::ExecuteEvent_Implementation()
{
}