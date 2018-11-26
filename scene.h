#ifndef SCENE_H
#define SCENE_H

#include "kdnode.h"

#include <memory>
#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Camera;
class Entity;
class Ray;
class ImageData;
class IntersectData;

class Scene {
	private:
		std::vector<std::shared_ptr<Camera>> cameras;
		std::vector<std::shared_ptr<Entity>> ents;
		std::shared_ptr<KDNode> kdnode;

	public:
		Scene();

		void addCam(std::shared_ptr<Camera> cam);
		void addEnt(std::shared_ptr<Entity> ent);

		std::vector<std::shared_ptr<Camera>> getCams() const;
		std::vector<std::shared_ptr<Entity>> getEnts() const;

		void captureImages();
		std::vector<ImageData> getCapturedImages();

		std::experimental::optional<IntersectData> intersectRay(const Ray &r) const;
		void recalculateKDtree();
};

}

#endif
