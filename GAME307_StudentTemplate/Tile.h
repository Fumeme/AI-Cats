#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>
#include <Scene.h>
#include "Node.h"





class Tile
{
private:
	float width, height;
	Uint8 r, g, b, a;
	Vec3 pos;
	Node* node;
	Scene* scene;
	bool passable;
	SDL_Color color;
	SDL_Rect rect;
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();


	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;

	}

public:
	Tile(Node* node, Vec3 pos_, float width_, float height_, Scene* scene_);
	virtual ~Tile() {}
	void Render();
	Node* getNode() const { return node; }
	bool isTileBlocked();
	void setColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_);
	void changeColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_);
	void setPassable(bool passable_);
	bool isPassable() const {
		return passable;
	}





};

