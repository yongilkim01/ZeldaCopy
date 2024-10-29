#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
	APlayMap* PMAP1 = GetWorld()->SpawnActor<APlayMap>();
	PMAP1->SetActorLocation({ 700, 200 });
	APlayMap* PMAP2 = GetWorld()->SpawnActor<APlayMap>();
	PMAP2->SetActorLocation({ 500, 1000 });
	APlayMap* PMAP3 = GetWorld()->SpawnActor<APlayMap>();
	PMAP3->SetActorLocation({ 900, 600 });
}

