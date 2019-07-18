// Fill out your copyright notice in the Description page of Project Settings.

#include "Gizmo/GizmoMeshComponent.h"
//#include "UEPrototype.h"

//UGizmoMeshComponent::UGizmoMeshComponent()
//{
//	//Super::UStaticMeshComponent();
//	VP_CTOR;
//}
void UGizmoMeshComponent::CreateGizmo(TArray<EGizmoAxisType> InAxisTypes, float InOffsetFromCenter, UStaticMesh* InMesh)
{
	this->AxisTypes = InAxisTypes;
	this->OffsetFromCenter = InOffsetFromCenter;

	if (InMesh != nullptr) 
		this->SetStaticMesh(InMesh);
	//else
	//	VP_LOG(Error, TEXT("GM_ ����� �˸��� �Ž��� ã�� �� �����ϴ�."));
	//GetClass()->GetDisplayNameText().ToString()
}
void UGizmoMeshComponent::UpdateGizmoTransType(EGizmoTransType InTransType)
{
	this->TransType = InTransType;
}
