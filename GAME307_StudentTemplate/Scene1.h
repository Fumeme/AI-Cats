#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"
#include "Character.h"
#include "Graph.h"
#include "Node.h"
#include "Tile.h"
#include "StaticBody.h"
#include "KinematicSeek.h"

#include <vector>

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	StaticBody* myNPC;      // For kinematic movement
	Character* blinky;      // Another NPC or character

	float tileWidth;
	float tileHeight;

	Graph* graph;           // Graph for pathfinding
	std::vector<Node*> path; // The path found for NPC to follow
	int currentTargetIndex;  // Current index in the path for NPC

public:
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	
	void renderMyNPC();
	void findPath();
};

#endif
