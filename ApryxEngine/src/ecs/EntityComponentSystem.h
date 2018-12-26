#pragma once

#include <vector>
#include <assert.h>
#include <string.h>
#include <functional>

#include "Entity.h"
#include "Component.h"

namespace apryx{
    
    const int MaxComponentInit = 1000;

    struct ComponentList{
        int size = 0;
        int reserved = 0;
        Component *components = nullptr;

        #ifdef _DEBUG
        int componentIndex = 0;
        #endif
    public:
		ComponentList() {};
		ComponentList(const ComponentList &c) = delete;
		ComponentList(ComponentList &&c);
		~ComponentList();

        inline bool isInitialized() { return components != nullptr; }

        template<typename T>
        void init(){
            assert(!isInitialized());
            assert(size == 0);
            assert(reserved == 0);

            reserved = MaxComponentInit;
            components = new T[MaxComponentInit];

            #ifdef _DEBUG
            componentIndex = getComponentId<T>();
            #endif
        }

        template<typename T>
        T *add(){
            assert(components != nullptr);

            #ifdef _DEBUG
            assert(componentIndex == getComponentId<T>());
            #endif
            
            if(size >= reserved){
                // Create the new array
                T* n = new T[reserved * 2];

                // Copy the old contents
                memcpy(n, components, sizeof(T) * reserved);

                // Update the amount reserved
                reserved *= 2;

                components = n;
            }

            size++;

			return get<T>(size - 1);
        }

		template<typename T>
		T *get(size_t index) {
			#ifdef _DEBUG
			assert(componentIndex == getComponentId<T>());
			#endif
			T* t = (T*)components;
			return &t[index];
		}

    };
    
    struct EntityComponentSystem {
        std::vector<Entity> entities;

        int currentId = 0;

        std::vector<ComponentList> components;
    public:
        Entity createEntity();

        template<typename T>
        T* addComponent(Entity entity){
			auto &list = getComponentList<T>();

            T* comp = list.add<T>();

			comp->entityId = entity.id;

            return comp;
        }

        template<typename T>
        T* getComponent(Entity entity){
            size_t componentIndex = getComponentId<T>();

            if(components.size() < componentIndex){
                return nullptr;
            }

            ComponentList &c = components[componentIndex];

            if(!c.isInitialized()){
                return nullptr;
            }

			// TODO binary search
			// TODO sort the lists
			// This can be changed to binary search when sorted
            for(int i = 0; i < c.size; i++){
				T* t = c.get<T>(i);
                if(t->entityId == entity.id){
					return t;
                }
            }
            
            return nullptr;
        }
    

		// All the process searches are very slow currently
		template<typename C1>
		void process(const std::function<void(Entity, C1 &)> &f) {

			auto &list1 = getComponentList<C1>();
			int index1 = 0;

			for (size_t i = 0; i < entities.size(); i++) {
				Entity e = entities[i];

				// TODO this can be optimized even further when overshooting just recorrecting the rest (maybe even not linearly)
				while (e.id > list1.get<C1>(index1)->entityId) {
					index1++;

					if (index1 >= list1.size)
						return;
				}

				if (e.id == list1.get<C1>(index1)->entityId) {
					f(entities[i], *list1.get<C1>(index1));
				}
			}

		}


		template<typename C1, typename C2>
		void process(const std::function<void(Entity, C1 &, C2 &)> &f) {
			// TODO fix the sorting. This only works if all the components are in order!
			// TODO fix the sorting again. This only works if the entities are in order as well.

			auto &list1 = getComponentList<C1>();
			auto &list2 = getComponentList<C2>();

			int index1 = 0;
			int index2 = 0;

			for (int i = 0; i < entities.size(); i++) {
				Entity e = entities[i];

				// TODO this can be optimized even further when overshooting just recorrecting the rest (maybe even not linearly)
				while (e.id > list1.get<C1>(index1)->entityId) {
					index1++;

					if (index1 >= list1.size)
						return;
				}
				while (e.id > list2.get<C2>(index2)->entityId) {
					index2++;

					if (index2 >= list2.size)
						return;
				}

				if (e.id == list1.get<C1>(index1)->entityId
					&& e.id == list2.get<C2>(index2)->entityId) {
					f(entities[i], *list1.get<C1>(index1), *list2.get<C2>(index2));
				}
			}
		}

		template<typename C1, typename C2, typename C3, typename C4, typename C5, typename C6>
		void process(const std::function<void(Entity, C1 &, C2 &, C3 &, C4 &, C5 &, C6 &)> &f) {

			for (size_t i = 0; i < entities.size(); i++) {

				// TODO use a smart search (knowing the order of the entities)
				C1 *c1 = getComponent<C1>(entities[i]);
				C2 *c2 = getComponent<C2>(entities[i]);
				C3 *c3 = getComponent<C3>(entities[i]);
				C4 *c4 = getComponent<C4>(entities[i]);
				C5 *c5 = getComponent<C5>(entities[i]);
				C6 *c6 = getComponent<C6>(entities[i]);

				if (c1 != nullptr
					&& c2 != nullptr
					&& c3 != nullptr
					&& c4 != nullptr
					&& c5 != nullptr
					&& c6 != nullptr) {
					f(entities[i], *c1, *c2, *c3, *c4, *c5, *c6);
				}
			}
		}

	private:
		template<typename T>
		ComponentList &getComponentList() {
			size_t componentIndex = getComponentId<T>();

			if (components.size() <= componentIndex) {
				components.resize(componentIndex + 1);
			}

			ComponentList &list = components[componentIndex];

			if (!list.isInitialized()) {
				list.init<T>();
			}

			return list;
		}
	};


}