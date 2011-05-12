#ifndef TEXTSHADER_H
#define TEXTSHADER_H

#include "project.h"
#include <string>
#include "Shader.h"

class TextShader : public Shader
{
    public:
        TextShader(const std::string& base);
        TextShader(const char* base);
        virtual ~TextShader();
        void setVertexFile(const std::string& vertexFile);
        void setFragmentFile(const std::string& fragmentFile);
    protected:
        virtual void copyVertex(void);
        virtual void copyFragment(void);
        virtual void afterCompile(bool successfulCompile);
    private:
        std::string m_VertexFile;
        std::string m_FragmentFile;

        // I don't want to "new" for such small arrays that won't never change in size
        const GLchar* m_IntermediateString[2];
        GLint m_IntermediateLength[2];
};

#endif // TEXTSHADER_H
