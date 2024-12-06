#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 3.0f;
		float maxAcceleration = 5.0f;
		float maxRotation = 2.5f;
		float maxAngular = 12.0f;
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




Node* Character::getPlayerNode() {

	return scene->getGraph()->getNode((scene->game->getPlayer()->getPos().x * 25) + scene->game->getPlayer()->getPos().y);
}

Node* Character::getNode() {

	return scene->getGraph()->getNode((body->getPos().x * 25) + (body->getPos().y));
}

void Character::setPath(vector<Node*> path_temp)
{
	path.clear();
	if (!path_temp.empty()) {
		path = path_temp;
	}

}
void Character::Update(float deltaTime) {
	if (path.empty()) {
		std::cout << "Path is empty" << std::endl;
		return;
	}

	Node* currentTarget = path[currentTargetIndex];
	Vec3 targetPos = currentTarget->getPos3();
	Vec3 direction = targetPos - body->getPos();


	if (calculateDistance(direction) < 0.1f) {
		currentTargetIndex++;
		if (currentTargetIndex >= path.size()) {
			currentTargetIndex = 0;  // Path completed
		}
	}

	SteeringBehaviour* steering_algorithm = new Seek(body, scene->game->getPlayer());
	SteeringOutput* steering = steering_algorithm->getSteering();

	body->Update(deltaTime, steering);

	delete steering_algorithm;
	//delete steering;
}
float Character::calculateDistance(const Vec3& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
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
