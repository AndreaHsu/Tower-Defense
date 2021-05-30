#include <string>

#include "StrongEnemy.hpp"

StrongEnemy::StrongEnemy(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
