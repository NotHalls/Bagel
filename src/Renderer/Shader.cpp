#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "Shader.hpp"


Shader* Shader::CreateShader(const std::vector<std::string>& shaderFiles)
{
    return new Shader(shaderFiles);
}


Shader::Shader(const std::vector<std::string>& shaderFiles)
{
    processShader(shaderFiles);
}
Shader::~Shader()
{
    glDeleteProgram(m_shaderProgram);
}

void Shader::processShader(const std::vector<std::string>& shaderFiles)
{
    m_shaderProgram = glCreateProgram();

    for(const std::string& file : shaderFiles)
    {
        GLenum shaderType;
        if(getShaderTypeFromExtension(file) == ".vertex.glsl")
            shaderType = GL_VERTEX_SHADER;
        else if(getShaderTypeFromExtension(file) == ".fragment.glsl")
            shaderType = GL_FRAGMENT_SHADER;
        else
            throw std::runtime_error(
                "Somethign Went Wrong While Trying To Get Shader Type Shader File"
            );

        uint32_t shader = glCreateShader(shaderType);

        std::string sourceString = readFile(file);
        const char* source = sourceString.c_str();
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, shaderType, &success);
        if(!success)
        {
            const int maxLength = 512;
            // glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            char infoLog[maxLength];
            glGetShaderInfoLog(shader, maxLength, nullptr, infoLog);

            glDeleteShader(shader);
            std::cout << "Failed To Compile "
                      << file << "\n\tDescription: " << infoLog << std::endl;
        }

        glAttachShader(m_shaderProgram, shader);
    }

    glLinkProgram(m_shaderProgram);
    int success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        const int maxLength = 512;
        // glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        char infoLog[maxLength];
        glGetProgramInfoLog(m_shaderProgram, maxLength, nullptr, infoLog);

        glDeleteProgram(m_shaderProgram);
        std::cout << std::string("Failed To Link The Shader Program\n\t")
                  << "\n\tDescription: " << infoLog;
    }
}

std::string Shader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if(!file)
        throw std::runtime_error("Failed To Open The File: " + filePath);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string Shader::getShaderTypeFromExtension(const std::string& filePath)
{
    size_t dotPosition = filePath.find_first_of(".");
    std::string extension = filePath.substr(dotPosition);

    if(dotPosition != std::string::npos)
        return extension;    // should be wprry about returning a temp obj?

    return "";                                  // here aswell
}