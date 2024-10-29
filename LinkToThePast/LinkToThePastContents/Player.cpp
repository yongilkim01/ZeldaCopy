#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
}

void APlayer::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}

void APlayer::Tick(float _DeltaTime)
{
	//if (UEngineInput::GetInst().IsDown('A'))
	//{
	//	int a = 0;
	//}

	// EngineInput::GetFree(EngineKey::HOME)
	// if (true == EngineInput::GetFree('A'))

	//// 안누르고 있을때 
	//if (true == EngineInput::GetFree("PlayerMove"))

	//// 키를 땟을때
	//if (true == EngineInput::GetUp("PlayerMove"))

	//// 계속 누르는 도중
	//if (true == EngineInput::GetPress("PlayerMove"))

	//// 가장 처음 한번 눌렀을때
	//if (true == EngineInput::GetDown("PlayerMove"))

	// Time::DeltaTime;

	// 여러분들의 컴퓨터가 1프레임이고
	// 선생님의 컴퓨터가 2프레임이

	// 게임시작하고 얼마지났다?

	//         여러분  제컴퓨터는
	// 0.5초             0.5        =+> 0.5         // 0.0, 0.0, => 0.5, 0.0
	// 1.0초    1.0f     0.5        =+> 1.0         // 0.5, 0.0, => 1.0, 0.0
	// 1.5초             0.5        =+> 1.5 - 1.0
	// 2.0초    1.0f     0.5        =+> 1.0         // 1.0, 0.0, => 2.0, 0.0

	// 델타임


	// 엔진에서 
	// 0.0, 0.0, => 1.0, 0.0

	// 내가 정해줘야 한다.
	// 렉걸렸어
	// 컴퓨터의 성능과 상관없이 => 같은 게임 내용을 보여주기 위해서 입니다. 

	// 기본적으로 어떤 기능을 만들때는

	// 내가 게임 엔진을 하고 있다면 무조건 엔진이 제공하는 기능을 써야한다.
	// 구현할수 있는 능력이 있다고 해도 엔진의 기능을 사용해야 한다.
	// 1. 컨텐츠 많이 사용하고 있다.
	// 2. 그리고 엔진이 버전업 되면 내가 만든게 그냥 무너진다. 
	// <= 엔진 버전 올라가면 내가 만든 것이 무너질수 있다. 5.4
	//    엔진을 고칠때 말하는 것.

	// 내가 직접 만들어야 한다면
	// 1. OS냐 std냐를 따져야 합니다.
	// 2. OS 기본적으로 하드웨어에 관련된건 대부분 Window
	//    CPU도 포함 대표적으로 추후 쓰레드를 배울때 이해하게 됩니다.
	// 3. std는 보통 문법적 측면에서 접근하는 문제들이 std가 지원해줄 가능성이 높다.
	//    배열 => 배열이 불편해 => std::vector

	// 그러면 그걸 유저들에게 대표적인 방법 랩핑 
	// EngineWindow가 우리엔진의 대표적인 랩핑 클래스입니다.
	// WindowAPI의 기능을 절대로 그냥 공개하는 경우는 없다.

	// 윈도우가 제공하는 기본 입력함수입니다.
	// 입력버퍼는 윈도우가 알아서 처리해주기 때문에
	// 입력이 있을때만 0이 아닌 수를 리턴하는 함수입니다.

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	//}

	// 마우스 왼쪽 버튼입니다.
	// 눌린 한순간만 체크할수 있는 기능이 필요하다.
	if (3.0f < UEngineInput::GetInst().IsPreeTime(VK_LBUTTON))
	{
		// 콘솔에서 슈팅 못만들면 API와서도 못만들어요.
		ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
		Ptr->SetActorLocation(GetActorLocation());
	}

}