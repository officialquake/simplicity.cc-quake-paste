/*
 *  main.h
 */
#pragma once

#include <map>
#include <array>
#include <deque>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <dlfcn.h>
#include <codecvt>          // string_to_wstring
#include <sys/stat.h>
#include <sys/mman.h>       // used in protect_addr
#include <unordered_map>
#include <mach-o/dyld_images.h>

using namespace std;

#include "SDK.h"

#include "settings.h"

#include "renderer.h"

#include "global.h"

#include "util.h"

#include "hooks.h"
