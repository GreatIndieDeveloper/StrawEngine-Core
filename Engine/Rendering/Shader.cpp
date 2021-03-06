#include "Shader.h"
#include <string>
#include "Renderer.h"
Shader::Shader(const std::string& FPath,const std::string& VPath)
    : FragShdr(0), VertShdr(0), ID(0) {
  _fragpath = FPath;
  _vertpath = VPath;
}
Shader::~Shader() {}

void Shader::Init() {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile; 
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open(_vertpath);
    fShaderFile.open(_fragpath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "Couldn't Read Shader File" << std::endl;
  }
  _vertsource = (char *)vertexCode.c_str();
  _fragsource = (char *)fragmentCode.c_str();
  CompileShader(&VertShdr, _vertsource, GL_VERTEX_SHADER);
  CompileShader(&FragShdr, _fragsource, GL_FRAGMENT_SHADER);
  ID = glCreateProgram();
  glAttachShader(ID, VertShdr);
  glAttachShader(ID, FragShdr);
  glLinkProgram(ID);
  int success;
  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    std::cout << _vertsource << std::endl;
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
}
void Shader::use() { glUseProgram(ID); }
void Shader::CompileShader(unsigned int *shdrID, const char *Source,
                           int SXType) {
  (*shdrID) = glCreateShader(SXType);
  glShaderSource((*shdrID), 1, &Source, NULL);
  glCompileShader((*shdrID));
  int success;
  char infoLog[512];
  glGetShaderiv((*shdrID), GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog((*shdrID), 512, NULL, infoLog);
    std::cout << " FAILED SHADER : " << infoLog << std::endl;
  }
}
