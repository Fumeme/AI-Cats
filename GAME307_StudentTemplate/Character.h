#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"

#include "Seek.h"
#include "Node.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};

	~Character() {};
	Node* getNodeForPosition(const Vec3& position) const;
	std::vector<Node*> path;  // Holds the path for the AI to follow



	bool OnCreate(Scene* scene_);
	void OnDestroy();
	bool setTextureWith(string file);
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f) const;

};

#endif

