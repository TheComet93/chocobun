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

#include "Matrix.hxx"

namespace Chocobun {

// --------------------------------------------------------------
template <class T>
Array2D<T>::Array2D( void ) :
    m_DefaultContent( T() ),
    m_SizeX(0),
    m_SizeY(0)
{
}

// --------------------------------------------------------------
template <class T>
Array2D<T>::Array2D( const T& content ) :
    m_DefaultContent( content ),
    m_SizeX(0),
    m_SizeY(0)
{
}

// --------------------------------------------------------------
template <class T>
Array2D<T>::Array2D( const Array2D& cp ) :
    m_DefaultContent( cp.m_DefaultContent ),
    m_SizeX( cp.m_SizeX ),
    m_SizeY( cp.m_SizeY ),
    m_Array( cp.m_Array )
{
}

// --------------------------------------------------------------
template <class T>
Array2D<T>::Array2D( const Array2D& cp, const T& content ) :
    m_DefaultContent( content ),
    m_SizeX( cp.m_SizeX ),
    m_SizeY( cp.m_SizeY ),
    m_Array( cp.m_Array )
{
}

// --------------------------------------------------------------
template <class T>
Array2D<T>::~Array2D( void )
{
}

// --------------------------------------------------------------
template <class T>
void Array2D<T>::setDefaultContent( const T& content )
{
    m_DefaultContent = content;
}

// --------------------------------------------------------------
template <class T>
const T& Array2D<T>::getDefaultContent( void ) const
{
    return m_DefaultContent;
}

// --------------------------------------------------------------
template <class T>
void Array2D<T>::resize( const std::size_t& x, const std::size_t& y )
{

    // scale x-dimension up or down
    if( x != m_SizeX )
    {
        m_Array.resize( x );
        while( x > m_SizeX )
        {
            m_Array[m_SizeX].resize( m_SizeY, m_DefaultContent );
            ++m_SizeX;
        }
        m_SizeX = x;
    }

    // scale y-dimension up or down
    if( y != m_SizeY )
    {
        for( typename std::vector< std::vector<T> >::iterator it = m_Array.begin(); it != m_Array.end(); ++it )
        {
            it->resize( y, m_DefaultContent );
        }
        m_SizeY = y;
    }
}

// --------------------------------------------------------------
template <class T>
const std::size_t& Array2D<T>::sizeX( void ) const
{
    return m_SizeX;
}

// --------------------------------------------------------------
template <class T>
const std::size_t& Array2D<T>::sizeY( void ) const
{
    return m_SizeY;
}

// --------------------------------------------------------------
template <class T>
std::vector<T>& Array2D<T>::operator[]( const std::size_t& index )
{
    return m_Array[index];
}

// --------------------------------------------------------------
template <class T>
const std::vector<T>& Array2D<T>::operator[]( const std::size_t& index ) const
{
    return m_Array[index];
}

} // namespace Chocobun
