//
// Created by Danil Tankov on 08.09.2021.
//

#ifndef ADS_CONTAINER_HPP
#define ADS_CONTAINER_HPP

#include <cstdlib>
#include <container_iterator.hpp>

template<typename T> class container {
				class container_iterator {
						public:
								container_iterator(const container<T>& container, std::size_t index)
																:container_(container), index_(index) {
								};

								container_iterator(const container_iterator&) {

								};

								container_iterator& operator=(const container_iterator&) noexcept {

								};

								T& operator*() {

								};

								container_iterator& operator++() {

								};

								container_iterator& operator--() {

								};

								bool operator==(const container_iterator&) {

								};

								bool operator!=(const container_iterator&) {

								};
						private:
								std::size_t index_;
								const container& container_;
				};

		public:
				container(const std::size_t&) {

				};

				container(const container<T>&) {

				};

				container<T>& operator=(const container<T>&) noexcept {

				};

				T& operator[](const std::size_t&) {

				};

				const T& operator[](const std::size_t&) const {

				}

				container_iterator begin() {

				};

				container_iterator end() {

				};

				std::size_t size() {

				};

				std::size_t capacity() {

				};

				bool empty() {

				};

				bool contains(const T&) {

				};

				std::size_t search_position(const T&) {

				};

				bool push_back(const T&) noexcept {

				};

				bool insert_at(const T&, std::size_t&) noexcept {

				};

				bool remove(const T&) noexcept {

				};

				bool remove_at(const std::size_t&) noexcept {

				};

				bool erase() {

				};

				~container() {

				};
};

#endif //ADS_CONTAINER_HPP
