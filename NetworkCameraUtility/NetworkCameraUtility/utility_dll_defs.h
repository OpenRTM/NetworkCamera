/*!
 * @file  utility_dll_defs.h
 * @brief dll export declarations
 * @date  2014-02-06
 */
#ifndef UTILITY_DLL_DEFS_H
#define UTILITY_DLL_DEFS_H

#ifdef NETWORKCAMERAUTILITY_EXPORTS
#define NETWORKCAMERAUTILITY_API __declspec(dllexport)
#else
#define NETWORKCAMERAUTILITY_API __declspec(dllimport)
#endif

#endif // UTILITY_DLL_DEFS_H