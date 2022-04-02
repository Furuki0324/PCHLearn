#pragma once
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <Windows.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <cassert>

/*Vector2などが入っているヘッダー*/
#include "Math.h"

/*DirectX*/
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

/*CRI SDK header*/
#include <cri_le_xpt.h>

/*CRI ADX2 LE header*/
#include <cri_le_atom_ex.h>
#include <cri_le_atom_wasapi.h>
#include <cri_le_atom.h>

#ifdef _DEBUG
#include <iostream>
#endif

/*CRI ADX2 LEデータディレクトリへのパス*/
#define PATH	"../PCHLearn/CRI/Public/"