#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	myNPC = NULL;
	blinky = nullptr;
	currentTargetIndex = 0; // Track path index for NPC
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	//Tile codes
	tileWidth = 3.0f;
	tileHeight = 2.0f;
	//creating a Vec3 tile position using float values:
	float x = 5.0f;
	float y = 3.0f; 
	Vec3 tilePos(x, y, 0.0f);

	// Set up myNPC kinematic character
	Vec3 position = Vec3(5.0f, 3.0f, 0.0f);
	float orientation = 0.0f;
	float maxSpeed = 5.0f;
	float maxRotation = 1.0f;
	myNPC = new StaticBody(
		position,
		orientation,
		maxSpeed,
		maxRotation
	);

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	//error checking
	if (image == nullptr)
	{
		std::cerr << "Can't open clyde image\n";
		return false;
	}
	if (texture == nullptr)
	{
		std::cerr << "Can't open clyde texture\n";
		return false;
	}
	else
	{
		myNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png"))
	{
		return false;
	}

	// end of character set ups

	//Graph and Nodes
	// Create the graph and nodes
	graph = new Graph();
	std::vector<Node*> nodes;
	//create 10 nodes
	for (int i = 0; i < 10; ++i) {
		nodes.push_back(new Node(i));
	}
	graph->OnCreate(nodes);

	// Create connections between the nodes
	// Example: connecting node 0 to node 1, node 1 to node 2, etc.
	//graph->addWeightedConnection(nodes[0], nodes[1], 1);
	//graph->addWeightedConnection(nodes[1], nodes[2], 1);


	// Define the start and goal nodes
	Node* startNode = blinky->getNodeForPosition(myNPC->getPos());
	Node* goalNode = blinky->getNodeForPosition(game->getPlayer()->getPos());

	// Find the path
	 path = graph->findPath(startNode, goalNode);
	return !path.empty();
}
void renderPath(const std::vector<Node*>& path) {

}
void Scene1::OnDestroy()
{
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	KinematicSteeringOutput* steering;

	//create seek algorithm
	KinematicSeek* steeringAlgorithm;
	steeringAlgorithm = new KinematicSeek(myNPC, game->getPlayer());
	steering = steeringAlgorithm->getSteering();

	//myNPC->Update(deltaTime, steering);

	   // If there is a path to follow, update NPC movement along it
	if (!path.empty()) {
		Node* currentNode = path[currentTargetIndex];
		Vec3 targetPos(currentNode->x * tileWidth, currentNode->y * tileHeight, 0.0f);

		// Move myNPC towards the target node
		myNPC->MoveTowards(targetPos, deltaTime);

		// Check if NPC has reached the current target node
		if (myNPC->HasReached(targetPos, 1.0f)) {
			currentTargetIndex++; // Move to the next node in the path
		}

		// If we reach the end of the path, reset or stop
		if (currentTargetIndex >= path.size()) {
			currentTargetIndex = 0; // Optionally reset or stop NPC movement
		}
	}

	blinky->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);

	// memory management
	if (steeringAlgorithm)
	{
		delete steeringAlgorithm;
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	
	// render any npc's
	blinky->render(0.05f);

	// render the player
	game->RenderPlayer(0.04f);
	/*
	// Optionally render path (for debugging purposes)
	for (size_t i = 0; i < path.size() - 1; ++i) {
		Node* startNode = path[i+1];
		Node* endNode = path[i + 2];
		// Render a line from startNode to endNode
		SDL_RenderDrawLine(renderer, startNode->x * tileWidth, startNode->y * tileHeight,
			endNode->x * tileWidth, endNode->y * tileHeight);
	}
	*/


	// Optionally render path (for debugging purposes)
	for (size_t i = 0; i < path.size() - 1; ++i) {
		Node* startNode = path[i];
		Node* endNode = path[i + 1];
		// Render a line from startNode to endNode
		SDL_RenderDrawLine(renderer, startNode->x * tileWidth, startNode->y * tileHeight,
			endNode->x * tileWidth, endNode->y * tileHeight);
	}


	SDL_RenderPresent(renderer);
}

void Scene1::renderMyNPC()
{
	SDL_Rect rect;
	Vec3 screenCoords;
	int w, h;

	// convert coords
	screenCoords = projectionMatrix * myNPC->getPos();
	float scale = 0.15f;

	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);

	rect.w = static_cast<int>(w * scale);
	rect.h = static_cast<int>(h * scale);
	rect.x = static_cast<int>(screenCoords.x - 0.5 * rect.w);
	rect.y = static_cast<int>(screenCoords.y - 0.5 * rect.h);

	float orientation = myNPC->getOrientation();
	double degrees = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &rect, degrees, nullptr, SDL_FLIP_NONE);

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
