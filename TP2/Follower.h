#ifndef FOLLOWER_H
#define FOLLOWER_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   Follower.h
//
//  Desc:   Definition of a simple Leader that uses steering behaviors
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "Vehicle.h"
#include "../Common/2d/Vector2D.h"
#include "../Common/misc/Smoother.h"

#include <vector>
#include <list>
#include <string>

class GameWorld;
class SteeringBehavior;



class Follower : public Vehicle
{
private:

public:

	Follower(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	~Follower();

};



#endif
