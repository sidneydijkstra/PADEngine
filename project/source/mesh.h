
#ifndef MESH_CLASS
#define MESH_CLASS

#include "resourcemanager.h"
#include "meshbuffer.h"

class Mesh {
	public:
		Mesh();
		~Mesh();

		void loadShape(MeshType _type);
		MeshBuffer* getBuffer();
		MeshType getType();

	private:
		MeshBuffer* _meshBuffer;
};
#endif