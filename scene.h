#ifndef SCENE_H
#define SCENE_H

namespace RayTracer {

class Scene {
	private:
		std::vector<std::shared_ptr<Camera>> cameras;
		std::vector<std::shared_ptr<Entity>> ents;
		KDNode kdnode;

		void recalculateKDtree();

	public:
		Scene();

		void addCam(std::shared_ptr<Camera> cam);
		void addEnt(std::shared_ptr<Entity> ent);

		std::vector<std::shared_ptr<Camera>> getCams() const;
		std::vector<std::shared_ptr<Entity>> getEnts() const;

		void captureImages();
		std::vector<std::shared_ptr<const ImageData>> getCapturedImages();

		std::experimental::optional

		std::vector<std::reference_wrapper<ImageData>> getCapturedImages();
		std::experimental::optional<IntersectData> getIntersectData(const Ray& _r);
};

}

#endif
