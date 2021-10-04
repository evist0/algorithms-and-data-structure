#ifndef ADS_CONTAINER_HPP
#define ADS_CONTAINER_HPP

#include <cstdlib>
#include <cassert>

template<class T>
class container {
		private:
				std::size_t head_;
				std::size_t free_;

				T* data_;
				std::size_t* next_;

				std::size_t capacity_;
				std::size_t size_;

		public:
				class iterator {
						public:
								using iterator_category = std::forward_iterator_tag;
								using value_type = T;
								using difference_type = std::ptrdiff_t;
								using pointer = T*;
								using reference = T&;

								iterator(container<T>* container, std::size_t current)
																:container_(container), current_(current) {
								}

								T& operator*() {
										if (current_ == -1) {
												throw std::out_of_range("iterator out of bounds");
										}

										return container_->data_[current_];
								}

								iterator& operator++() {
										if (current_ == -1) {
												return *this;
										}

										current_ = container_->next_[current_];
										return *this;
								}

								iterator& next() {
										return ++(*this);
								}

								bool operator==(const iterator& rhs) const {
										assert(container_ == rhs.container_);

										return current_ == rhs.current_;
								}

								bool operator!=(const iterator& rhs) const {
										assert(container_ == rhs.container_);

										return current_ != rhs.current_;
								}

						private:
								friend container;

								container<T>* container_;
								std::size_t current_;
				};

				explicit container(std::size_t capacity = 4)
												:capacity_(capacity), size_(0) {
						head_ = -1;
						free_ = 0;

						data_ = new T[capacity_];
						next_ = new std::size_t[capacity_];

						for (std::size_t i = 0; i < capacity_; i++) {
								next_[i] = i + 1;
						}
				}

				container(const container& other) {
						if (*this == other) {
								return *this;
						}

						T* new_data = nullptr;
						std::size_t* new_next = nullptr;
						auto new_capacity = other.capacity_;

						try {
								new_data = new T[new_capacity];
								new_next = new std::size_t[new_capacity];

								for (std::size_t i = 0; i < new_capacity; i++) {
										new_data[i] = other.data_[i];
										new_next[i] = other.next_[i];
								}
						}
						catch (...) {
								delete[] new_data;
								delete[] new_next;
								throw;
						}

						delete[] data_;
						delete[] next_;

						head_ = other.head_;
						free_ = other.free_;

						data_ = new_data;
						next_ = new_next;

						capacity_ = new_capacity;
						size_ = other.size_;
				}

				[[nodiscard]] std::size_t size() const {
						return size_;
				}

				iterator begin() {
						if (size_ == 0) {
								return end();
						}

						return { this, head_ };
				}

				iterator end() {
						return { this, free_ };
				}

				void insert(std::size_t where, const T& element) {
						if (where > size_ || size_ + 1 > capacity_) {
								throw std::out_of_range("position greater than size");
						}

						std::size_t slot = free_;

						data_[slot] = element;

						free_ = next_[free_];

						std::size_t* next_previous = [&]() {
								std::size_t* p = &head_;

								for (std::size_t i = 0; i < where; ++i) {
										p = &next_[*p];
								}

								return p;
						}();

						next_[slot] = *next_previous;
						*next_previous = slot;

						++size_;
				}

				void push_front(const T& element) {
						insert(0, element);
				}

				void push_back(const T& element) {
						insert(size_, element);
				}

				void remove(std::size_t where) {
						if (where >= size_) {
								throw std::out_of_range("position greater than size");
						}

						auto remove_at = begin();
						std::advance(remove_at, where);

						std::size_t* next_previous = &head_;
						for (std::size_t i = 0; i < where; i++) {
								next_previous = &next_[*next_previous];
						}

						*next_previous = next_[remove_at.current_];

						next_[remove_at.current_] = free_;
						free_ = remove_at.current_;

						--size_;
				}

				bool remove_value(const T& value) {
						auto position = find(value);

						if (position >= size_) {
								return false;
						}

						remove(position);
						return true;
				}

				T& operator[](std::size_t where) {
						if (where >= size_) {
								throw std::out_of_range("position greater than size");
						}

						auto iter = begin();
						std::advance(iter, where);

						return *iter;
				}

				std::size_t find(const T& value) {
						std::size_t index = 0;
						std::size_t position = head_;

						while (position != -1) {
								if (data_[position] == value) {
										break;
								}

								position = next_[position];
								++index;
						}

						return index == size_ ? -1 : index;
				}

				bool contains(const T& value) {
						return find(value) < size_;
				}

				void erase() {
						for (std::size_t i = 0; i < capacity_; i++) {
								next_[i] = i + 1;
						}

						head_ = -1;
						free_ = 0;
						size_ = 0;
				}

				bool empty() {
						return size_ == 0;
				}

				~container() {
						delete[] data_;
						delete[] next_;
				}
};

#endif //ADS_CONTAINER_HPP
