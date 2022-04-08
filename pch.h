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


#include <iostream>


/*CRI ADX2 LEデータディレクトリへのパス*/
#define PATH	"../PCHLearn/CRI/Public/"

/*仮想キーコードの追加*/
#ifndef VK_ADDITIONAL
#define VK_ADDITIONAL

constexpr int VK_0 = (0x30);
constexpr int VK_1 = (0x31);
constexpr int VK_2 = (0x32);
constexpr int VK_3 = (0x33);
constexpr int VK_4 = (0x34);
constexpr int VK_5 = (0x35);
constexpr int VK_6 = (0x36);
constexpr int VK_7 = (0x37);
constexpr int VK_8 = (0x38);
constexpr int VK_9 = (0x39);

constexpr int VK_A = (0x41);
constexpr int VK_B = (0x42);
constexpr int VK_C = (0x43);
constexpr int VK_D = (0x44);
constexpr int VK_E = (0x45);
constexpr int VK_F = (0x46);
constexpr int VK_G = (0x47);
constexpr int VK_H = (0x48);
constexpr int VK_I = (0x49);
constexpr int VK_J = (0x4A);
constexpr int VK_K = (0x4B);
constexpr int VK_L = (0x4C);
constexpr int VK_M = (0x4D);
constexpr int VK_N = (0x4E);
constexpr int VK_O = (0x4F);
constexpr int VK_P = (0x50);
constexpr int VK_Q = (0x51);
constexpr int VK_R = (0x52);
constexpr int VK_S = (0x53);
constexpr int VK_T = (0x54);
constexpr int VK_U = (0x55);
constexpr int VK_V = (0x56);
constexpr int VK_W = (0x57);
constexpr int VK_X = (0x58);
constexpr int VK_Y = (0x59);
constexpr int VK_Z = (0x5A);

#endif