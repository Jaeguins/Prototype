// Fill out your copyright notice in the Description page of Project Settings.

#include "Gizmo/GizmoMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
//#include "UEPrototype.h"

//UGizmoMeshComponent::UGizmoMeshComponent()
//{
//	//Super::UStaticMeshComponent();
//	VP_CTOR;
//}
void UGizmoMeshComponent::CreateGizmo(TArray<EGizmoAxisType> InAxisTypes, float InOffsetFromCenter)
{
	this->AxisTypes = InAxisTypes;
	//else
	//	VP_LOG(Error, TEXT("GM_ ����� �˸��� �Ž��� ã�� �� �����ϴ�."));
	//GetClass()->GetDisplayNameText().ToString()
}

FVector UGizmoMeshComponent::GetAxisUnitDirectionVector()
{
	//if (GetAttachmentRootActor() != nullptr)
	//{
	//	return UKismetMathLibrary::GetDirectionUnitVector(getattach()->GetActorLocation(), GetComponentLocation());
	//}
	//return FVector::ZeroVector;
}
