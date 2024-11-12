#include "Character.h"
#include "Tile.h"
#include "Node.h"


bool Character::OnCreate(Scene* scene_)
{
	path.clear();
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!body)
	{
		return false;
	}

	return true;
}

void Character::OnDestroy()
{
	path.clear();
	if (body)
	{
		if (body->getTexture())
		{
			SDL_DestroyTexture(body->getTexture());
		}
		delete body;

	}
};

bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	if (body->getTexture()) SDL_DestroyTexture(body->getTexture());
	body->setTexture(texture);
	SDL_FreeSurface(image);
	return true;
}


Node* Character::getNodeForPosition(const Vec3& position) const
{
	int gridWidth = 25, gridHeight = 25;
	int gridSize = gridHeight * gridWidth;
	int x = static_cast<int>(position.x / gridSize);  // Convert position to grid coordinates
	int y = static_cast<int>(position.y / gridSize);

	long nodeLabel = y * gridWidth + x;



	// Check if the position is within bounds of the grid
	if (x < 0 || x > gridWidth || y < 0 || y > gridHeight) {
		std::cerr << "Error: out of bounds error." << std::endl;
		return nullptr;  // Return nullptr if out of bounds
	}
	if(scene->getGraph()->getNode(nodeLabel))
	return scene->getGraph()->getNode(nodeLabel);
	else {
		std::cerr << "Error: Invalid node error." << std::endl;
		return nullptr;
	}
}


void Character::Update(float deltaTime)
{
	// If the path is empty, calculate a new path to the player
	if (path.empty()) {  // If no path, find the path
		Node* startNode = getNodeForPosition(body->getPos());
		Node* goalNode = getNodeForPosition(scene->game->getPlayer()->getPos());

		if (!startNode) {
			std::cerr << "Error: Invalid start node." << std::endl;
			return;
		}
		else if (!goalNode) 
		{
			std::cerr << "Error: Invalid goal node." << std::endl;
			return;
		}


		// Optionally visualize the path for debugging
		 scene->renderPath(path);
		 
	}

	// If there are nodes in the path, steer towards the next node
	if (!path.empty()) {
		Node* nextNode = path.front();  // Get the next node in the path
		MATH::Vec2 nextNodePos = nextNode->NodeToGrid(nextNode->getLabel());  // Get the position of that node

		// Steering behavior: steer towards the next node in the path
		SteeringBehaviour* steering_algorithm = new Seek(body, scene->game->getPlayer());
		SteeringOutput* steering = steering_algorithm->getSteering();

		// Apply the steering to the character's body
		body->Update(deltaTime, steering);
		/*
		// Check if the character has reached the current node, if so, remove it from the path
		if (Vec2::distance(body->getPos().xy(), nextNodePos) < 0.2f) {  // Use a threshold to check if it's close enough
			path.erase(path.begin());  // Remove the node from the front of the path
		}
		*/
		// Clean up the steering algorithm
		delete steering_algorithm;
	}
}



void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale) const
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}
