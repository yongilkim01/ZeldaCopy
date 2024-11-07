#include "PreCompile.h"
#include "EngineCoreDebug.h"
#include <EnginePlatform/EngineWinDebug.h>
#include "EngineAPICore.h"

namespace UEngineDebug
{
	class DebugTextInfo
	{
	public:
		std::string Text;
		FVector2D Pos;
	};


	// ����
	std::vector<DebugTextInfo> DebugTexts;


	// #ifdef _DEBUG
	FVector2D EngineTextPos = FVector2D::ZERO;
	// #endif

#ifdef _DEBUG
	bool IsDebug = true;
#else
	bool IsDebug = false;
#endif

	void SetIsDebug(bool _IsDebug)
	{
		IsDebug = _IsDebug;
	}

	void SwitchIsDebug()
	{
		IsDebug = !IsDebug;
	}

	void CoreOutPutString(std::string_view _Text)
	{
		// #ifdef _DEBUG
				// �ٷ� ������� �ʴ´�.
		DebugTexts.push_back({ _Text.data(), EngineTextPos });
		EngineTextPos.Y += 20;
		// endif 
	}

	void CoreOutPutString(std::string_view _Text, FVector2D _Pos)
	{
		// #ifdef _DEBUG
		DebugTexts.push_back({ _Text.data(), _Pos });
		// #endif
	}

	class DebugPosInfo
	{
	public:
		FVector2D Pos;
		EDebugPosType Type;
	};


	std::vector<DebugPosInfo> DebugPoses;

	void CoreDebugPos(FVector2D _Pos, EDebugPosType _Type)
	{
		DebugPoses.push_back({ _Pos, _Type });
	}

	void PrintEngineDebugRender()
	{
		if (false == IsDebug)
		{
			return;
		}

		// void WinAPIOutPutString(UEngineWinImage * _Image, std::string_view _Text, FVector2D _Pos);
		UEngineWinImage* BackBuffer = UEngineAPICore::GetCore()->GetMainWindow().GetBackBuffer();

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			DebugTextInfo& Debug = DebugTexts[i];
			WinAPIOutPutString(BackBuffer, Debug.Text, Debug.Pos);
		}

		EngineTextPos = FVector2D::ZERO;
		DebugTexts.clear();

		FTransform Trans;
		Trans.Scale = FVector2D(6, 6);

		for (size_t i = 0; i < DebugPoses.size(); i++)
		{

			EDebugPosType Type = DebugPoses[i].Type;

			Trans.Location = DebugPoses[i].Pos;
			FVector2D LT = Trans.CenterLeftTop();
			FVector2D RB = Trans.CenterRightBottom();
			switch (Type)
			{
			case UEngineDebug::Rect:
				Rectangle(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			case UEngineDebug::Circle:
				Ellipse(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			default:
				break;
			}
		}

		DebugPoses.clear();

	}


}
