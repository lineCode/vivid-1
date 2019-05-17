#include "vivid/conversion.h"

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>

namespace vivid::hsv {


////////////////////////////////////////////////////////////////////////////////
//  r: [0, 1], g: [0, 1], b: [0, 1]
//  [2] https://www.cs.rit.edu/~ncs/color/t_convert.html
////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb )
{
    const float r = rgb.x;
    const float g = rgb.y;
    const float b = rgb.z;

    const float cmax = glm::max( glm::max( r, g ), b );
    const float cmin = glm::min( glm::min( r, g ), b );
    const float delta = cmax - cmin;

    col_t hsv = { 0.f, 0.f, cmax };

    if ( cmax != 0.f ) {
        hsv.y = delta / cmax;
    } else {
        hsv.x = 0;
        hsv.y = 0;
        return hsv;
    }

    if ( glm::epsilonEqual( r, cmax, glm::epsilon<float>() ) ) {
        hsv.x = ( g - b ) / delta;		// between yellow & magenta
    } else if ( glm::epsilonEqual( g, cmax, glm::epsilon<float>() ) ) {
        hsv.x = 2 + ( b - r ) / delta;	// between cyan & yellow
    } else {
        hsv.x = 4 + ( r - g ) / delta;	// between magenta & cyan
    }

    hsv.x /= 6.f;   // to degrees
    hsv.x = std::fmodf( hsv.x + 1.f, 1.f );

    return hsv;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHsl( const col_t& hsl ) {
    return hsv::fromRgb( rgb::fromHsl( hsl ) );
}


}   //  ::vivid::hsv

