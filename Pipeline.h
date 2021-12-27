#pragma once
#include "Entity.h"
#include "LogicDecorators.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Queue>
#include <memory>
#include "ShaderProgram.h"
#include <map>
#include <string>
#include <list>

class Pipeline {
private:
	std::list<std::shared_ptr<Entity>> world;
	std::list<std::weak_ptr<Entity>> movableEnts;
	std::list<std::weak_ptr<Entity>> statEnts;
	std::list<std::weak_ptr<Entity>> sterable;
	std::queue<std::pair<glm::vec2, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Entity>>>> registerdEvents;
	static Pipeline* singleton;
	std::shared_ptr<Entity> player;
	std::map<std::string, bool>* keys;
	std::map<std::string, GLuint> textures;
	Pipeline();
public:
	float dT;
	Pipeline(Pipeline& other) = delete;
	void operator=(const Pipeline&) = delete;
	static Pipeline* getInstance();
	void proccesColisions();
	void proccesLogic();
	void processPhysics();
	void worldSize();
	void initalizeEnts();
	void attachKey(std::map<std::string, bool>*);
	void proccesKeyinput();
	//--------Drawing Stuff----------
	std::list<std::weak_ptr<Entity>> foreground;
	std::map<std::string, ShaderProgram*> shaderPrograms;
	glm::mat4 P = glm::ortho(-400.f,400.f,-225.f,225.f);

	Entity* background;

	ShaderProgram* getSP(std::string name);
	GLuint getTex(std::string name);
	void initializeSPs();
	void deleteSPs();
	void draw();
};

