#include "FPSGameMode.h"
#include "Engine.h"
#include "FPSHUD.h"
#include "../Characters/FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "CPlayerState.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_CPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
	PlayerStateClass = ACPlayerState::StaticClass();
}

void AFPSGameMode::OnActorKilled(AActor* VictimActor)
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElpased", Player->GetController());

		float RespawnDelay = 3.f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}
}

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	//GetAllActorsByClass
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		if (It->PlayerStartTag == "Red")
		{
			RedTeamPlayerStarts.Add(*It);
		}
		else
		{
			GreenTeamPlayerStarts.Add(*It);
		}
	}
	UE_LOG(LogTemp, Error, TEXT("RedTeam : %d"), RedTeamPlayerStarts.Num());
	UE_LOG(LogTemp, Error, TEXT("GreenTeam : %d"), GreenTeamPlayerStarts.Num());
}

void AFPSGameMode::PostLogin(APlayerController* NewPlayer)
{
	//LaunchGame-> Do Not Work
	Super::PostLogin(NewPlayer);

	AFPSCharacter* PlayerCharacter = NewPlayer->GetPawn<AFPSCharacter>();
	ACPlayerState* PS = NewPlayer->GetPlayerState<ACPlayerState>();

	if (PlayerCharacter && PS)
	{
		if (RedTeamPawns.Num() > GreenTeamPawns.Num())
		{
			PS->Team = ETeamType::Green;
			GreenTeamPawns.Add(PlayerCharacter);
		}
		else
		{
			PS->Team = ETeamType::Red;
			RedTeamPawns.Add(PlayerCharacter);
		}
	}

	PlayerCharacter->SetTeamColor(PS->Team);
}

void AFPSGameMode::RespawnPlayerElpased(APlayerController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
		AFPSCharacter* NewPlayerCharacter = Controller->GetPawn<AFPSCharacter>();

		ACPlayerState* PS = Controller->GetPlayerState<ACPlayerState>();
		if (PS)
		{
			NewPlayerCharacter->SetTeamColor(PS->Team);
		}
	}
}
