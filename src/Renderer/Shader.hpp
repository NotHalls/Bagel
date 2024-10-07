#pragma once

#include "ext/vector_float3.hpp"
#include "ext/vector_int3.hpp"
#include <string>
#include <vector>

#include <glad/glad.h>


class Shader
{
private:
    uint32_t m_shaderProgram = NULL;


private:
    std::string ReadFromFile(const std::string& filePath);
    
    std::string readFile(const std::string& filePath);
    void processShader(const std::vector<std::string>& shaderFiles);

    std::string getShaderTypeFromExtension(const std::string& filePath);
    int getUniformLocation(const std::string& name);

public:
    Shader(const std::vector<std::string>& shaderFiles);  
    ~Shader();
    
    void Bind() { glUseProgram(m_shaderProgram); }
    void Unbind() { glUseProgram(0); }

    void SetUniformFloat(const std::string& uniformName, float value);
    void SetUniformInt(const std::string& uniformName, int value);

    void SetUniformVec3(const std::string& uniformName, const glm::vec3& value);
    void SetUniformIVec3(const std::string& uniformName, const glm::ivec3& value);


    
    static Shader* CreateShader(const std::vector<std::string>& shaderFiles);
};