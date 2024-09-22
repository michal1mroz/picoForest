# picoForest
Pichał wants, Pichał gets

## How to run
To compile run
```shell
  cmake .
  make run
```

### Important stuff here I guess

### To do
- [x] add glfw library
- [x] start project
- [ ] pichał finishes my project
- [ ] happy ending

### Changes
- Moved display related functionality to display/MainDisplay class
- Created Shader class in shaders directory
- As of now setters in Entity class sets also the modelMatrix used in shaders.
This means that the state of the Entity should be modified only using them, or, 
when changing position, rotation or scale inside the Entity class, one should also call getModelMatrix method to apply the changes. 
