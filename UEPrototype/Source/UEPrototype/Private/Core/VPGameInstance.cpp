// Fill out your copyright notice in the Description page of Project Settings.

#include "VPGameInstance.h"

void UVPGameInstance::ChangeState(EGameState NewState)
{
	this->CurrentGameState = NewState;
	OnStateChanged.Broadcast(NewState);

	if (NewState == EGameState::GS_EDIT)
		print(TEXT("Now Edit Mode"));
	else if (NewState == EGameState::GS_BASIC)
		print(TEXT("Now Basic Mode"));
}