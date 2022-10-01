#pragma once

#include <vector>

using std::vector;

class Player;

class GameObject								//12400 bytes (7 bytes available for packing in gcc)
{
public:
    GameObject(double x, double y);

    virtual void update(double dt);
    virtual void render(SDL_Renderer* renderer) const;
    void testCollision(Player& obj);

    double getW() const;						//8 bytes
    double getH() const;						//8 bytes
    bool shouldDelete() const;					//1 byte

    double x;									//8 bytes
    double bloop[256];							//8 bytes * 256 = 2048 bytes
    double y;									//8 bytes
    double blaap[256];							//8 bytes * 256 = 2048 bytes
    double w, h;								//8 bytes
protected:
    bool isColliding(Player& obj);				//1 byte
    virtual void collide(Player& obj) = 0;		//8 bytes pure virtual

    double vx;									//8 bytes
    double bleep[256];							//8 bytes * 256 = 2048
    double vy;									//8 bytes
    double bliip[256];							//8 bytes * 256 = 2048
    double ax;									//8 bytes
    double bluup[256];							//8 bytes * 256 = 2048
    double ay;									//8 bytes
    double blyyp[256];							//8 bytes * 256 = 2048

    double color_r, color_g, color_b, color_a;	//8 bytes
    bool deleteMe;								//1 byte

    vector<double> playerCoords;
    vector<double> myCoords;
};
