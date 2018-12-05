#ifndef GATLING_H
#define GATLING_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Weapon_Gatling.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   
//-----------------------------------------------------------------------------
#include "Raven_Weapon.h"


class  Raven_Bot;



class Gatling : public Raven_Weapon
{
private:

  void  InitializeFuzzyModule();
  
public:

	Gatling(Raven_Bot*   owner);


  void  Render();

  void  ShootAt(Vector2D pos);

  double GetDesirability(double DistToTarget);
};



#endif