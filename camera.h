#ifndef CAMERA_H
#define CAMERA_H

namespace RayTracer {

class Camera {
	private:
		CameraSensor sensor;
		ImageData capturedImage;

		std::clock_t startTime;
		double runDuration;

	public:
		Camera(const CameraSensor &sensor);

		void setSensor(const CameraSensor &sensor);
		const CameraSensor& getSensor() const;

		void captureImage();
		const ImageData& getCapturedImage() const;

		double getRunDuration() const;
};

}

#endif
