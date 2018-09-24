#include <fstream>
#include <time.h>
#include <thread>         // std::thread

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunker.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "../Common/misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

void MinerThread(Miner* Bob)
{
	Bob->Update();
}

void MinersWifeThread(MinersWife* Elsa)
{
	Elsa->Update();
}

void DrunkerThread(Drunker* Jack)
{
	Jack->Update();
}

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  //MinersWife* Elsa = new MinersWife(ent_Elsa);

  //TODO: create soulard
  Drunker* Jack = new Drunker(ent_Soulard);

  //register them with the entity manager
  //TODO: register soulard
  EntityMgr->RegisterEntity(Bob);
  //EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Jack);

  //TODO: thread ici!!!
  
  for (int i = 0; i < 30; ++i)
  {
	  std::thread first(MinerThread, Bob);
	  Sleep(500);
	  //std::thread second(MinersWifeThread, Elsa);
	  std::thread third(DrunkerThread, Jack);
	  Sleep(500);
	  //Threads now runs concurrently

	  //pauses until other threads to finish
	  first.join();
	  //second.join();
	  third.join();

	  Dispatch->DispatchDelayedMessages();

	  Sleep(800);
  }
  
  
  //run Bob and Elsa through a few Update calls
  //TODO: retirer après que les thread soit fait
  /*for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Jack->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }*/

  //tidy up
  //TODO: delete soulard
  delete Bob;
  //delete Elsa;
  delete Jack;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






