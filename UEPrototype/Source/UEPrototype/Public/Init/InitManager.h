// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "InitManager.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitEventDispatcher);
DECLARE_DYNAMIC_DELEGATE(FReferenceDelegate);


/*
 *	AInitManager�� �� �ϳ��� �����Ǿ�� �ϴ�, �Ǵ� ���� ���۽�
 *	�ʱ�ȭ�Ǿ�� �ϴ� �͵��� �ʱ�ȭ�ϴ� Ŭ�����Դϴ�.
 */
UCLASS(abstract)
class UEPROTOTYPE_API AInitManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInitManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// �� �� ���� �����Ǿ�� �� �͵��� ��� �ʱ�ȭ(����)�մϴ�.
	UFUNCTION(BlueprintCallable, Category = "Prototpe|Init")
		void InitializeUniques();

	// ����ũ ��ü�� �ʿ�� �ϴ� ��ü�� �����ϰ� ���۷����ϵ��� �մϴ�.
	UFUNCTION(BlueprintCallable, Category = "Prototpe|Init")
		void SafeRefUniqueToActor(FReferenceDelegate EventToBind);

private:
	// InitManager�� ��Ű�� �ʱ�ȭ�� ���� �������� �� �߻���ų �̺�Ʈ�Դϴ�.
	// bUniquesEndInit�� true�� ��ȯ�մϴ�.
	UFUNCTION(BlueprintCallable, Category = "Prototype|Init", meta = (AllowPrivateAccess = "true"))
		void OnEndInitEvent();


public:
	// �ʱ�ȭ �Ŵ����� ����ũ �ʱ�ȭ�� ������ ���Ŀ� �̰͵��� �ʿ�� �ϴ�
	// ��󿡰� ��ε�ĳ��Ʈ�ϱ� ���� �̺�Ʈ ����ó�Դϴ�.
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Prototype|Init")
		FInitEventDispatcher OnUniquesEndInit;

private:
	// ����ũ���� ��� �ʱ�ȭ�� ���ƴ��� �����Դϴ�.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Prototype|Init", meta = (AllowPrivateAccess = "true"))
		bool bUniquesEndInit;

};
