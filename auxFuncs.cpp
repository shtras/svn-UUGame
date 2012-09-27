#include "StdAfx.h"
#include "auxFuncs.h"
#include <strsafe.h>
#include "Renderer.h"
#include "WLayout.h"

double RadToDeg(double rad)
{
  return rad * 180.0 / PI;
}

double DegToRad(double deg)
{
  return deg * PI / 180.0;
}

bool isNumberChar(int key)
{
  if (key >= 'a' && key <= 'z') {
    return true;
  }
  if (key >= 'A' && key <= 'Z') {
    return true;
  }
  return false;
}

bool isLetterChar(int key)
{
  if (key >= 0x30 && key <= 0x39) {
    return true;
  }
  return false;
}

void checkErrorDebug(CString errorMsg/* = ""*/)
{
  GLenum err = glGetError();
  if (err != 0) {
    Logger::getInstance().log(ERROR_LOG_NAME, errorMsg + CString(" OpenGL error: ") + CString((int)err));
  }
  assert(err == 0);
}

void checkReleaseError(CString errorMsg)
{
  checkErrorDebug(errorMsg);
}

vector<CString> getFileNames(CString dir)
{
  vector<CString> res;
  dir += "/*";

  HANDLE hFind = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATAA FindFileData;

  hFind = FindFirstFileA(dir, &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Cannot get files from " + dir);
    return res;
  }

  int nextFileExists = 0;

  do {
    CString fileName = FindFileData.cFileName;
    if (!(FindFileData.dwFileAttributes & 0x10)) {
      //Not a directory
      res.push_back(fileName);
    }
    nextFileExists = FindNextFileA(hFind, &FindFileData);
  } while (nextFileExists);

  return res;
}

bool loadBMP(CString fileName, GLuint* texNum)
{
  FILE* file = fopen(fileName, "rb");
  if (!file) {
    return false;
  }

  char signature[2];
  fread(signature, 1, 2, file);
  if (signature[0] != 'B' || signature[1] != 'M') {
    fclose(file);
    Logger::getInstance().log(ERROR_LOG_NAME, "Wrong magic in file: " + fileName);
    return false;
  }

  struct {
    DWORD fileSize;
    DWORD reserved;
    DWORD pixelOffset;
  } bmpHeader;

  fread(&bmpHeader, sizeof(bmpHeader), 1, file);

  struct {
    DWORD headerSize;
    DWORD width;
    DWORD height;
    WORD planes;
    WORD bpp;
    DWORD compression;
    DWORD imageSZ;
    DWORD xppm;
    DWORD yppm;
    DWORD colors;
    DWORD importantColors;
  } dibHeader;

  fread(&dibHeader, sizeof(dibHeader), 1, file);

  if (dibHeader.bpp != 24) {
    fclose(file);
    Logger::getInstance().log(ERROR_LOG_NAME, "BMP file is not in the 24bit format: " + fileName);
    return false;
  }

  fseek(file, bmpHeader.pixelOffset, SEEK_SET);
  unsigned char* buffer = new unsigned char[dibHeader.width * dibHeader.height * 3];
  if (fread(buffer, dibHeader.width*dibHeader.height*3, 1, file) != 1) {
    delete[] buffer;
    Logger::getInstance().log(ERROR_LOG_NAME, "Could not load image data from: " + fileName);
    fclose(file);
    return false;
  }
  fclose(file);

  unsigned char temp;
  for (uint32_t i=0; i<dibHeader.width*dibHeader.height*3; i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = buffer[i];
    buffer[i] = buffer[i+2];
    buffer[i+2] = temp;
  }

  glGenTextures(1, texNum);
  glBindTexture(GL_TEXTURE_2D, *texNum);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, dibHeader.width, dibHeader.height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dibHeader.width, dibHeader.height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
  delete[] buffer;

  checkReleaseError("Could not initialize texture from file: " + fileName);

  return true;
}

float getSquareWidthForHeightInLayout(float height, WLayout* layout)
{
  return height / (layout->getWidth()/layout->getHeight() * (float)Renderer::getInstance().getWidth() / (float)Renderer::getInstance().getHeight());
}
