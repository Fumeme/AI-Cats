#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "GameManager.h"
#include <Graph.h>

using namespace MATH;

class Scene {
private:
	Graph graph;

public:
	Graph* getGraph() {
		if (&graph) {
			return &graph;
		}
		else {
			std::cerr << "Error: Invalid graph error." << std::endl;
			return nullptr;

		}

	}

	class GameManager* game = NULL;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
	virtual ~Scene() {};
	virtual float getxAxis() = 0;
	virtual float getyAxis() = 0;
	virtual SDL_Window* getWindow() = 0;
	virtual Matrix4 getProjectionMatrix() = 0;
	virtual Matrix4 getInverseMatrix() = 0;
	void renderPath(const std::vector<Node*>& path);
};

#endif
