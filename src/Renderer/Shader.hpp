#pragma once

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

public:
    Shader(const std::vector<std::string>& shaderFiles);  
    ~Shader();
    
    void Bind() { glUseProgram(m_shaderProgram); }
    void Unbind() { glUseProgram(0); }
    
    static Shader* CreateShader(const std::vector<std::string>& shaderFiles);
};