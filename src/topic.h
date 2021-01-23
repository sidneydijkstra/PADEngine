#ifndef PAD_ENGINE_UTILITY_TOPIC_HEADER
#define PAD_ENGINE_UTILITY_TOPIC_HEADER

#include <queue>

namespace pad {

template<typename Publisher_T, typename Content_T>
class Topic final {

	friend class NotifyFunctor;

public:

	class NotifyFunctor final {

		friend class Publisher_T;

	private:

		const Topic& _topic;

		NotifyFunctor(const Topic&) noexcept = default;

		NotifyFunctor(const NotifyFunctor&) = delete;
		NotifyFunctor(NotifyFunctor&&) = delete;

		~NotifyFunctor() noexcept = default;

		void operator()(Content_T content) noexcept;

	};

	class Subscription final {

		friend class Topic;

	public:

		bool hasContent() const noexcept;
		Content_T getNextContent() noexcept;

	private:

		std::queue<Content_T> content;

		Subscription();

	};

	NotifyFunctor notify;

private:

	std::vector<Subscription> subscribers;

};

}

#endif