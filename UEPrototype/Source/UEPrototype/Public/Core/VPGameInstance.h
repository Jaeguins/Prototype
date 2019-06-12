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
	// �Ϲ� ��� - ������Ʈ�� ������ �� ���� �����Դϴ�.
	GS_BASIC UMETA(DisplayName = "BasicState"),
	// ���� ��� - ������Ʈ�� ���� ������ �����Դϴ�.
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
	// ���¸� �����մϴ�. - PC���� �Է�Ű�� ���� ȣ���
	UFUNCTION(BlueprintCallable, Category = "Global|State")
	void ChangeState(EGameState NewState);

	// ���°� �ٲ� �� �߻��ϴ� �̺�Ʈ�� ����մϴ�.
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Global|State")
	FStateEventDispatcher OnStateChanged;
};
