#pragma once

#include <gl/glew.h>
#include <gl/glut.h>

class WLayout;

double RadToDeg(double rad);
double DegToRad(double deg);

bool isNumberChar(int key);
bool isLetterChar(int key);

void checkErrorDebug(CString errorMsg = "");

void checkReleaseError(CString errorMsg);

bool loadBMP(CString fileName, GLuint* texNum);

vector<CString> getFileNames(CString dir);

float getSquareWidthForHeightInLayout(float height, WLayout* layout);

void drawCircle(float radius, bool filled, int segments = 36);

float getRandom(float cap);
