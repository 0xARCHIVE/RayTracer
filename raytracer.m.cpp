#include "scene.h"

#include <iostream>

int main() {
	RayTracer::Scene scene("config.cfg","scene.dat");
	std::cout << "test" << std::endl;
	return 0;
}
