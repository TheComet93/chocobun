/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
 */

// --------------------------------------------------------------
// define export macros
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_EXPORT_HPP__
#   define __CHOCOBUN_CORE_EXPORT_HPP__

    // headers
#   include <ChocobunConfig.hpp>

#   if defined(CHOCOBUN_CORE_DYNAMIC)
#       define CHOCOBUN_CORE_API CHOCOBUN_CORE_EXPORT
#   else
#       define CHOCOBUN_CORE_API CHOCOBUN_CORE_IMPORT
#   endif

#endif // __CHOCOBUN_CORE_EXPORT_HPP__