#include "DrunkerOwnedStates.h"
#include "../Common/fsm/State.h"
#include "Drunker.h"
#include "Locations.h"
#include "../Common/messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
//#include "../Common/Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
StealForNugget* StealForNugget::Instance()
{
  static StealForNugget instance;

  return &instance;
}

void StealForNugget::Enter(Drunker* pDrunker)
{
  //Si le Soulard n'est pas dans le village, il doit changer de location pour 
  //la ville
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  if (pDrunker->Location() != city)
  {
	
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Walkin' in the city ";

    pDrunker->ChangeLocation(city);
  }
}

void StealForNugget::Execute(Drunker* pDrunker)
{  
	int qte = 0;
  //Maintennt que le Soulard est dans la ville, il vole les gens de la ville (75% de réussite)
  //Une fois qu'il a soif, il va boire au saloon. 
  qte = pDrunker->StealGold(90, 50, 25);

  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Stealin' up " << qte << " nugget";

  pDrunker->IncreaseFatigue();

  //Si assoifé, aller au saloon
  if (pDrunker->Thirsty())
  {
    pDrunker->GetFSM()->ChangeState(DrunkerQuenchThirst::Instance());
  }
}

void StealForNugget::Exit(Drunker* pDrunker)
{
	cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " 
       << "Need a drink after this freshly stolen' gold";
}

bool StealForNugget::OnMessage(Drunker* pDrunker, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

ReturnToCardBox* ReturnToCardBox::Instance()
{
  static ReturnToCardBox instance;

  return &instance;
}

void ReturnToCardBox::Enter(Drunker* pDrunker)
{
  if (pDrunker->Location() != shack)
  {
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Walkin' home";
    pDrunker->ChangeLocation(shack); 
  }
}

void ReturnToCardBox::Execute(Drunker* pDrunker)
{ 
  if (!pDrunker->Fatigued())
  {
	  cout << "\n" << GetNameOfEntity(pDrunker->ID()) 
		   << ": " << "Time to steal some gold!";

	  pDrunker->GetFSM()->ChangeState(StealForNugget::Instance());
  }
  else {
	  pDrunker->DecreaseFatigue();
	  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "ZZZZ... ";
  }
}

void ReturnToCardBox::Exit(Drunker* pDrunker)
{ 
}

bool ReturnToCardBox::OnMessage(Drunker* pDrunker, const Telegram& msg)
{
   return false; //send message to global message handler
}

//------------------------------------------------------------------------PlayCoinMachine

PlayCoinMachine* PlayCoinMachine::Instance()
{
	static PlayCoinMachine instance;

	return &instance;
}

void PlayCoinMachine::Enter(Drunker* pDrunker)
{
	if (pDrunker->Location() != coinmachine)
	{
		pDrunker->ChangeLocation(coinmachine);
		cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Can't wait to get rich with the coin machine!";
	}
}

void PlayCoinMachine::Execute(Drunker* pDrunker)
{
	if (pDrunker->MoneyAvailable()) {

		cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Come on!";
		pDrunker->PutCoinInMachine();
		pDrunker->IncreaseFatigue();


		int max = 99, min = 0;
		int winChance = rand() % (max - min + 1) + min;

		if (winChance <= 10) {
			pDrunker->AddToGoldCarried(3);

			cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Yes I'm a winner!";
		}
	} 
	
	if(!pDrunker->MoneyAvailable())
	{
		cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "DAMN YOU.. no more money!";
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pDrunker->ID(),        //ID of sender
			ent_Miner_Bob,         //ID of recipient
			Msg_LetsFight,		   //the message
			NO_ADDITIONAL_INFO);
	}
}

void PlayCoinMachine::Exit(Drunker* pDrunker)
{
}

bool PlayCoinMachine::OnMessage(Drunker* pDrunker, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{

	case Msg_NotAvailable:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunker->ID())
			<< " at time: ";// << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunker->ID())
			<< ": CRAP! I'm alone...";

		pDrunker->GetFSM()->ChangeState(StealForNugget::Instance());

		return true;

	case Msg_AcceptFight:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunker->ID())
			<< " at time: ";// << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunker->ID())
			<< ": HAHA I'm going to win!";

		pDrunker->GetFSM()->ChangeState(DrunkerFight::Instance());

		return true;
	}//end
	pDrunker->GetFSM()->ChangeState(ReturnToCardBox::Instance());
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------Fight

DrunkerFight* DrunkerFight::Instance()
{
	static DrunkerFight instance;

	return &instance;
}

void DrunkerFight::Enter(Drunker* pDrunker)
{
	cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Okay let's fight!";
}

void DrunkerFight::Execute(Drunker* pDrunker)
{
	pDrunker->IncreaseFatigue();


	cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "I'm getting tired";

	//if too fatigued, lose the fight and go home
	if (pDrunker->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Damn I lost";
		pDrunker->GetFSM()->ChangeState(ReturnToCardBox::Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pDrunker->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_Soulardlose,   //the message
			NO_ADDITIONAL_INFO);
	}
}

void DrunkerFight::Exit(Drunker* pDrunker)
{
	cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
		<< "Time to go home";
}

bool DrunkerFight::OnMessage(Drunker* pDrunker, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Boblose:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunker->ID())
			<< " at time: ";// << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunker->ID())
			<< ": I won";

		pDrunker->GetFSM()->ChangeState(ReturnToCardBox::Instance());

		return true;

	}//end switch

	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------QuenchThirst

DrunkerQuenchThirst* DrunkerQuenchThirst::Instance()
{
  static DrunkerQuenchThirst instance;

  return &instance;
}

void DrunkerQuenchThirst::Enter(Drunker* pDrunker)
{
  if (pDrunker->Location() != saloon)
  {    
    pDrunker->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Getting to the saloon. Can't wait to drink again!";
  }
}

void DrunkerQuenchThirst::Execute(Drunker* pDrunker)
{
  pDrunker->BuyAndDrinkAWhiskey();

  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "WHAT a tasty drink";

  //S'il n'a plus soif et qu'il lui reste de l'argent, aller à la machine à sous
  if (!pDrunker->Thirsty() && pDrunker->MoneyAvailable())
  {
	  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Time to make money";
    pDrunker->GetFSM()->ChangeState(PlayCoinMachine::Instance());
  }
  else if (pDrunker->Thirsty() && !pDrunker->MoneyAvailable())
  {
	  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "I want to drink but no more money!";
	  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		  pDrunker->ID(),        //ID of sender
		  ent_Miner_Bob,         //ID of recipient
		  Msg_LetsFight,		   //the message
		  NO_ADDITIONAL_INFO);
  } 
  else if (!pDrunker->Thirsty() && !pDrunker->MoneyAvailable())
  {
	  cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "So tired";
    pDrunker->GetFSM()->ChangeState(ReturnToCardBox::Instance());
  }
}

void DrunkerQuenchThirst::Exit(Drunker* pDrunker)
{ 

}

bool DrunkerQuenchThirst::OnMessage(Drunker* pDrunker, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
	case Msg_AcceptFight:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunker->ID())
			<< " at time: ";// << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunker->ID())
			<< ": HAHA I'm going to win!";

		pDrunker->GetFSM()->ChangeState(DrunkerFight::Instance());

		return true;
	}//end
	pDrunker->GetFSM()->ChangeState(ReturnToCardBox::Instance());

  //send msg to global message handler
  return false;
}

