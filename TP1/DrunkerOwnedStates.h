#ifndef DRUNKER_OWNED_STATES_H
#define DRUNKER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunker class.
//          Note that a global state has not been implemented.
//
//  Author: Pierre-Yves Glidden & Julien Samson
//
//------------------------------------------------------------------------
#include "../Common/fsm/State.h"

  
class Drunker;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the Drunker will walk to a goldmine and pick up a nugget
//  of gold. If the Drunker already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class StealForNugget : public State<Drunker>
{
private:
  
  StealForNugget(){}

  //copy ctor and assignment should be private
  StealForNugget(const StealForNugget&);
  StealForNugget& operator=(const StealForNugget&);
 
public:

  //this is a singleton
  static StealForNugget* Instance();

  virtual void Enter(Drunker* drunker);

  virtual void Execute(Drunker* drunker);

  virtual void Exit(Drunker* drunker);

  virtual bool OnMessage(Drunker* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Drunker will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class ReturnToCardBox : public State<Drunker>
{
private:
  
  ReturnToCardBox(){}

  //copy ctor and assignment should be private
  ReturnToCardBox(const ReturnToCardBox&);
  ReturnToCardBox& operator=(const ReturnToCardBox&);
 
public:

  //this is a singleton
  static ReturnToCardBox* Instance();

  virtual void Enter(Drunker* drunker);

  virtual void Execute(Drunker* drunker);

  virtual void Exit(Drunker* drunker);

  virtual bool OnMessage(Drunker* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunker changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the goldmine
//  and resumes his quest for nuggets.
//------------------------------------------------------------------------
class DrunkerQuenchThirst : public State<Drunker>
{
private:
  
	DrunkerQuenchThirst(){}

  //copy ctor and assignment should be private
	DrunkerQuenchThirst(const DrunkerQuenchThirst&);
	DrunkerQuenchThirst& operator=(const DrunkerQuenchThirst&);
 
public:

  //this is a singleton
  static DrunkerQuenchThirst* Instance();

  virtual void Enter(Drunker* drunker);

  virtual void Execute(Drunker* drunker);

  virtual void Exit(Drunker* drunker);

  virtual bool OnMessage(Drunker* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The Drunker play the coing machine
//
//------------------------------------------------------------------------
class PlayCoinMachine : public State<Drunker>
{
private:
  
  PlayCoinMachine(){}

  //copy ctor and assignment should be private
  PlayCoinMachine(const PlayCoinMachine&);
  PlayCoinMachine& operator=(const PlayCoinMachine&);
 
public:

  //this is a singleton
  static PlayCoinMachine* Instance();

  virtual void Enter(Drunker* drunker);

  virtual void Execute(Drunker* drunker);

  virtual void Exit(Drunker* drunker);

  virtual bool OnMessage(Drunker* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The Drunker fight the miner
//
//------------------------------------------------------------------------
class DrunkerFight : public State<Drunker>
{
private:
  
	DrunkerFight(){}

  //copy ctor and assignment should be private
	DrunkerFight(const DrunkerFight&);
	DrunkerFight& operator=(const DrunkerFight&);
 
public:

  //this is a singleton
  static DrunkerFight* Instance();

  virtual void Enter(Drunker* drunker);

  virtual void Execute(Drunker* drunker);

  virtual void Exit(Drunker* drunker);

  virtual bool OnMessage(Drunker* agent, const Telegram& msg);
};



#endif