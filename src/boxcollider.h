#ifndef PAD_ENGINE_PHYSICS_BOXCOLLIDER_HEADER
#define PAD_ENGINE_PHYSICS_BOXCOLLIDER_HEADER

#include "collider.h"

namespace pad {

class BoxCollider final : public Collider {

public:

	bool collidesWith(const Collider& other) const noexcept override {
		if constexpr (debugging_enabled) {
			static const Collider* lastCollider = nullptr;
			assert((lastCollider==&other) && "An overload of 'collidesWith' for the used Collider types does not currently exist.");
			lastCollider = &other;
		}

		return other.collidesWith(*this);
	}

	virtual bool collidesWith(const BoxCollider& other) const noexcept = 0 {
		return true;
	}

	virtual bool collidesWith(const SphereCollider& other) const noexcept = 0 {
		return true;
	}

	virtual bool collidesWith(const CapsuleCollider& other) const noexcept = 0 {
		return true;
	}

	virtual bool collidesWith(const MeshCollider& other) const noexcept = 0 {
		return true;
	}

};

}

using namespace pad;

#endif
