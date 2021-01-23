#ifndef PAD_ENGINE_PHYSICS_COLLIDER_HEADER
#define PAD_ENGINE_PHYSICS_COLLIDER_HEADER

#include <cassert>

namespace pad {

class BoxCollider;
class SphereCollider;
class CapsuleCollider;
class MeshCollider;

class Collider {

public:

	virtual bool collidesWith(const Collider& other) const noexcept = 0;

	virtual bool collidesWith(const BoxCollider& other) const noexcept = 0;
	virtual bool collidesWith(const SphereCollider& other) const noexcept = 0;
	virtual bool collidesWith(const CapsuleCollider& other) const noexcept = 0;
	virtual bool collidesWith(const MeshCollider& other) const noexcept = 0;
	
	virtual ~Collider() noexcept = 0;

protected:

#ifndef NDEBUG
	static constexpr auto debugging_enabled = true;
#else
	static constexpr auto debugging_enabled = false;
#endif

};

}

using namespace pad;

#endif
