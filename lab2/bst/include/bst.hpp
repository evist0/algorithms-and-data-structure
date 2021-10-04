#ifndef ADS_CONTAINER_HPP
#define ADS_CONTAINER_HPP

#include <cstdlib>
#include <cassert>
#include <optional>

template<class Tk, class Td>
class bst {
		public:
				class iterator {
						public:
								Td& operator*() {
								}

								iterator& operator++() {
								}

								iterator& operator--() {
								}

								bool operator==(const iterator& rhs) const {
								}

								bool operator!=(const iterator& rhs) const {
								}

						private:
								bst<Tk, Td> current_;

								iterator(bst<T> current)
																:current_(current) {
								}
				};

				explicit bst() {
				}

				bst(const bst& other) {
				}

				[[nodiscard]] std::size_t size() const {
				}

				void erase() {
				}

				bool empty() {
				}

				Td& operator[](const Tk& key) {
				}

				bool emplace(const Tk& key, const Td& data) {
				}

				bool remove(const Tk& key) {
				}

				Tk* tlr() {
				}

				std::size_t& height() {
				}

				iterator& begin() {

				}

				iterator& rbegin() {

				}

				iterator& end() {

				}

				iterator& rend() {

				}

				~bst() {
				}

		private:
};

#endif //ADS_CONTAINER_HPP
