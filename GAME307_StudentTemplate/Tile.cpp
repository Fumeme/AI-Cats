#include "Tile.h"
#include <SDL.h>
#include <SDL_image.h>

Tile::Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_) :
	node{ node_ }, pos{ pos_ }, width{ width_ }, height{ height_ }, scene{ scene_ }, passable{ true }, color{ 17,178,178,255 }
{

}

void Tile::setColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
{

	color = { r,g,b,a };

}

void Tile::changeColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
{

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Tile::setPassable(bool passable_)
{
	std::cout << "set inpassable" << passable_ << std::endl;
	this->passable = passable_;
}






void Tile::Render()
{


	Vec3 topleft, bottomright, topLeftScreen, bottomRightScreen;


	topleft = Vec3(pos.x - 0.5 * width, pos.y - 0.5 * height, 0.0f);
	bottomright = Vec3(pos.x + 0.5 * width, pos.y + 0.5 * height, 0.0f);
	topLeftScreen = projectionMatrix * topleft;
	bottomRightScreen = projectionMatrix * bottomright;

	rect =
	{
	static_cast<int>(topLeftScreen.x),
	static_cast<int>(topLeftScreen.y),
	static_cast<int>(bottomRightScreen.x - topLeftScreen.x),
	static_cast<int>(bottomRightScreen.y - topLeftScreen.y),

	};




	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);

	//draw border around tile
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);


}



