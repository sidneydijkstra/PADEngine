
#ifndef MESH_CLASS
#define MESH_CLASS

#include "resourcemanager.h"
#include "meshbuffer.h"

class Mesh {
	public:
		Mesh();
		~Mesh();

		void loadShape(MeshType _type);
		void loadObject(const char* _path);
		MeshBuffer* getBuffer();
		MeshType getType();

	private:
		MeshBuffer* _meshBuffer;
};
#endif