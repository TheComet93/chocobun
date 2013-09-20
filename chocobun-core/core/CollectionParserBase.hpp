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
// Base class for all collection parsers
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__

// --------------------------------------------------------------
// include files

#include <string>
#include <vector>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations
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
    virtual std::string parse( std::ifstream& file, std::vector<Level*>& levels ) = 0;

    /*!
     * @brief Saves a vector of level objects to a file
     *
     * This method is pure virtual and must be implemented by the inheriting class
     */
    virtual void save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels ) = 0;

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
     * @brief Registers a level to a level vector
     */
    void registerLevel( Level* level, std::string& levelName, std::vector<Level*>& levels );

};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_BASE_HPP__