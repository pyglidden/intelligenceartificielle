#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_LetsFight,
  Msg_AcceptFight,
  Msg_Boblose,
  Msg_Soulardlose,
  Msg_GoldGiven,
  Msg_GoldStolen,
  Msg_NotAvailable,
  Msg_Nothandle
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
   return "StewReady";

  case 2:

	return "LetsFight";

  case 3:

	  return "AcceptFight";

  case 4:

	  return "Boblose";

  case 5:

	  return "Soulardlose";

  case 6:

	  return "GoldGiven";

  case 7:

	  return "GoldStolen";

  case 8:

	  return "NotAvailable";

  default:

    return "Not recognized!";
  }
}

#endif