#pragma once

namespace UEngineDebug
{
	enum EDebugPosType
	{
		Rect,
		Circle,
	};

	// MainWindow가 있다.

	void SetIsDebug(bool _IsDebug);

	void SwitchIsDebug();

	void CoreOutPutString(std::string_view _Text);

	void CoreOutPutString(std::string_view _Text, FVector2D _Pos);

	void CoreDebugPos(FVector2D _Pos, EDebugPosType _Type);

	// 분리해야 하겠네요

	void PrintEngineDebugRender();
}