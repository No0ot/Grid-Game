#include "Engine.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <random>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
#define SIZE 10



class Job
{
public:

	std::string name;
	int attack;
	int health;
	SDL_Texture* m_texture;
	int initmod;
	int jobid;

	Job()
	{
		name = " ";
		attack = 0;
		health = 0;

	}
	Job(int id, std::string n, int a, int h, int init)
	{
		jobid = id;
		name = n;
		attack = a;
		health = h;
		initmod = init;
	}
	std::string getName() { return name; }
	int getAttack() { return attack; }
	int getHealth() { return health; }
	int getJobid() { return jobid; }
	int getInitmod() { return initmod; }
};

Job soldier = { 1,"Soldier" ,15, 100, 1 };
Job squire = { 2,"Squire",10, 150, 0 };
Job scout = { 3, "Scout",15,100, 2 };
Job disciple = { 4,"Disciple", 10, 125, 1 };
Job apprentice = { 5,"Apprentice", 30, 75, 0 };

class Character
{
public:
	std::string name;

	Hex* hexptr;
	Job job;
	SDL_Rect m_src, m_dst;
	bool hostile;
	int initiative;

	Character()
	{
		name = " ";
		m_src = { 0,0,0,0 };
		m_dst = { 0,0,0,0 };
	}
	Character(std::string n, Job c, Hex h, bool b)
	{
		hostile = b;
		hexptr = &h;
		name = n;
		job = c;
		initiative = job.getInitmod() + rand() % 10;
		m_src = { 0,0,32,32 };
		m_dst = { h.hx_dst.x + 32, h.hx_dst.y, m_src.w * 2, m_src.h * 2 };
	}
	std::string getName() { return name; }
	Hex getPos() { return *hexptr; }
	Job getJob() { return job; }
	void setPos(Hex& p) {
		hexptr->setOccupied(false);		// sets hex to unoccupied
		hexptr = &p;		// set address of new hex 
		m_dst = { p.hx_dst.x + 32, p.hx_dst.y, m_src.w * 2, m_src.h * 2 }; // moves character to new hex
		p.setOccupied(true);		// sets new hex to occupied
	}
	int getIn() { return initiative; }
};

Character playerchar[5];
Character initorder[5];


Engine::Engine() :g_bRunning(false) //Class initializer list way.
{
	std::cout << "Constructing engine class..." << std::endl;
}

Engine::~Engine()
{}

void initiative() {

	Character temp;
	for (int i = 0; i < 5; i++) {
		initorder[i] = playerchar[i];
	}

	for (int in = 0; in < 4; in++) {
		if (initorder[in + 1].getIn() > initorder[in].getIn()) {
			temp = initorder[in];
			initorder[in] = initorder[in + 1];
			initorder[in + 1] = temp;
		}
	}
	for (int i = 0; i < 5; i++) {
		std::cout << initorder[i].getName() << ": " << initorder[i].getIn() << std::endl;
	}

}

void charturn(int i, int j) {
	static int turn = 0;
	if (turn < 5) {
		playerchar[turn].setPos(g_hex[i][j]);
		turn++;
	}
	else
		turn = 0;
}

void gridcreation() {
	// GRID CREATION
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			if (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 11 || j == 13 || j == 15)
				g_hex[i][j] = { 20 + (j * 95) , (50 + (i * 64)) - 15 };

			else if (j == 0 || j == 2 || j == 4 || j == 6 || j == 8 || j == 10 || j == 12 || j == 14)
				g_hex[i][j] = { 20 + (j * 95) , (50 + (i * 64)) + 15 };

		}
	}

	g_hex[0][0].m_active = true;
}
void partyLoadout() {
	playerchar[0] = { "Joe", squire, g_hex[3][4],false };
	playerchar[1] = { "Danny", soldier, g_hex[4][6],true };
	playerchar[2] = { "Bob", scout, g_hex[6][0],false };
	playerchar[3] = { "Cid", disciple, g_hex[2][8],true };
	playerchar[4] = { "Will", apprentice, g_hex[7][6],false };
}

void battle() {

	initiative();

}

bool Engine::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	std::cout << "Initializing game." << std::endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (g_pWindow != nullptr) // Window init success.
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr) // Renderer init success.
			{
				if (IMG_Init(IMG_INIT_PNG))
				{
					g_pTexture[0] = IMG_LoadTexture(g_pRenderer, "Hex.png");
					g_pTexture[1] = IMG_LoadTexture(g_pRenderer, "selector.png");
					soldier.m_texture = IMG_LoadTexture(g_pRenderer, "soldier.png");
					squire.m_texture = IMG_LoadTexture(g_pRenderer, "squire.png");
					scout.m_texture = IMG_LoadTexture(g_pRenderer, "scout.png");
					disciple.m_texture = IMG_LoadTexture(g_pRenderer, "disciple.png");
					apprentice.m_texture = IMG_LoadTexture(g_pRenderer, "apprentice.png");
				}

				else return false; // Renderer init fail.
			}
			else return false; // Window init fail.
		}
		else return false; // SDL init fail.


	}
	else return false;
	g_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	g_iKeystates = SDL_GetKeyboardState(nullptr);

	gridcreation();
	partyLoadout();
	battle();

	g_bRunning = true; // Everything is okay, start the engine.
	std::cout << "Success!" << std::endl;
	return true;
}


