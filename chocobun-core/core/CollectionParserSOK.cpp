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
// CollectionParserSOK.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Utils.hpp>
#include <core/Collection.hpp>
#include <core/CollectionParserSOK.hpp>
#include <core/Level.hpp>
#include <core/RLE.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParserSOK::CollectionParserSOK( void ) :
    m_EnableRLE( false )
{
}

// --------------------------------------------------------------
CollectionParserSOK::~CollectionParserSOK( void )
{
}

// --------------------------------------------------------------
bool CollectionParserSOK::getKeyValuePair( const std::string& str, std::string& key, std::string& value )
{

    size_t pos = str.find( ":" ); // key-value pairs are split by a colon
    if( pos == std::string::npos )
        return false;

    if( pos < 2 ) // empty key value pairs
        return false;

    if( str.find( "::" ) != std::string::npos ) // comments are not permitted
        return false;

    // extract key and value
    key = str.substr(0, pos);
    value = str.substr(pos+1, str.size()-pos);

    // trim key and value from leading and trailing spaces
    size_t strBegin = key.find_first_not_of( " " );
    size_t strEnd = key.find_last_not_of( " " );
    key = key.substr(strBegin, strEnd-strBegin+1);
    strBegin = value.find_first_not_of( " " );
    strEnd = value.find_last_not_of( " " );
    value = value.substr(strBegin, strEnd-strBegin+1);

    return true;
}

// --------------------------------------------------------------
void CollectionParserSOK::_parse( std::ifstream& file, Collection& collection )
{
#ifdef _DEBUG
    std::cout << "parsing SOK" << std::endl;
#endif

    // the first level is a requirement
    Level* lvl = collection.addLevel();

    // run length encoding
    RLE rle;

    // parser temporaries
    Uint32 tileLine = 0;
    bool lastLineWasBlank = true;
    bool isLevelData = false;
    bool lastLineWasLevelData = false;
    bool levelDataReadForFirstTime = false;
    std::string inBuf("");
    std::string oldInBuf("");
    std::string levelName("");
    std::string tempLevelName("");

    // parse file
    while( !file.eof() )
    {

        // read line from file and filter out any blank lines
        // additionally, flag if a blank line was found and save the last line
        // in an old buffer so the title of the level can be determined later on
        lastLineWasBlank = false;
        oldInBuf = inBuf;
        while(!file.eof())
        {
            std::getline( file, inBuf );
            if( inBuf.size() > 1 )
                break;
            lastLineWasBlank = true;
        }

        // remove tabs
        inBuf.erase(std::remove(inBuf.begin(), inBuf.end(), '\t'), inBuf.end());

        // so checks are only performed once
        lastLineWasLevelData = isLevelData;
        isLevelData = Utils::isTileData( inBuf );

        // requirements for a level title are:
        // - the last non-blank line before a puzzle, saved game, or solution
        // - must be preceeded by a blank line
        // - must not be a comment
        // copying the last line as the level title before getting a new line
        // from the file to meet these requirements

        if( lastLineWasBlank && oldInBuf.find("::") == std::string::npos && isLevelData && !Utils::isTileData( oldInBuf ) )
        {
            std::string key("");
            std::string value("");
            if( !this->getKeyValuePair(oldInBuf, key, value) )
            {
                tempLevelName = oldInBuf;
                if( levelName.size() == 0 && !levelDataReadForFirstTime )
                    levelName = tempLevelName;
            }
        }

        // create new level if beginning of new level data has been found
        // this only works if level data has been read at least once
        if( levelDataReadForFirstTime && (!lastLineWasLevelData || lastLineWasBlank) && isLevelData )
        {
            if( levelName.size() != 0 )
            {
                lvl->removeHeaderData( levelName ); // level name was added in the last pass, remove it again
                lvl->removeLevelNote( levelName );
            }
            if( tempLevelName.size() != 0 )
            {
                lvl->removeHeaderData( tempLevelName );
                lvl->removeLevelNote( tempLevelName );
            }

            // finalise the level name
            collection.generateLevelName( levelName );
            lvl->setLevelName( levelName );

            // TODO reverse Y order of level array (see issue #16)

            // generate new level
            lvl = collection.addLevel();
            if( levelName.compare( tempLevelName ) == 0 ) tempLevelName = "";
            levelName = tempLevelName;
            tileLine = 0;
        }
        if( isLevelData )
            levelDataReadForFirstTime = true;

        // process input
        for(;;){

            // determine if if is level data
            if( isLevelData )
            {
                rle.decompress( inBuf );
                this->convertTilesToConventional( inBuf );
                lvl->insertTileLine( tileLine, inBuf );
                ++tileLine;
                break;
            }

            // determine if it is a key-value pair
            std::string key("");
            std::string value("");
            if( this->getKeyValuePair( inBuf, key, value ) )
            {

                // special case for collection name
                if( key.compare("Collection") == 0 )
                {
                    collection.setName( value );
                    break;
                }

                // special case for snapshots
                if( key.compare("Snapshot") == 0 )
                {
                    lvl->importUndoData( value );
                    break;
                }

                // add meta data to level
                lvl->addMetaData( key, value );
                break;
            }

            // add data as comment data
            if( levelDataReadForFirstTime )
                lvl->addLevelNote( inBuf );
            else
                lvl->addHeaderData( inBuf );
            break;
        }
    }

    // give the still open level its name
    collection.generateLevelName( levelName );
    lvl->setLevelName( levelName );

#ifdef _DEBUG
    std::cout << "parsing SOK successful" << std::endl;
#endif
}

// --------------------------------------------------------------
void CollectionParserSOK::enableCompression( void )
{
    m_EnableRLE = true;
}

// --------------------------------------------------------------
void CollectionParserSOK::disableCompression( void )
{
    m_EnableRLE = false;
}

// --------------------------------------------------------------
void CollectionParserSOK::_save( std::ofstream& file, const Collection& collection )
{

    // write all levels to file stream
    file << "Collection: " << collection.getName() << std::endl;
    RLE rle;
    for( Collection::const_level_iterator it = collection.level_begin(); it != collection.level_end(); ++it )
    {

        // header data contains all unformatted text read in from the file (including comments)
        (*it)->streamAllHeaderData( file );

        // place level name above tile data between two empty lines
        file << std::endl << (*it)->getLevelName() << std::endl << std::endl;

        // write tile data with optional RLE compression
        std::stringstream ss;
        (*it)->streamInitialTileData( ss, !m_EnableRLE );
        std::string compressed = ss.str();
        if( m_EnableRLE ) rle.multiPassCompress( compressed );
        file << compressed;

        // add meta data below tile data
        (*it)->streamAllMetaData( file );

        // save snapshot
        if( (*it)->undoDataExists() || (*it)->redoDataExists() )
            file << "Snapshot: " << (*it)->exportUndoData() << std::endl;

    }
}

} // namespace Chocobun
