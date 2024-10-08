#pragma once

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>


// OPENGL STUFF //
#define ASSERT(x, msg)\
    {\
        if(!(x))\
        {\
            throw std::runtime_error("ASSERTION OCCURED WITH DESCRIPTION: " + std::string(msg));\
        }\
    }
#define CheckErrors(x)\
    clearErrors();\
    x;\
    ASSERT(checkGLErrors(#x, __FILE__, __LINE__), "\n:(\n");

static void clearErrors()
{ while(glGetError() != GL_NO_ERROR); }

static bool checkGLErrors(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cerr << "FUCK! ERROR WITH OPENGL: " << error
                  << "\tIn FIle: " << file
                  << "\tIn Line: " << line << std::endl;

        return false;
    }
    return true;
}