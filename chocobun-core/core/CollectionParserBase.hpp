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
// CollectionParserBase.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__

// --------------------------------------------------------------
// include files

#include <string>
#include <vector>
#include <core/Config.hpp>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

class Collection;
class Level;

/*!
 * @brief Base class for all collection parsers
 */
class CollectionParserBase
{
public:

    /*!
     * @brief Constructor
     */
    CollectionParserBase( void );

    /*!
     * @brief Destructor
     */
    virtual ~CollectionParserBase( void );

    /*!
     * @brief Saves a vector of level objects to a file
     *
     * This method performs some internal calculations, such as calculating
     * the maximum width and height of all of the levels, and then calls
     * the abstract method _save.
     *
     * @param collectionName The name of the collection to be saved
     * @param file An output file stream object to save to
     * @param levels A vector of level pointers to save
     */
    void save( std::ofstream& file, const Collection& collection );

    /*!
     * @brief Parses and loads all levels into a vector of Level objects
     *
     * This method calls the abstract method _parse
     *
     * @param file An open file input stream object, ready to read from
     * @param levels An empty vector in which the newly constructed levels can be
     * saved
     * @return Must return the name of the collection, so the host application is able
     * to display it. If no collection name is available, it is recommended to return
     * "collection".
     */
    void parse( std::ifstream& file, Collection& collection );

    /*!
     * @brief Enables compression of exported files
     *
     * Depending on what exporter is selected, a corresponding
     * compression algorithm is applied.
     *
     * @note Default is <b>disabled</b>
     */
    virtual void enableCompression( void );

    /*!
     * @brief Disables compression of exported files
     *
     * @note Default is <b>disabled</b>
     */
    virtual void disableCompression( void );

protected:

    /*!
     * @brief Parses and loads all levels into a vector of Level objects
     *
     * This method is pure virtual and must be implemented by the inheriting class.
     *
     * @param file An open file input stream object, ready to read from
     * @param levels An empty vector in which the newly constructed levels can be
     * saved
     * @return Must return the name of the collection, so the host application is able
     * to display it. If no collection name is available, it is recommended to return
     * "collection".
     */
    virtual void _parse( std::ifstream& file, Collection& collection ) = 0;

    /*!
     * @brief Saves a vector of level objects to a file
     *
     * This method is pure virtual and must be implemented by the inheriting class
     *
     * @param collectionName The name of the collection to be saved
     * @param file An output file stream object to save to
     * @param levels A vector of level pointers to save
     */
    virtual void _save( std::ofstream& file, const Collection& collection ) = 0;

    /*!
     * @brief Returns the maximum width of the level with the largest width.
     *
     * Returns the maximum width of the largest level in a collection. This
     * value is updated every time save is called.
     *
     * @return Maximum width of the largest level in this collection
     */
    Uint32 getMaxLevelWidth( void );

    /*!
     * @brief Returns the maximum height of all of the levels
     *
     * Returns the maximum height of the largest level in a collection. This
     * value is updated every time save is called.
     *
     * @return Maximum height of the largets level in this collection
     */
    Uint32 getMaxLevelHeight( void );

    /*!
     * @brief Converts a string of tiles to a standard internal format
     * Some Sokoban level formats differ from the conventional format by using
     * Capital and non-capital letters instead of symbols. This method converts
     * those back to conventional symbols to simplify internal use.
     * @note At this point, it should be definitive that the passed data does
     * in fact represent tiles and not something else, as no checks are
     * performed.
     * @param tiles The tiles to convert
     */
    void convertTilesToConventional( std::string& tiles );

private:

    Uint32 m_MaxLevelWidth;
    Uint32 m_MaxLevelHeight;

};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__
