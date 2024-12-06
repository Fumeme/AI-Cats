#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Node.h"
#include "Tile.h"
#include "Scene.h"
#include "KinematicBody.h"

#include "Seek.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;



public:
	std::vector<Node*> path;  // stores the path
	int currentTargetIndex;  // stores the current target index in the path
	Character()
	{
		body = NULL;
		scene = NULL;
	};

	~Character() {};

	Node* getPlayerNode();

	Node* getNode();

	vector<Node*> getPath() { return path; }

	void setPath(vector<Node*> path_temp);
	bool OnCreate(Scene* scene_);
	void OnDestroy();
	bool setTextureWith(string file);
	void Update(float time);
	float calculateDistance(const Vec3& vec);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f) const;

};

#endif

