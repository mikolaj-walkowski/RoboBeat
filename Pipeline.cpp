#include "Pipeline.h"
#include "TextureLoader.h"

Pipeline* Pipeline::singleton = nullptr;

Pipeline::Pipeline() {

}

Pipeline* Pipeline::getInstance() {
	if (singleton == nullptr) {
		singleton = new Pipeline();
	}
	return singleton;
}

void Pipeline::proccesColisions()
{

	for (auto dEnt = movableEnts.begin(); dEnt != movableEnts.end();) {
		if (auto ref = dEnt->lock())
		{
			for (auto dEnt2 = std::next(dEnt, 1); dEnt2 != movableEnts.end();) {
				if (auto ref2 = dEnt2->lock()) {
					if (ref->getCollisonInterface()->isInRange(ref2->getCollisonInterface())) {
						auto wek = ref->getCollisonInterface()->collide(ref2->getCollisonInterface());
						if (wek != glm::vec2(0.0, 0.0)) {
							if (wek.y == -1.0) ref->getPhysicsInterface()->touching_stat = true;
							if (wek.y == 1.0) ref2->getPhysicsInterface()->touching_stat = true;

							registerdEvents.push(std::make_pair(wek, std::make_pair(ref, ref2)));
						}
					}
					++dEnt2;
				}
				else movableEnts.erase(dEnt2);
			}
			for (auto sEnt = statEnts.begin(); sEnt != statEnts.end();) {
				if (auto ref2 = sEnt->lock()) {
					if (ref->getCollisonInterface()->isInRange(ref2->getCollisonInterface())) {
						auto wek = ref->getCollisonInterface()->collide(ref2->getCollisonInterface());
						if (wek != glm::vec2(0.0, 0.0)) {
							if (wek.y == -1.0) ref->getPhysicsInterface()->touching_stat = true;
							registerdEvents.push(std::make_pair(wek, std::make_pair(ref, ref2)));
						}
					}
					++sEnt;
				}
				else statEnts.erase(sEnt);
			}
			++dEnt;
		}
		else movableEnts.erase(dEnt);
	}
}

void Pipeline::proccesLogic()
{
}

void Pipeline::processPhysics(const float& dT)
{

	for (auto dEnt = movableEnts.begin(); dEnt != movableEnts.end();) {
		if (auto ref = dEnt->lock()) {
			ref->getPhysicsInterface()->changeVelo(dT);
			++dEnt;
		}
		else statEnts.erase(dEnt);
	}

	while (!registerdEvents.empty())
	{
		auto curr = registerdEvents.front();
		if (auto ref1 = curr.second.first.lock()) {
			if (auto ref2 = curr.second.second.lock()) { //Nie wiem dlaczego ale z and mi nie dzia�a
				ref1->getPhysicsInterface()->resolveCollision(curr.first, ref2->getPhysicsInterface());
			}
		}
		registerdEvents.pop();
	}

	for (auto dEnt = movableEnts.begin(); dEnt != movableEnts.end();) {
		if (auto ref = dEnt->lock()) {
			ref->getPhysicsInterface()->move(dT);
			ref->getPhysicsInterface()->touching_stat = false;
			++dEnt;
		}
		else statEnts.erase(dEnt);
	}

}
void Pipeline::worldSize()
{
	printf("Size of world list %d\n", world.size());
}
void Pipeline::initalizeEnts()
{
	glm::vec2* pos = new glm::vec2(0.0, 0.0);
	std::shared_ptr<Entity> sEnt = std::shared_ptr<Entity>(new Entity(pos, new SquareCollision(pos, glm::vec2(100, 100)), new StaticObject(pos), new DrawSimpleSquare(pos, glm::vec2(100, 100), glm::vec4(0, 1, 0, 1))));
	world.push_back(sEnt);
	statEnts.push_back(sEnt);
	foreground.push_back(sEnt);

	pos = new glm::vec2(-150.0, -20.0);
	sEnt = std::shared_ptr<Entity>(new Entity(pos, new SquareCollision(pos, glm::vec2(200, 30)), new StaticObject(pos), new DrawSimpleSquare(pos, glm::vec2(200, 30), glm::vec4(0, 1, 1, 1))));
	world.push_back(sEnt);
	statEnts.push_back(sEnt);
	foreground.push_back(sEnt);


	glm::vec2* pos2 = new glm::vec2(0.0, 200.0);

	std::shared_ptr<Entity> dEnt = std::shared_ptr<Entity>(new Entity(pos2, new SquareCollision(pos2, glm::vec2(50.f, 50.f)), new DynamicObject(pos2), new DrawSimpleSquare(pos2, glm::vec2(50, 50), glm::vec4(1,0,0,1))));
	world.push_back(dEnt);
	movableEnts.push_back(dEnt);
	foreground.push_back(dEnt);
	player = dEnt;
}
void Pipeline::attachKey(std::map<std::string, bool>* _keys) {
	keys = _keys;
}
void Pipeline::proccesKeyinput()
{
	auto pPI = player->getPhysicsInterface();
	if(pPI->touching_stat && (*keys)["W"]) printf("Print t_stat %d\n" , player->getPhysicsInterface()->touching_stat);
	pPI->setMomentVelocity(glm::vec2((*keys)["D"] - (*keys)["A"],0));
	((DynamicObject*)pPI)->velocity.y += (pPI->touching_stat && (*keys)["W"])* 300;//((DynamicObject*)pPI)->speed; //TODO hate that
}
ShaderProgram* Pipeline::getSP(std::string name)
{
	return shaderPrograms[name];
}
GLuint* Pipeline::getTex(std::string name)
{
	return textures[name];
}
void Pipeline::initializeSPs()
{
	shaderPrograms.insert(std::pair<std::string, ShaderProgram*>("spFullColor", new ShaderProgram("v_FullColor.glsl", NULL, "f_FullColor.glsl")));
	shaderPrograms.insert(std::pair<std::string, ShaderProgram*>("spTextured", new ShaderProgram("v_Textured.glsl", NULL, "f_Textured.glsl")));

	textures = loadTexturesdir("Textury");
}
void Pipeline::draw()
{
	for (auto itr = foreground.begin(); itr != foreground.end();) {
		if (auto ref = itr->lock()) {
			auto sp = shaderPrograms[ref->getDrawingInterface()->spName];
			sp->use();
			glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));

			ref->getDrawingInterface()->draw();
			++itr;
		}
		else
			foreground.erase(itr);
	}
}

void Pipeline::deleteSPs()
{
	for (auto itr : shaderPrograms) {
		delete itr.second;
	}
	shaderPrograms.clear();
}


