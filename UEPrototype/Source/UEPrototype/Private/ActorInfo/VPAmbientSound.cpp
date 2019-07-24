// Fill out your copyright notice in the Description page of Project Settings.

#include "VPAmbientSound.h"
#include <Components/AudioComponent.h>
#include <Sound/SoundBase.h>
AVPAmbientSound::AVPAmbientSound() 
{
	//Default Values
	GetAudioComponent()->VolumeMultiplier = 1.f;
	GetAudioComponent()->PitchMultiplier = 1.f;
	GetAudioComponent()->AttenuationOverrides.FalloffDistance = 3600.f;
	GetAudioComponent()->AttenuationOverrides.AttenuationShapeExtents
		= FVector(400.f, 0.0f, 0.0f);
}

void AVPAmbientSound::CreateSound(const AActor* Actor, FSoundProperty SoundProperty, FAttenuationProperty AttenuationProperty)
{
	

	//���忡 ���� Value ����
	{
		GetAudioComponent()->Sound = SoundProperty.Sound;
		GetAudioComponent()->bIsUISound = SoundProperty.bUISound;
		GetAudioComponent()->bAutoActivate = SoundProperty.bAutoActivate;
		GetAudioComponent()->VolumeMultiplier = SoundProperty.VolumeMultiplier;
		GetAudioComponent()->PitchMultiplier = SoundProperty.PitchMultiplier;
		GetAudioComponent()->bAlwaysPlay = SoundProperty.bAlwaysPlay;

		if (SoundProperty.bLooping)
		{
			GetAudioComponent()->OnAudioFinished.AddDynamic(this, &AVPAmbientSound::PlayVPNormal);
		}
	}
		
		
	//���迡 ����  Value ����

	{
		//����ȭ�� �� ���ΰ�(�ϴ� �����̱��ѵ� ����ڿ��� �Ѱ����� �ȳѰ����� �����غ�����)
		GetAudioComponent()->bAllowSpatialization = true;

		//���迡 ���� �Ķ���͸� ���� �����ϱ����� bool��
		GetAudioComponent()->bOverrideAttenuation = true;

		//3d���������� ����ȭ, true�� ���������.
		GetAudioComponent()->AttenuationOverrides
			.bApplyNormalizationToStereoSounds = true;

		//���׷��� ���� �Ÿ�, �ʹ� ��ȭ�۾��̹Ƿ� default���� �ھƵд�.
		GetAudioComponent()->AttenuationOverrides.StereoSpread = 200.0f;

		//����ȭ �˰���, �ʹ� ��ȭ�۾��̹Ƿ� default���� �ھƵд�.
		GetAudioComponent()->AttenuationOverrides.SpatializationAlgorithm =
			ESoundSpatializationAlgorithm::SPATIALIZATION_Default;

		//����ȭ ���뿡 ���� bool��(�ڷᰡ ����)
		GetAudioComponent()->AttenuationOverrides.bSpatialize = true;

		//2���������� ���� �ݰ�, 3������ ����� ���� 0���� ����
		GetAudioComponent()->AttenuationOverrides.OmniRadius = 0.0f;

		//Enable volume attenuation�� �ɷ� �����ϰ� ������(�ȵǸ� ã�ƺ���)
		GetAudioComponent()->AttenuationOverrides.bAttenuate = true;

		//����Ÿ��� ���� �˰��� ����
		GetAudioComponent()->AttenuationOverrides.DistanceAlgorithm
			= (EAttenuationDistanceModel)AttenuationProperty.AttenuationDistanceModel;

		//�׻� play�� ��Ű���� NaturalSound �˰����� ������ �����̵Ǿ���Ѵ�. ���� 
		//AlwaysPlay�� �����ٸ� ������ NaturalSound�� ����ǵ�����.(����ڿ��� NaturalSound�� �����������)
		if (SoundProperty.bAlwaysPlay)
		{
			GetAudioComponent()->AttenuationOverrides.DistanceAlgorithm = EAttenuationDistanceModel::NaturalSound;
			GetAudioComponent()->AttenuationOverrides.dBAttenuationAtMax = -60;
		}

		//���� ��翡 ���� ����
		GetAudioComponent()->AttenuationOverrides.AttenuationShape
			= AttenuationProperty.AttenuationShape;
		//���谡 ������(���� =0)�Ÿ��� ���� ����
		GetAudioComponent()->AttenuationOverrides.FalloffDistance
			= AttenuationProperty.FalloffDistance;
		//���谡 ����Ǵ� �Ÿ�, ���� X���� �ְ� ������������ ������.
		GetAudioComponent()->AttenuationOverrides.AttenuationShapeExtents
			= FVector(AttenuationProperty.DecreaseRadius, 0.0f, 0.0f);

		//���ιݰ��� ���谡 �����°Ÿ����� �ָ� ������ ȿ�� �����̾ȵ�. ���� ���ιݰ���
		//�ݵ�� falloffDistance���� ���� ���� �������Ѵ�.
		if (AttenuationProperty.FalloffDistance < AttenuationProperty.DecreaseRadius)
		{
			GetAudioComponent()->AttenuationOverrides.AttenuationShapeExtents =
				FVector(AttenuationProperty.FalloffDistance, 0.0f, 0.0f);	
		}
			
	}
		

		

	

	//������ ���� Value ����
		//������ ����ڰ� ���� �ǵ鿩�� �ʿ䰡 ���� ����.���߿� �ʿ信 ���� ����ü �ּ��� Ǯ�� �Ű�������
		//�޾ƿ� ����
	{
		GetAudioComponent()->PitchModulationMax = 1.0f;
		GetAudioComponent()->PitchModulationMin = 1.0f;
		GetAudioComponent()->VolumeModulationMax = 1.0f;
		GetAudioComponent()->VolumeModulationMin = 1.0f;
	}
	

	
	//�ش� Actor�� LableName�� �ۼ�
	this->SetActorLabel(SoundLabelName);

	//������ default location ���� �ٿ��� Actor�� location�� �̿��� ����
	this->SetActorLocation(Actor->GetActorLocation());

	//�ش� Actor�� �ٿ��� Actor�� ���̰� ������� Ʈ�������� ��������.
	this->AttachToActor(const_cast<AActor*>(Actor), FAttachmentTransformRules::KeepWorldTransform);
	
	//������ ���ÿ� �����ϴ� ������ true��� �ٷ� �����Ų��.
	if (GetAudioComponent()->bAutoActivate)
		Play();
}
//���� Actor ����
void AVPAmbientSound::DestroySound()
{
	Destroy();
}
//���̵� ����� ���� ���ص� �ɵ�
void AVPAmbientSound::FadeInVP(float FadeInDuration, float FadeVolumeLevel)
{
	FadeIn(FadeInDuration, FadeVolumeLevel);
}

