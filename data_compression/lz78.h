/*
 * LZ78 - This is a library that encode a strem with LZ78 algorithm
 * Copyright (C) 2010  Leonardo Richter Korndorfer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   lz78.h
 * @Author Leonardo Korndorfer (leokorndorfer@gmail.com)
 * @date   October, 2010
 *
 * @brief  This file has complement stuff
 *
 * Detailed description of file.
 */


#ifndef __LZ78_H__
#define __LZ78_H__

#define DICT_SIZE 200

typedef struct lz78_triplet_s lz78_triplet_t;
struct  lz78_triplet_s
{
	int  dict_entry;
	char next_letter;	
};

/*
 * this is the lz78 dictionary.
 * times_used is used when dictionaly is full
 */
typedef struct dictionary_lz78_s dictionary_lz78_t;
struct dictionary_lz78_s
{
	int  times_used;
	char *word;
};

#endif
