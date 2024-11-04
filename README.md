# Bagel
im learning 3D graphics. hey maybe we will make a photorealistic scene who knows.

# How To Build
## Deps
1. OpenGL 460
2. cmake
3. Clang
4. ninja
<br> <br>
on windows, you can use MSVC instead of clang. <br>
if it doesnt build, i will probably fix it soon.

## The linux build problem
I dont know if its just for me but when i try to build on linux the app cant fucking compile the Shader Program. And I dont knwo why. <br>
I think its because of the OpenGL Version but again... I DONT KNOW! <br>
Maybe you can fix it.

## Build process
### Clone The Repo:
1. `git clone https://github.com/NotHalls/Bagel --recursive`
<br>
NOTE: do not forget the "--recursive" flag
<br>
2. `cd Bagel`

### Windows:
1. `cmake -G Ninja -B build -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug`
<br>OR, if you want MSVC<br>
`cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug`
2. `cmake --build build`
<br>
if you are using MSVC then just open the .sln file in Visual Studio

###

yea that should be all. <br>
unless im forgetting something.