#ifndef DRUNKER_H
#define DRUNKER_H
//------------------------------------------------------------------------
//
//  Name:   Drunker.h
//
//  Desc:   A class defining a drunk.
//
//  Author: Julien Samson & Pierre-Yves Glidden
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "../Common/misc/ConsoleUtils.h"
#include "DrunkerOwnedStates.h"
#include "../Common/fsm/StateMachine.h"

//class State;
struct Telegram;

//the amount of gold a Drunker must have before he feels he can go home
const int DrunkerComfortLevel       = 5;
//the amount of nuggets a Drunker can carry
const int DrunkerMaxNuggets         = 20;
//above this value a Drunker is thirsty
const int DrunkerThirstLevel        = 5;
//above this value a Drunker is sleepy
const int DrunkerTirednessThreshold = 5;



class Drunker : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Drunker>*  m_pStateMachine;
  
  location_type         m_Location;

  //how many nuggets the Drunker has in his pockets
  int                   m_iGoldCarried;

  //the higher the value, the thirstier the Drunker
  int                   m_iThirst;

  //the higher the value, the more tired the Drunker
  int                   m_iFatigue;

public:

  Drunker(int id):m_Location(shack),
                          m_iGoldCarried(0),
                          m_iThirst(0),
                          m_iFatigue(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Drunker>(this);
    
    m_pStateMachine->SetCurrentState(ReturnToCardBox::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE Drunker */
  }

  ~Drunker(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Drunker>* GetFSM()const{return m_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(int val) { m_iGoldCarried = val; }
  void          AddToGoldCarried(int val);
  int           StealGold(int chance_one, int chance_two, int chance_three);


  void          PutCoinInMachine() {m_iGoldCarried -= 1;}
  bool			MoneyAvailable()const;

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  bool          Thirsty()const; 
  void          BuyAndDrinkAWhiskey(){m_iThirst -= 2; m_iGoldCarried-=1;}

};



#endif
