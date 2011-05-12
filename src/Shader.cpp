#include "Shader.h"

Shader::Shader(void) : compiled(false)
{
    id = glCreateProgram();
}

Shader::~Shader(void)
{
    glDeleteProgram(id);
}

void Shader::printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = new char[infologLength+1];
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cerr << infoLog << "\n";
		delete [] infoLog;
    }
}

void Shader::printProgramInfoLog(void)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(id, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = new char[infologLength+1];
        glGetProgramInfoLog(id, infologLength, &charsWritten, infoLog);
		std::cerr << infoLog << "\n";
		delete [] infoLog;
    }
}

bool Shader::compile(void)
{
    bool success = true;
    GLint result;

    if (compiled)
    {
        // Detach previous shaders
        glDetachShader(id, vertexId);
        glDetachShader(id, fragmentId);
    }

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    this->copyVertex();
    glShaderSource(vertexId, vertexCount, vertexString, vertexLength);
    glCompileShader(vertexId);
    glAttachShader(id, vertexId);
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &result);
    success &= (result == GL_TRUE);
    if (result == GL_FALSE)
        printShaderInfoLog(vertexId);

    this->copyFragment();
    glShaderSource(fragmentId, fragmentCount, fragmentString, fragmentLength);
    glCompileShader(fragmentId);
    glAttachShader(id, fragmentId);
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &result);
    success &= (result == GL_TRUE);
    if (result == GL_FALSE)
        printShaderInfoLog(fragmentId);

    if (success) {
	    glBindAttribLocation(id, 0, "vVertex");
	    glBindAttribLocation(id, 1, "vColor");
	    glBindAttribLocation(id, 2, "vNormal");
	    glBindAttribLocation(id, 3, "vTexCoord");

        glLinkProgram(id);
        printProgramInfoLog();
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        success &= (result == GL_TRUE);
    }

    this->afterCompile(success);

    // Mark shaders for deletion
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    compiled = success;
    return success;
}

void Shader::use(bool useShader) const
{
	if( useShader && compiled )
		glUseProgram(id);
	else
		glUseProgram(0);
}

GLuint Shader::getId(void) const
{
	return id;
}

void Shader::afterCompile(bool successfulCompile)
{
    //
}

bool Shader::setUniformMatrix4(const char* name, const GLfloat* value, GLsizei count, GLboolean transpose)
{
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name);
    if (location < 0)
        return false;
    glUniformMatrix4fv(location, count, transpose, value);
    glUseProgram(0);
    return true;
}

bool Shader::setUniformMatrix3(const char* name, const GLfloat* value, GLsizei count, GLboolean transpose)
{
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name);
    if (location < 0)
        return false;
    glUniformMatrix3fv(location, count, transpose, value);
    glUseProgram(0);
    return true;
}

bool Shader::setUniform3f(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name);
    if (location < 0)
        return false;
    glUniform3f(location, x, y, z);
    glUseProgram(0);
    return true;
}

bool Shader::setUniform1i(const char* name, GLint v0)
{
    glUseProgram(id);
    GLint location = glGetUniformLocation(id, name);
    if (location < 0)
        return false;
    glUniform1i(location, v0);
    glUseProgram(0);
    return true;
}
