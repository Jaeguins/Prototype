// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

#include "Engine/GameInstance.h"
#include "VPGameInstance.generated.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, text)

/**
 *
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
	// 일반 모드 - 오브젝트를 수정할 수 없는 상태입니다.
	GS_BASIC UMETA(DisplayName = "BasicState"),
	// 편집 모드 - 오브젝트를 수정 가능한 상태입니다.
	GS_EDIT	 UMETA(DisplayName = "EditState")
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateEventDispatcher, EGameState, NewState);

UCLASS()
class UEPROTOTYPE_API UVPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Global|State", meta = (AllowPrivateAccess = "true"))
	EGameState CurrentGameState;

public:
	// 상태를 변경합니다. - PC에서 입력키에 따라 호출됨
	UFUNCTION(BlueprintCallable, Category = "Global|State")
	void ChangeState(EGameState NewState);

	// 상태가 바뀔 때 발생하는 이벤트를 등록합니다.
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Global|State")
	FStateEventDispatcher OnStateChanged;
};
