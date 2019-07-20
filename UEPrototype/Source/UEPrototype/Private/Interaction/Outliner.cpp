// Fill out your copyright notice in the Description page of Project Settings.

#include "Outliner.h"
#include "../Public/Interaction/Outliner.h"
#include <GameFramework/Actor.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <Engine/World.h>
#include <UObjectGlobals.h>
#include <Materials/MaterialInstanceDynamic.h>

 UOutliner::UOutliner()
{
	
}
 // actor�� const�ε� const�� ���� ����� �� �ִ� �͵��� ����(���߿� �����غ�����)
void UOutliner::DrawActorOutline(const AActor * actor)
{
	LastOutlinedActor = const_cast<AActor*>(actor);
	
	//�׸��� �ߺ� �˻�
	TArray<AActor*> ChildOutliner;
	actor->GetAttachedActors(ChildOutliner);
	for (int i = 0; i < ChildOutliner.Num(); ++i)
	{
		if (ChildOutliner[i]->GetActorLabel() == OutlinerLabelName) return;
	}

	//�����ص� material�� �������� �۾�
	UMaterialInstance* OutlineMaterial = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Material/MI_Outliner"));
	if (OutlineMaterial == nullptr)
	{
		return;
	}

	
	AActor* SpawnedOutlineActor = GetWorld()->SpawnActor<AActor>(actor->GetClass(), actor->GetActorLocation(), actor->GetActorRotation());

	// �ƿ������� ������ ������ �ڽ����� �־��ش�(����� Ʈ�������� ���� �̵��� ���ؼ� ���� ���󰡾��ϴϱ�)
	SpawnedOutlineActor->AttachToActor(const_cast<AActor*>(actor),FAttachmentTransformRules::KeepWorldTransform);
	
	//�ڽ� �̸��� �������ش�. �̰��� ���� outline�� �������θ� key�μ� Ȯ���� ���̴�.
	SpawnedOutlineActor->SetActorLabel(OutlinerLabelName);

	//actor(Ȥ�� �ڽ�)�� material�� �����ϱ����� staticmeshcomponent ���
	TArray<UStaticMeshComponent*> SM_Comp;
	SpawnedOutlineActor->GetComponents(SM_Comp);

	for (int i = 0; i < SM_Comp.Num(); i++)
	{
		UStaticMeshComponent* thisComp = Cast<UStaticMeshComponent>(SM_Comp[i]);
		if (thisComp)
		{
			thisComp->SetMaterial(0, UMaterialInstanceDynamic::Create(OutlineMaterial, this));
		}
	}

}

void UOutliner::EraseActorOutline()
{
	TArray<AActor*> ChildOutliner;

	if (LastOutlinedActor == nullptr) return;

	LastOutlinedActor->GetAttachedActors(ChildOutliner);
	
	if (ChildOutliner.Num() == 0) return;

	for (int i = 0; i < ChildOutliner.Num(); ++i)
	{
		if (ChildOutliner[i]->GetActorLabel() == OutlinerLabelName)
		{
			ChildOutliner[i]->Destroy();			
		}
	}
	LastOutlinedActor = nullptr;
}





