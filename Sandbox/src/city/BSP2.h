#pragma once

#include <memory>
#include <functional>

#include "math/Line2.h"

namespace apryx {

	template<typename T>
	struct BSP2 {
		BSP2<T> *parent = nullptr;

		std::unique_ptr<BSP2<T>> front = nullptr;
		std::unique_ptr<BSP2<T>> back = nullptr;

		Line2<T> line;

		BSP2(Line2<T> line) : line(line) { }

		void insertFrontRaw(Line2<T> line) {
			front = std::make_unique<BSP2<T>>(line);
			front->parent = this;
		}

		void insertBackRaw(Line2<T> line) {
			back = std::make_unique<BSP2<T>>(line);
			back->parent = this;
		}

		void insert(Line2<T> newLine) {
			T distance = line.distanceFrom(newLine.position);

			// Inserting into the front
			if (distance > 0) {
				if (front == nullptr) {
					insertFrontRaw(newLine);
				}
				else {
					front->insert(newLine);
				}
			} 
			
			// Inserting into the rear (winkface)
			else {
				if (back == nullptr) {
					insertBackRaw(newLine);
				}
				else {
					back->insert(newLine);
				}
			}
		}
		
		void forEach(const std::function<void(BSP2<T>*)> &f) {
			f(this);

			if (front) front->forEach(f);
			if (back) back->forEach(f);
		}

		bool isLeaf() {
			return front == nullptr && back == nullptr;
		}
	};


	typedef BSP2<float> BSP2f;
	typedef BSP2<double> BSP2d;
}