# cpp-object-pool

A simple c++ object pool header only library.

## Usage

```
#include "objectpool.h"

class Resource
{
  public:
    int x;
    Resource() = default;
    ~Resource() = default;
};

int main(int argc, char *argv[])
{
    std::shared_ptr<ObjectPool<Resource>> objPool{ObjectPool<Resource>::getInstance()};
    
    // get resource 1;
    std::unique_ptr<Resource> res1 = objPool->getResource();
    
    // return resource 1 
    objPool->returnResource(std::move(res1));
   
    //again get resource 1
    res1 = objPool->getResource();

    // get resource 2;
    std::unique_ptr<Resource> res2 = objPool->getResource();

    // returning both resources
    objPool->returnResource(std::move(res1));
    objPool->returnResource(std::move(res2));

    return 0;
}
```