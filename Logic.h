#pragma once
class PlayerLI;
class ProjectileLI;

class LogicInterface //TODO w sumie to nie wiem czy to zostaiwe ale trzeba dorobiæ logikê w PipeLine
{
public:
	virtual void accept(LogicInterface* lI);
	virtual void playerReact(PlayerLI* p);
	virtual void projectileReact(ProjectileLI* t);
	virtual void nullReact(LogicInterface* lI);
};
//class PlayerLI : public LogicInterface
//{
//public:
//	float hp = 5.0;
//	void accept(LogicInterface* lI);
//	void playerReact(PlayerLI* p);
//	void projectileReact(ProjectileLI* t);
//	void nullReact(LogicInterface* lI);
//	
//private:
//
//};
//class ProjectileLI : public LogicInterface
//{
//	void accept(LogicInterface* lI);
//	void playerReact(PlayerLI* p);
//	void projectileReact(ProjectileLI* t);
//	void nullReact(LogicInterface* lI);
//
//};


//TODO klasa gracza mo¿e na spotkaniu 
//TODO klasa udeerzenie która zadaje graczowi/hasHealth obra¿enia i znika po ustalonym czasie.
