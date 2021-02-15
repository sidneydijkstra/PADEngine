
#ifndef SHADERDEMO_CANVAS_CLASS
#define SHADERDEMO_CANVAS_CLASS

#include "entity.h"
#include "input.h"

using namespace pad;

struct DataBuffer {
	glm::dvec2 center;
	double zoom;
	int maxIts;
};

class Canvas : public Entity {
	public:
		Canvas();
		~Canvas();

		void update() override;
		void updateDescriptors(int _index) override;

	private:
		UniformBuffer<DataBuffer>* _buffer;
		glm::dvec2 center;
		double zoom;
		glm::vec2 lastMouse;
		int maxIts;

		double map(double value, double min1, double max1, double min2, double max2);
};
#endif