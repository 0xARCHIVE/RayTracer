#ifndef FILE_H
#define FILE_H

#include <string>

namespace RayTracer {

class ImageData;
class File {
	protected:
		std::string filepath;
	public:
		File(const std::string& _filepath);
		void writeImageData(const ImageData& _data);
};

}

#endif
