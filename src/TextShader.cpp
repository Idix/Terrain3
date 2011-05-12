#include "TextShader.h"

#include <fstream>

TextShader::TextShader(const std::string& base)
{
    setVertexFile(base + ".vertex");
    setFragmentFile(base + ".fragment");
}

TextShader::TextShader(const char* cbase)
{
    std::string base(cbase);
    setVertexFile(base + ".vertex");
    setFragmentFile(base + ".fragment");
}

TextShader::~TextShader()
{
    //dtor
}

void TextShader::setVertexFile(const std::string& vertexFile)
{
    m_VertexFile = vertexFile;
}

void TextShader::setFragmentFile(const std::string& fragmentFile)
{
    m_FragmentFile = fragmentFile;
}

void TextShader::copyVertex(void)
{
    int length;
    vertexCount = 1;
    vertexString = &m_IntermediateString[0];
    vertexLength = &m_IntermediateLength[0];

    std::ifstream is;
    is.open (m_VertexFile.c_str(), std::ios::out);

    // get length of file:
    is.seekg (0, std::ios::end);
    length = is.tellg();
    is.seekg (0, std::ios::beg);

    // allocate memory:
    m_IntermediateString[0] = new GLchar[length];
    m_IntermediateLength[0] = length;

    // read data as a block:
    is.read((char*)m_IntermediateString[0], length);
    is.close();
}

void TextShader::copyFragment(void)
{
    int length;
    fragmentCount = 1;
    fragmentString = &m_IntermediateString[1];
    fragmentLength = &m_IntermediateLength[1];

    std::ifstream is;
    is.open (m_FragmentFile.c_str(), std::ios::out);

    // get length of file:
    is.seekg (0, std::ios::end);
    length = is.tellg();
    is.seekg (0, std::ios::beg);

    // allocate memory:
    m_IntermediateString[1] = new GLchar[length];
    m_IntermediateLength[1] = length;

    // read data as a block:
    is.read((char*)m_IntermediateString[1], length);
    is.close();
}

void TextShader::afterCompile(bool successfulCompile)
{
    Shader::afterCompile(successfulCompile);

    delete [] m_IntermediateString[0];
    delete [] m_IntermediateString[1];
}
