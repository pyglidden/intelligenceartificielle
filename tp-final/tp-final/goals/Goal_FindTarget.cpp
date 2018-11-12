#include "Goal_Wander.h"
#include "Goal_FindTarget.h"
#include "..\Raven_Bot.h"
#include "..\Raven_SteeringBehaviors.h"





//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Wander::Activate()
{
  m_pOwner->GetSteering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Wander::Process()
{
  if (m_iStatus == inactive)
  {
	 
    Activate();
    m_iStatus = active;
  }

  return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Wander::Terminate()
{
  m_pOwner->GetSteering()->WanderOff();

  m_iStatus = completed;
}

