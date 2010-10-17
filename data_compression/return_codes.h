/**
 * @file   return_codes.h
 * @Author Leonardo Korndorfer (leokorndorfer@gmail.com)
 * @date   September, 2010
 *
 * @brief  Stores return codes
 *
 * This file will define return codes for all error and function return in all 
 * the application. Please define new error codes inside this file.
 */

#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

enum return_codes {
	GENERIC_SUCCESS,
	GENERIC_FAIL,
	NODE_FOUND,
	NODE_NOT_FOUND 
};

#endif
