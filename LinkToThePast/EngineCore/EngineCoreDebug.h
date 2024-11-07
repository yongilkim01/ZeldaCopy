#pragma once

namespace UEngineDebug
{
	enum EDebugPosType
	{
		Rect,
		Circle,
	};

	// MainWindow�� �ִ�.

	void SetIsDebug(bool _IsDebug);

	void SwitchIsDebug();

	void CoreOutPutString(std::string_view _Text);

	void CoreOutPutString(std::string_view _Text, FVector2D _Pos);

	void CoreDebugPos(FVector2D _Pos, EDebugPosType _Type);

	// �и��ؾ� �ϰڳ׿�

	void PrintEngineDebugRender();
}