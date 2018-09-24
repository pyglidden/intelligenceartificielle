#include "Drunker.h"

bool Drunker::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Drunker::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

  m_iThirst += 1;
  
  m_pStateMachine->Update();
}

void Drunker::AddToGoldCarried(const int val)
{
	m_iGoldCarried += val;

	if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

bool Drunker::MoneyAvailable()const
{

	if (m_iGoldCarried > 0) {
		return true;
	}
	else {
		return false;
	}
}

int Drunker::StealGold(const int chance_one, const int chance_two, const int chance_three) 
{
	int qte = 0;
  int max = 99, min = 0;
  int steal = rand()%(max-min + 1) + min;

  if(steal <= chance_one) 
  {
    if(steal <= chance_two) 
    {
      if(steal <= chance_three) 
      {
        m_iGoldCarried += 3;
		qte = 3;
      }
	  else
	  {
		m_iGoldCarried += 2;
		qte = 2;
	  }
    }
	else
	{
		m_iGoldCarried += 1;
		qte = 1;
	}
  }
  else
  {
	  m_iGoldCarried += 0;
	  qte = 0;
  }

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;

  return qte;
}

bool Drunker::Thirsty()const
{
  if (m_iThirst >= DrunkerThirstLevel){return true;}

  return false;
}

bool Drunker::Fatigued()const
{
  if (m_iFatigue > DrunkerTirednessThreshold)
  {
    return true;
  }

  return false;
}
