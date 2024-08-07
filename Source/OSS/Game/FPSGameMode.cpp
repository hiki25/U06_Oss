#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "../Characters/FPSCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "../OSS.h"

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

	LogOnScreen(this, __FUNCTION__); //Hack

	//GetAllActorsByClass
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		if (It->PlayerStartTag == "Red")
		{
			if (RedTeamPlayerStarts.Find(*It) < 0 )
			{
				RedTeamPlayerStarts.Add(*It);
			}
		}
		else
		{
			if (GreenTeamPlayerStarts.Find(*It) < 0)
			{
				GreenTeamPlayerStarts.Add(*It);
			}
		}
	}
	//UE_LOG(LogTemp, Error, TEXT("RedTeam : %d"), RedTeamPlayerStarts.Num());
	//UE_LOG(LogTemp, Error, TEXT("GreenTeam : %d"), GreenTeamPlayerStarts.Num());
}

void AFPSGameMode::PostLogin(APlayerController* NewPlayer)
{
	//LaunchGame-> Do Not Work
	Super::PostLogin(NewPlayer);

	LogOnScreen(this, __FUNCTION__); //Hack

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
	MoveToPlayerStart(PlayerCharacter,PS->Team);
}

void AFPSGameMode::MoveToPlayerStart(APawn* Pawn, ETeamType Team)
{
	//LogOnScreen(this, FString::FromInt(RedTeamPlayerStarts.Num()), FColor::Red); //Hack
	//LogOnScreen(this, FString::FromInt(GreenTeamPlayerStarts.Num()), FColor::Green); //Hack

	if (RedTeamPlayerStarts.Num() < 1 || GreenTeamPlayerStarts.Num() < 1)
	{
		StartPlay();
	}

	int32 Random = 0;
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
	switch (Team)
	{
	case ETeamType::Red:
	{
		Random = UKismetMathLibrary::RandomInteger(RedTeamPlayerStarts.Num() - 1);
		Location = RedTeamPlayerStarts[Random]->GetActorLocation();
		Rotation = RedTeamPlayerStarts[Random]->GetActorRotation();
		break;
	}

	case ETeamType::Green:
	{
		Random = UKismetMathLibrary::RandomInteger(GreenTeamPlayerStarts.Num() - 1);
		Location = GreenTeamPlayerStarts[Random]->GetActorLocation();
		Rotation = GreenTeamPlayerStarts[Random]->GetActorRotation();
		break;
	}
	}
	Pawn->SetActorLocation(Location);
	//Pawn->SetActorRotation(Rotation);
	if (Pawn->GetController())
	{
		Pawn->GetController()->ClientSetRotation(Rotation,true);
	}
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
			MoveToPlayerStart(NewPlayerCharacter, PS->Team);
		}
	}
}

