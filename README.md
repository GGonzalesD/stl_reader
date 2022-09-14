# Stl Reader

Leactura y escritura de archivos `.stl` en diferentes lenguages.

---
## Stl Reader en C
```c
#include "stl_reader.h"

MODEL * model = stl_load("model.stl");

stl_print(*model);

stl_save("model.edit.stl", model);

stl_free(model);
```
---
## Stl Reader en C++
```cpp
#include "stl_reader.hpp"

stl::Model model = stl::Model::read("model.stl");

std::cout << model << std::endl;

model.write("model.edit.stl");
```
---
## Stl Reader en Python
```python
from stl_reader import Stl

stl = Stl.read("model.stl")

print(stl)

stl.write("model.edit.stl")
```
---
## Stl Reader en Javascript
```js
import { save, load } from "./stl.js";

const model = load("model.stl")

console.log(model)

save("model.edit.stl", model)
```
---
## Stl Reader en Java
```java
try{
    Stl stl = Stl.read("model.stl");

    System.out.println(stl);

    stl.write("model.edit.stl");
}catch(FileNotFoundException e){
    e.printStackTrace(System.err);
}
```
---
## Stl Reader en C#
```c#
var stl = Stl.Read("model.stl");

Console.WriteLine(stl);

stl.Write("model.edit.stl");
```
