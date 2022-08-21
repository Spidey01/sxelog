#ifndef SXE_LOGGING_API__HPP
#define SXE_LOGGING_API__HPP
/*-
 * Copyright (c) 2020-current, Terry Mathew Poulin <BigBoss1964@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *	1. The origin of this software must not be misrepresented; you must
 *	   not claim that you wrote the original software. If you use this
 *	   software in a product, an acknowledgment in the product
 *	   documentation would be appreciated but is not required.
 *
 *	2. Altered source versions must be plainly marked as such, and must
 *	   not be misrepresented as being the original software.
 *
 *	3. This notice may not be removed or altered from any source
 *	   distribution.
 */

/* Standard headers required for logging. */

#include <algorithm>
#include <cassert>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

/*
 * SxE has work arounds for detecting __cplusplus saying C++17 but no filesystem header exists.
 * SxE log does not.
 * This would be a good thing to put in a config.hpp.in -> config.hpp.
 * 
 * To override __cplusplus: define SXELOG_NO_FILESYSTME_HEADER when building and using.
 */

#ifndef SXELOG_NO_FILESYSTEM_HEADER
#define SXELOG_NO_FILESYSTEM_HEADER 0
#endif
#define SXELOG_CXX17 ( __cplusplus > 201402L && !SXELOG_NO_FILESYSTEM_HEADER )
#if SXELOG_CXX17
#include <filesystem>
#endif

/* Generate by cmake generate_export_header(). */
#include <sxe/logging/sxelog_export.hpp>

#endif // SXE_LOGGING_API__HPP