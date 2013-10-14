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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Chocobun. If not, see <http://www.gnu.org/licenses/>.
*/

// --------------------------------------------------------------
// include files

#include <iostream>
#include <vector>

namespace Chocobun {

/*!
 * @brief Wraps a dynamic 2-dimensional array with std::vector< std::vector<T> > at its core
 */
template <class T>
class Array2D
{
public:

    /*!
     * @brief Default constructor
     */
    Array2D( void );

    /*!
     * @brief Constructor setting the default content of the array
     * see @a setDefaultContent for more information
     * @param content The content to use
     */
    Array2D( const T& content );

    /*!
     * @brief Copy Constructor
     * @param cp The other 2D array to copy
     */
    Array2D( const Array2D& cp );

    /*!
     * @brief Copy Constructor with setting the default content of the array
     */
    Array2D( const Array2D& cp, const T& content );

    /*!
     * @brief Default destructor
     */
    ~Array2D( void );

    /*!
     * @brief Sets the default initial content of the array
     * Sets what content should be inserted into the array
     * when first allocated or cleared.
     * @param content The content to use
     */
    void setDefaultContent( const T& content );

    /*!
     * @brief Retrieves the default content of the array
     */
    const T& getDefaultContent( void ) const;

    /*!
     * @brief Resizes the Array2D to the specified dimensions
     * @param x The new x-size
     * @param y The new y-size
     */
    void resize( const std::size_t& x, const std::size_t& y );

    /*!
     * @brief Subscript operator overload
     * Enables the use of writing to the Array2D using [][]
     */
    std::vector<T>& operator[]( const std::size_t& index );

    /*!
     * @brief Subscript operator overload
     * Enables the use of reading from the Array2D using [][]
     */
    const std::vector<T>& operator[]( const std::size_t& index ) const;
 
    void output( void )
    {
        for( typename std::vector< std::vector<T> >::iterator itx = m_Array.begin(); itx != m_Array.end(); ++itx )
            for( typename std::vector<T>::iterator ity = itx->begin(); ity != itx->end(); ++ity )
                std::cout << *ity;
        std::cout << std::endl;
    }

private:

    T                               m_DefaultContent;
    std::vector< std::vector<T> >   m_Array; // NOTE: outer vector: x-dimension, inner vector: y-dimension
    std::size_t                     m_SizeX;
    std::size_t                     m_SizeY;
};

} // namespace Chocobun
