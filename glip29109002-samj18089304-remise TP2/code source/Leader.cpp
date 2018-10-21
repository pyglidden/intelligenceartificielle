#include "Leader.h"
#include "Vehicle.h"
#include "../Common/2d/C2DMatrix.h"
#include "../Common/2d/Geometry.h"
#include "SteeringBehaviors.h"
#include "../Common/2d/Transformations.h"
#include "GameWorld.h"
#include "../Common/misc/CellSpacePartition.h"
#include "../Common/misc/cgdi.h"

using std::vector;
using std::list;


//----------------------------- actor ------------------------------------
//------------------------------------------------------------------------
Leader::Leader(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale): Vehicle(world,
		position,
		rotation,
		velocity,
		mass,
		max_force,
		max_speed,
		max_turn_rate,
		scale)
{

}
//---------------------------- dtor -------------------------------------
//-----------------------------------------------------------------------
Leader::~Leader()
{

}


