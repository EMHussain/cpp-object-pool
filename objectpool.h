#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H


#include <list>
#include <memory>

template<typename T>
class ObjectPool
{
        private:
        std::list<std::unique_ptr<T>> resources;

        static inline std::shared_ptr<ObjectPool> instance;  // c++17 inline static
        ObjectPool() {}
public:
        /**
         * Static method for accessing class instance.
         * Part of Singleton design pattern.
         *
         * @return ObjectPool instance.
         */
        static std::shared_ptr<ObjectPool> getInstance()
        {
            if (instance == 0)
            {
                instance = std::shared_ptr<ObjectPool>(new ObjectPool);
            }
            return instance;
        }
        /**
         * Returns instance of Resource.
         *
         * New resource will be created if all the resources
         * were used at the time of the request.
         *
         * @return Resource instance.
         */
        std::unique_ptr<T> getResource()
        {
            if (resources.empty())
            {
                return std::unique_ptr<T> (new T());
            }
            else
            {
                std::unique_ptr<T> resource = std::move(resources.front());
                resources.pop_front();
                return resource;
            }
        }
        /**
         * Return resource back to the pool.
         *
         * The resource must be initialized back to
         * the default settings before someone else
         * attempts to use it.
         *
         * @param object Resource instance.
         * @return void
         */
        void returnResource(std::unique_ptr<T> object)
        {
            resources.push_back(std::move(object));
        }
};
#endif //OBJECTPOOL_H
