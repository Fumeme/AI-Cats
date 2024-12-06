#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"
#include "Character.h"
#include "Node.h"
#include "Graph.h"
#include <Tile.h>


using namespace MATH;
class Scene1 : public Scene {
private:


	std::vector<Node*> sceneNodes;

	float tileHeight;
	float tileWidth;
	int w;
	int h;
	std::vector<std::vector<Tile*> > tiles;
	void CreateTiles();
	Node* getNodeAtPosition(int mouseX, int mouseY);
	Node* selectedNode;

	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4     inverseProjection;

	SDL_Surface* background;
	SDL_Texture* backgroundtexture;

	Character* blinky;
//	Cop* cop;

public:
	void calculateConnectionsWeights();
	//class Graph* graph;
	//Graph* getGraph() const { return graph; }
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
	void ClearConnections();


};

#endif
