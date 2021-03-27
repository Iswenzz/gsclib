/* Copyright (c) 2014, 2015 Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

/**
  @file binary_log_types.h

  @brief This file contains the field type.


  @note This file can be imported both from C and C++ code, so the
  definitions have to be constructed to support this.
*/

#ifndef BINARY_LOG_TYPES_INCLUDED
#define BINARY_LOG_TYPES_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Constants exported from this package.
 */

typedef enum enum_field_types {
  MYSQL_TYPE_DECIMAL      = 0,
  MYSQL_TYPE_TINY         = 1,
  MYSQL_TYPE_SHORT        = 2,
  MYSQL_TYPE_LONG         = 3,
  MYSQL_TYPE_FLOAT        = 4,
  MYSQL_TYPE_DOUBLE       = 5,
  MYSQL_TYPE_NULL         = 6,
  MYSQL_TYPE_TIMESTAMP    = 7,
  MYSQL_TYPE_LONGLONG     = 8,
  MYSQL_TYPE_INT24        = 9,
  MYSQL_TYPE_DATE         = 10,
  MYSQL_TYPE_TIME         = 11,
  MYSQL_TYPE_DATETIME     = 12,
  MYSQL_TYPE_YEAR         = 13,
  MYSQL_TYPE_NEWDATE      = 14,
  MYSQL_TYPE_VARCHAR      = 15,
  MYSQL_TYPE_BIT          = 16,
  MYSQL_TYPE_TIMESTAMP2   = 17,
  MYSQL_TYPE_DATETIME2    = 18,
  MYSQL_TYPE_TIME2        = 19,
  MYSQL_TYPE_JSON         = 245,
  MYSQL_TYPE_NEWDECIMAL   = 246,
  MYSQL_TYPE_ENUM         = 247,
  MYSQL_TYPE_SET          = 248,
  MYSQL_TYPE_TINY_BLOB    = 249,
  MYSQL_TYPE_MEDIUM_BLOB  = 250,
  MYSQL_TYPE_LONG_BLOB    = 251,
  MYSQL_TYPE_BLOB         = 252,
  MYSQL_TYPE_VAR_STRING   = 253,
  MYSQL_TYPE_STRING       = 254,
  MYSQL_TYPE_GEOMETRY     = 255
} enum_field_types;

#define DATETIME_MAX_DECIMALS 6

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* BINARY_LOG_TYPES_INCLUDED */
