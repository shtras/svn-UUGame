#pragma once

#include <gl/glew.h>
#include <gl/glut.h>

double RadToDeg(double rad);
double DegToRad(double deg);

bool isNumberChar(int key);
bool isLetterChar(int key);

void checkErrorDebug(CString errorMsg = "");

void checkReleaseError(CString errorMsg);

bool loadBMP(CString fileName, GLuint* texNum);

vector<CString> getFileNames(CString dir);
