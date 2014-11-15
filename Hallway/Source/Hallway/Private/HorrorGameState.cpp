// Fill out your copyright notice in the Description page of Project Settings.

#include "Hallway.h"
#include "Engine.h"
#include "HorrorGameState.h"


AHorrorGameState::AHorrorGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

bool AHorrorGameState::CallRandomEvent()
{
	if (Events.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No events to call"));
		return false;
	}

	UObject* Obj = Events[FMath::RandHelper(Events.Num())];
	if (!Obj || !Obj->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid UObject in AHorrorGameState::Events array"));
		return false;
	}

	if (Obj->GetClass()->ImplementsInterface(UGameplayEvent::StaticClass()))
	{
		IGameplayEvent::Execute_ExecuteEvent(Obj);
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tried to call invalid IGameplayEvent"));
		return false;
	}
}

bool AHorrorGameState::AddGameplayEvent(UObject* Object)
{
	if (!Object || !Object->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid UObject passed to AddGameplayEvent"));
		return false;
	}

	if (Object->GetClass()->ImplementsInterface(UGameplayEvent::StaticClass()))
	{
		Events.Add(Object);
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tried to register invalid IGameplayEvent"));
		return false;
	}
}