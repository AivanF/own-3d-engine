# Own 3D engine using Qt, C++ with different algorithms and solids generating (w/o OpenGL)

![Screenshot 1](https://github.com/AivanF/own-3d-engine/raw/master/Screenshot1.jpeg)
![Screenshot 2](https://github.com/AivanF/own-3d-engine/blob/master/Screenshot2.jpeg?raw=true)

## 1. Functionality

- Simple 3D engines with planty of models (may be generated programmatically or loaded from files) and scene objects (they have their own properties such as position and rotation).
- Transform matrices with homogeneous coordinates: shifting, scaling, rotationg, perspective.
- Pruning of invisible edges with Roberts algorithm.
- Drawing algorithm with Z-buffer.
- Lighting: ambient, diffuse, and reflected light. Different fillings: by edges, Gouraud shading, and Phong shading.
- Models: Platonic solids, (tetrahedron, octahedron, hexahedron, icosahedron, dodecahedron), sphere, "garlic", torus, spiral, spring, conical spiral.
- Many helpful math (generating of transform matrices, matrices and vectors multiplication, dot production, normals, and reflected vectors calculations) and other functions.

## 2. Control

- Left/right arrow — scene rotating.
- Z/X keys — scene scaling.
- Q/E keys — change light intensity.
- E/R keys — change ratio of ambient light.
- T/Y keys — change power of reflected light.
- A/S/D keys — change between filling by edges, Gouraund and Phong shading.
- Checkbox "Perspective" — perspective/ortho projection.
- Checkbox "Roberts" — whether to use Roberts algorithm for invisible edges prunning.
- Checkbox "Z-buffering/Usual" — whether to use Z-buffer (with light shading) or painter algorithm.

## 3. Project structure

Programming language: C++. IDE: Qt Creator. Rendering created with standard facilities of Qt for GUI. OS: Mac OS X (butno platform-specific function was used). Explanations for .h/.cpp file pairs:

- `model` — class Model, it describes vertices, edges and triagles of a solid. Can be drawn from an Item. Can be loaded from or saved to a file.
- `item` — class Item, it is a scene object, it is linked with a model and has some own geometric attributes.
- `viewer` — Viewer class acts as both camera and scene.
- `mainwindow` — main window of the app. Handles user input.
- `data` — Functions for generation of different solids.
- `helper` — Some helpful math and other functions.

## 4. Interesting points

- During generation of dodecahedron initially pentagonal edges are created, which then are being splitted into 3 triangles.
- Sphere model is creating through recursive "inflation" of tetrahedron. Recursion depth is under control: depth 0 gives 12 verticies and 20 edges (usual tetrahedron), depth 1 — 42 verticies and 80 edges, depth 2 — 222 verticies and 320 edges.
- "Garlic" model was created from sphere transforming all the verticies this way: if Y greater than 0, than Y is increasing; if X or Z are close to 0, than other coordinate if decreasing. File `data.cpp`, function `createGarlic()`.
- Models of torus, spring and spiral are created this way: a set of circle's points is taken, then it is shifted along an axis, then it is cyclically rotated and copied. At each iteration a surface is created to link pair of circles. The algorithm has the following arguments: 1) circle (pipe) radius, 2) shifting length (torus radius), 3) rotations count, 4) iterative horizontal shifting, 5) iterative vertical shifting, 6) circle points count, and 7) circles count for each 360°. File `data.cpp`, function `createTorus()`.
- Double bufferisation is used to avoid "breaks".
- Rendering execution time is calculated and printed.
- To reduce rendering time when using Z-buffer and light shading, picture dimensions are divided by 2.

## 5. Structure of model file

The model files consist of 2 kinds of lines:
- Vertex description: `0 x y z` where x,y and z are float numbers.
- Triangle description: `1 a b c` where a, b and c are vertex indices.

Lines of different kinds may be passed in any order, only relative order of vertices must be the same to keep their indices.

## 6. References

- [Stack Overflow: perspective projection](https://gamedev.stackexchange.com/a/106349)
- [Wolfram MathWorld: Triangle Interior](http://mathworld.wolfram.com/TriangleInterior.html)
- [Paul Bourke: Platonic Solids](http://paulbourke.net/geometry/platonic/)
- [Wikipedia: Blinn–Phong shading model](https://en.wikipedia.org/wiki/Blinn–Phong_shading_model)
- [Wikipedia: Dot product](https://en.wikipedia.org/wiki/Dot_product)
- [Wikipedia: Normal](https://en.wikipedia.org/wiki/Normal_(geometry))

## 7. License

This code is provided 'as-is', without any express or implied warranty.
 You may not hold the author liable.
 
Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:
 
1. The origin of this code must not be misrepresented. You must not claim
 that you wrote the original software. When use the code, you must give appropriate credit,
 provide an active link to the original software, and indicate if changes were made.
 
2. Altered source versions must be plainly marked as such, and must not be misrepresented
 as being the original software.
 
3. This notice may not be removed or altered from any source distribution.
