﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Command/CommandQueue.h"
#include "UEPrototype.h"
#include "VPFrameworkLibrary.h"
#include "UObjectIterator.h"
#include "Core/EditorModulesManager.h"
#include "Tool/ToolBase.h"



UCommandQueue::UCommandQueue()
{
	// DEBUG
	VP_CTOR;

	/* 유효하지 않은 싱글톤 CDO는 더이상 초기화를 진행하지 않습니다 */
	if (UVPFrameworkLibrary::IsValidSingletonCDO(this) == false)
	{
		return;
	}



	/* 상위 모듈을 불러와서 이벤트에 함수들을 바인딩합니다 */
	UEditorModulesManager* EditorModulesManager =
		UEditorModulesManager::GetGlobalEditorModulesManager();
	if (IsValid(EditorModulesManager) == false)
	{
		return;
	}

	FEventToRegister Event;
	Event.BindUFunction(this, "BindToEvents");
	EditorModulesManager->RegisterIf(Event);
}





void UCommandQueue::BindToEvents()
{
	// TODO : 모든 구체 도구들에 대한 바인드
	
}





void UCommandQueue::AddUndoQueue(UCommandBase * CommandExecuted)
{
	/* 커맨드가 유효한 지 검사합니다 */
	if (IsValid(CommandExecuted) == false)
	{
		VP_LOG(Warning, TEXT("커맨드가 유효하지 않습니다."));
		return;
	}
	
	/* UndoQueue에 추가합니다. */
	UndoQueue.Add(CommandExecuted);
}



void UCommandQueue::Undo()
{
	/* 큐가 비었는 지 확인합니다 */
	if (UndoQueue.Num() == 0)
	{
		VP_LOG(Warning, TEXT("취소할 명령이 없습니다."));
		return;
	}

	/* 커맨드를 UndoQueue에서 Dequeue하여 실행한 후,
		RedoQueue에 Enqueue합니다.*/
	UCommandBase* CommandToUndo;
	CommandToUndo = UndoQueue.Pop();

	CommandToUndo->Undo();
	RedoQueue.Add(CommandToUndo);
}



void UCommandQueue::Redo()
{
	/* 큐가 비었는 지 확인합니다 */
	if (RedoQueue.Num() == 0)
	{
		VP_LOG(Warning, TEXT("재실행할 명령이 없습니다."));
		return;
	}

	/* 커맨드를 RedoQueue에서 Dequeue하여 실행한 후,
		UndoQueue에 Enqueue합니다. */
	UCommandBase* CommandToRedo;
	CommandToRedo = RedoQueue.Pop();

	CommandToRedo->ExecuteIf();
	UndoQueue.Add(CommandToRedo);
}



void UCommandQueue::AddUndoEditQueue(UCommandBase * CommandExecuted)
{
	/* 커맨드가 유효한 지 검사합니다 */
	if (IsValid(CommandExecuted) == false)
	{
		VP_LOG(Warning, TEXT("커맨드가 유효하지 않습니다."));
		return;
	}

	/* UndoQueue에 추가합니다. */
	UndoEditQueue.Add(CommandExecuted);
}



void UCommandQueue::UndoEdit()
{
	/* 큐가 비었는 지 확인합니다 */
	if (UndoEditQueue.Num() == 0)
	{
		VP_LOG(Warning, TEXT("취소할 명령이 없습니다."));
		return;
	}

	/* 커맨드를 UndoEditQueue에서 Dequeue하여 실행한 후,
	RedoEditQueue에 Enqueue합니다.*/
	UCommandBase* CommandToUndo;
	CommandToUndo = UndoEditQueue.Pop();

	CommandToUndo->Undo();
	RedoEditQueue.Add(CommandToUndo);
}



void UCommandQueue::RedoEdit()
{
	/* 큐가 비었는 지 확인합니다 */
	if (RedoEditQueue.Num() == 0)
	{
		VP_LOG(Warning, TEXT("재실행할 명령이 없습니다."));
		return;
	}

	/* 커맨드를 RedoEditQueue에서 Dequeue하여 실행한 후,
	UndoEditQueue에 Enqueue합니다. */
	UCommandBase* CommandToRedo;
	CommandToRedo = RedoEditQueue.Pop();

	CommandToRedo->ExecuteIf();
	UndoEditQueue.Add(CommandToRedo);
}
