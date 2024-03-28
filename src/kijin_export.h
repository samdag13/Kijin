#pragma once
#ifdef KIJIN_EXPORTS
#define KIJIN_API __declspec(dllexport)
#else
#define KIJIN_API __declspec(dllimport)
#endif