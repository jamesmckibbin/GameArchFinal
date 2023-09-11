#pragma once
#include "Enemy.h"
#include <vector>

const int NUM_UNITS = 100;

class EnemyManager : public Trackable
{
public:
	EnemyManager() {}
	~EnemyManager() {
		cleanup();
	}
	void init();
	void cleanup();

	void createUnit(const Vector2D& pos);
	void deleteUnit(int unitToDelete);
	bool checkAtLocation(const Vector2D& loc, int radius);
	void deleteAtLocation(const Vector2D& loc, int radius);
	void deleteAtLocation(const Vector2D& loc, int radius, bool multipleUnits);
	void clearUnits();
	void updateUnits(float deltaTime);
	void drawUnits();
	void pauseUnits();
	void unPauseUnits(); 
	void updateVelocity(Vector2D target);
	int getActiveEnemyUnits() { return mActiveEnemyUnits; }
	Vector2D randomSpawnLocation();

	Enemy* getUnit(int index) { return &mUnits[index]; }

	bool unitExists(int unitToFind);
private:
	Enemy mUnits[NUM_UNITS];
	std::vector<int> mIndexes;

	bool mShouldAnimate = true;
	int mActiveEnemyUnits = 0;
};