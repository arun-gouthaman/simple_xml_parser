<B>Simple xml parser that reads xml data and creates nodes.</B>

Parse xml file checking for tags and values

for each tag and value a node is created which holds pointers to next and previous nodes

next node points to vector of nodes to hold multiple children.

with each node the length of the node from root is incremented to hold head and end nodes.

After parsing the entire file and nodes are created, nodes are traversed from root recursively and values printed.



to build
install cmake (https://cmake.org/download/)
navigate to cloned folder

```mkdir build; cd build```

```cmake .. -G "Visual Studio 16 2019"```

compiling code

```msbuild .\<solutuion_file>.sln /p:Configuration=RelWithDebInfo```