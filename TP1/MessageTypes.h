#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_LetsFight,
  Msg_Boblose,
  Msg_Soulardlose,
  Msg_GoldGiven
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 1:
    
    return "HiHoneyImHome"; 

  case 2:
    
    return "StewReady";

  case 3:

	return "LetsFight";

  case 4:

	  return "Boblose";

  case 5:

	  return "Soulardlose";

  case 6:

	  return "GoldGiven";

  default:

    return "Not recognized!";
  }
}

#endif