void AVPAmbientSound::FadeOutVP(float FadeOutDuration, float FadeVolumeLevel)
{
	FadeOut(FadeOutDuration, FadeVolumeLevel);
}
// ���� ����
void AVPAmbientSound::AdjustVolumeVP(float AdjustVolumeDuration, float AdjustVolumeLevel)
{
	AdjustVolume(AdjustVolumeDuration, AdjustVolumeLevel);
}

void AVPAmbientSound::PlayVPNormal()
{
	Play();
}

void AVPAmbientSound::PlayVPDelay(float StartTime =0.0f)
{
	Play(StartTime);
}

void AVPAmbientSound::StopVP()
{
	Stop();
}

UAudioComponent * AVPAmbientSound::GetAudioComponentVP() const
{
	return GetAudioComponent();
}

void AVPAmbientSound::Pause()
{
	if (!GetAudioComponent()->bIsPaused)
	{
		GetAudioComponent()->SetPaused(true);
	}
	else
	{
		GetAudioComponent()->SetPaused(false);
	}
}



void AVPAmbientSound::SetupGizmo(FTransform Transform)
{
}

//���� ���尡 �ش� ������ ���� Sound���ͷμ� �������� �����ϴ� �Լ�
//�� �Լ��� �ܺ�(�Ƹ��� UI���� �� ��)���� ����Ͽ� �����ؾ���.
bool AVPAmbientSound::CheckIsUniqueSound(const AActor* Actor)
{
	TArray<AActor*> ChildSound;
	Actor->GetAttachedActors(ChildSound);
	for (int i = 0; i < ChildSound.Num(); ++i)
	{
		if (ChildSound[i]->GetActorLabel() == "AmbientSound") return false;
	}

	return true;
}



