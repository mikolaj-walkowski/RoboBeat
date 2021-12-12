#include "Logic.h"


void LogicInterface::accept(LogicInterface* lI)
{
	lI->nullReact(this);
}

void LogicInterface::playerReact(PlayerLI* p)
{
}

void LogicInterface::projectileReact(ProjectileLI* t)
{
}

void LogicInterface::nullReact(LogicInterface* lI)
{
}

//void PlayerLI::accept(LogicInterface* lI)
//{
//	lI->playerReact(this);
//}
//
//void PlayerLI::playerReact(PlayerLI* p)
//{
//
//}
//
//void PlayerLI::projectileReact(ProjectileLI* t)
//{
//}