void Engine::wake() {
	g_start = SDL_GetTicks();
}

void Engine::sleep()
{
	g_end = SDL_GetTicks();
	g_delta = g_end - g_start;
	if (g_delta < g_fps) // Engine has to sleep.
		SDL_Delay(g_fps - g_delta);
}
bool rup = false, lup = false;
bool select = true;

void Engine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			g_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_bRunning = false;
			else if (event.key.keysym.sym == SDLK_DOWN) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++)
					{
						if (g_hex[i][j].getActive() == true)
						{

							if (i < 9) {
								std::cout << i + 1 << j << std::endl;
								g_hex[i + 1][j].setActive(true);
								g_hex[i][j].setActive(false);

							}
							rup = true;
							break;
						}

					}
					if (rup)
						break;
				}
				rup = false;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++)
					{
						if (g_hex[i][j].getActive() == true)
						{

							if (i > 0) {
								std::cout << i - 1 << j << std::endl;
								g_hex[i - 1][j].setActive(true);
								g_hex[i][j].setActive(false);

							}

						}
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++)
					{
						if (g_hex[i][j].getActive() == true)
						{
							if (j < 9) {
								std::cout << i << j + 1 << std::endl;
								g_hex[i][j + 1].setActive(true);
								g_hex[i][j].setActive(false);

							}
							lup = true;
							break;
						}
					}
					if (lup)
						break;
				}
				lup = false;
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++)
					{
						if (g_hex[i][j].getActive() == true)
						{
							if (j > 0) {
								std::cout << i << j - 1 << std::endl;
								g_hex[i][j - 1].setActive(true);
								g_hex[i][j].setActive(false);

							}

						}
					}
				}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++)
					{
						if (g_hex[i][j].getActive() == true && g_hex[i][j].getOccupied() == false) {

							charturn(i, j);

						}
					}

				}
			}
			break;

		}
	}
}

// Keyboard utility function.
bool Engine::keyDown(SDL_Scancode c)
{
	if (g_iKeystates != nullptr)
	{
		if (g_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::update()
{

}

void Engine::render()
{
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer); // Clear the screen with the draw color.
	// Render stuff.
	//SDL_RenderCopyEx(g_pRenderer,knight.m_text, &g_selector.hx_src, &g_selector.hx_dst, 0, nullptr, SDL_FLIP_NONE);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (g_hex[i][j].m_active == false)
				SDL_RenderCopyEx(g_pRenderer, g_pTexture[0], &g_hex[i][j].hx_src, &g_hex[i][j].hx_dst, 0, nullptr, SDL_FLIP_NONE);
			else if (g_hex[i][j].m_active == true)
				SDL_RenderCopyEx(g_pRenderer, g_pTexture[1], &g_hex[i][j].hx_src, &g_hex[i][j].hx_dst, 0, nullptr, SDL_FLIP_NONE);
		}
	}
	for (int i = 0; i < 5; i++) {
		if (playerchar[i].job.getJobid() == 1) {
			SDL_RenderCopyEx(g_pRenderer, soldier.m_texture, &playerchar[i].m_src, &playerchar[i].m_dst, 0, nullptr, SDL_FLIP_NONE);
		}
		else if (playerchar[i].job.getJobid() == 2) {
			SDL_RenderCopyEx(g_pRenderer, squire.m_texture, &playerchar[i].m_src, &playerchar[i].m_dst, 0, nullptr, SDL_FLIP_NONE);
		}
		else if (playerchar[i].job.getJobid() == 3) {
			SDL_RenderCopyEx(g_pRenderer, scout.m_texture, &playerchar[i].m_src, &playerchar[i].m_dst, 0, nullptr, SDL_FLIP_NONE);
		}
		else if (playerchar[i].job.getJobid() == 4) {
			SDL_RenderCopyEx(g_pRenderer, disciple.m_texture, &playerchar[i].m_src, &playerchar[i].m_dst, 0, nullptr, SDL_FLIP_NONE);
		}
		else if (playerchar[i].job.getJobid() == 5) {
			SDL_RenderCopyEx(g_pRenderer, apprentice.m_texture, &playerchar[i].m_src, &playerchar[i].m_dst, 0, nullptr, SDL_FLIP_NONE);
		}
	}
	// Draw anew.

	SDL_RenderPresent(g_pRenderer);
}

void Engine::clean()
{
	std::cout << "Cleaning game." << std::endl;
	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(g_pTexture[i]);
	}

	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

// Main function.
int Engine::run()
{

	if (init("Grid Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (g_bRunning)
	{
		srand((unsigned)time(NULL));
		wake();
		handleEvents();
		update();
		render();
		if (g_bRunning)
			sleep();
	}
	clean();
	return 0;
}