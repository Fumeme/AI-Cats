#include "Scene1.h"


void Scene1::CreateTiles()
{
	//singleTile = new Tile(Vec3(15.0f, 7.7f, 0.0f), 3.0f, 3.0f, this);
	tileHeight = 1.5f;
	tileWidth = 1.5f;

	//resize tiles
	int cols = ceil((xAxis - 0.5 * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5 * tileHeight) / tileHeight);

	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	sceneNodes.resize(cols * rows);

	Node* n;
	int label = 0;
	Tile* t;
	int i, j;

	i = 0;
	j = 0;


	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		//do things as y increases
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			//do things as x increases
			//create tile
			n = new Node(label);
			sceneNodes[label] = n;
			Vec3 tilePos = Vec3(x, y, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			//i or j?
			j++;
			label++;

		}
		j = 0;
		i++;
	}

}

Node* Scene1::getNodeAtPosition(int mouseX, int mouseY) {
	// Convert mouse coordinates to world coordinates
	float worldX = (mouseX / (float)w) * xAxis;
	float worldY = yAxis - (mouseY / (float)h) * yAxis;

	// Find the corresponding tile
	int col = worldX / tileWidth;
	int row = worldY / tileHeight;

	if (col >= 0 && col < tiles[0].size() && row >= 0 && row < tiles.size()) {
		return tiles[row][col]->getNode();
	}

	return nullptr;
}

//Tile* Scene1::getTileAtPosition(float x, float y) {
//
//	int col = x / tileWidth;
//	int row = y / tileHeight;
//
//	if (col >= 0 && col < tiles[0].size() && row < tiles.size()) {
//		return tiles[row][col];
//	}
//
//	return nullptr;
//}


void Scene1::calculateConnectionsWeights()
{
	// I'm smart enough to only call this
	// after having properly created the tiles matrix
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//tiles[i][j]->getNode();
			//
			//                 i+1, j
			//   i,j-1            i,j                i,j+1
			//                 i-1, j
			Tile* fromTile = tiles[i][j];
			Node* from = fromTile->getNode();

			// left
			if (j >= 1 && tiles[i][j - 1]->isPassable() == true)
			{
				Node* to = tiles[i][j - 1]->getNode();
				graph->addWeightedConnection(from, to, tileWidth);
			}

			// right
			if ((j + 1) < cols && tiles[i][j + 1]->isPassable() == true)
			{
				Node* to = tiles[i][j + 1]->getNode();
				graph->addWeightedConnection(from, to, tileWidth);
			}

			//above
			if ((i + 1) < rows && tiles[i + 1][j]->isPassable() == true)
			{
				Node* to = tiles[i + 1][j]->getNode();
				graph->addWeightedConnection(from, to, tileHeight);
			}

			//below
			if ((i - 1) >= 0 && tiles[i - 1][j]->isPassable() == true)
			{
				Node* to = tiles[i - 1][j]->getNode();
				graph->addWeightedConnection(from, to, tileHeight);
			}

		}


	}

}

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	tileHeight = 0.0f;
	tileWidth = 0.0f;
	selectedNode = nullptr;


	// create a NPC
	blinky = nullptr;
	
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	//int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	CreateTiles();

	//background = IMG_Load("Map.png");
	backgroundtexture = SDL_CreateTextureFromSurface(renderer, background);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;



	image = IMG_Load("Pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setPos(Vec3(2.5f, 0.8f, 0.0f));
	game->getPlayer()->setTexture(texture);



	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png"))
	{
		return false;
	}

	
	// end of character set ups

	// create a graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		//TODO error message
		return false;
	}

	calculateConnectionsWeights();

	std::vector<Node*> path = graph->findPath(
		sceneNodes[0],
		sceneNodes[15]
	);




	return true;
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
	blinky->Update(deltaTime);
	
	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	//do not deprioritize these
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//move this above tile rendering to show map after grid & vice versa
	SDL_RenderCopy(renderer, backgroundtexture, NULL, NULL);

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			Tile* tile = tiles[i][j];
			//if (tile->getNode() == selectedNode) {
			//	// Change color for the selected node
			//	tile->setColor(255, 0, 0, 255); // Red color
			//}
			//else {
			//	tile->setColor(17, 178, 178, 255); // Default color
			//}


			tile->Render();


		}

	}



	// render any npc's
	blinky->render(0.10f);
	//cop->render(0.10f);

	// render the player
	game->RenderPlayer(0.10f);



	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{

	//if mouse clicked, record position on screen and relay it to terminal
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// get mouse button clicks location
		int x = event.button.x, y = event.button.y;
		SDL_GetMouseState(&x, &y);
		printf("Clicked at: %i x, %i x\n", x, y);


		//Gets the node at the position of the mouse click
		Node* selectedNode = getNodeAtPosition(x, y);
		if (selectedNode)
		{

			printf("Selected Node: %d\n", selectedNode->getLabel());
			// You can now use the selected node for further processing



			for (int i = 0; i < tiles.size(); i++)
			{
				for (int j = 0; j < tiles[i].size(); j++)
				{

					Tile* tile = tiles[i][j];

					if (tile->getNode() == selectedNode) {
						tile->setPassable(false);
						// Change color for the selected node
						tile->setColor(255, 0, 0, 255); // Red color
						//SDL_RenderPresent(renderer);
						calculateConnectionsWeights();
						graph->findPath(
							sceneNodes[0],
							sceneNodes[15]
						);

					}
					else {

					}
				}


			}




		}



		SDL_RenderPresent(renderer);
		// send events to npc's as neededD

	}







	// send events to player as needed
	game->getPlayer()->HandleEvents(event);


}
