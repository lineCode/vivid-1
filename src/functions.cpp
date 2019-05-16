#include "vivid/functions.h"
#include "vivid/conversion.h"
#include "vivid/stream.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace tq::rgb {


////////////////////////////////////////////////////////////////////////////////
col_t lerp( const col_t& rgb1, const col_t& rgb2, const float t ) {
    return glm::mix( rgb1, rgb2, t );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHsv(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t hsv1 = hsv::fromRgb( rgb1 );
    col_t hsv2 = hsv::fromRgb( rgb2 );

    if ( std::abs( hsv1.x - hsv2.x ) > 0.5f )
    {
        if( hsv1.x > hsv2.x ) {
            hsv1.x -= 1.0f;
        } else {
            hsv1.x += 1.0f;
        }
    }

    col_t hsv = glm::mix( hsv1, hsv2, t );
    hsv.x = std::fmodf( hsv.x, 1.0f );

    return rgb::fromHsv( hsv );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHsl(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t hsl1 = hsl::fromRgb( rgb1 );
    col_t hsl2 = hsl::fromRgb( rgb2 );

    if ( std::abs( hsl1.x - hsl2.x ) > 0.5f )
    {
        if( hsl1.x > hsl2.x ) {
            hsl1.x -= 1.0f;
        } else {
            hsl1.x += 1.0f;
        }
    }

    col_t hsl = glm::mix( hsl1, hsl2, t );
    hsl.x = std::fmodf( hsl.x, 1.0f );

    return rgb::fromHsl( hsl );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHcl(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t lch1 = hcl::fromRgb( rgb1 );
    col_t lch2 = hcl::fromRgb( rgb2 );

    col_t delta = lch2 - lch1;

    if ( delta.z > glm::pi<float>() ) {
        delta.z -= glm::two_pi<float>();
    } else if ( delta.z < - glm::pi<float>() ) {
        delta.z += glm::two_pi<float>();
    }

    col_t lch = lch1 + t * delta;

    return rgb::fromHcl( lch );
}


////////////////////////////////////////////////////////////////////////////////
// input 0..255 for rainbow colors!
col_t rainbow( const int c )
{
    const int k = c % 255;
    col_t col;

    if ( k < 42 ) {
        col.x = 255;
        col.y = float( k * 6 );
        col.z = 0;
    } else if ( k < 2 * 42 ) {
        col.x = float( 42 - ( k - 42 ) ) * 6;
        col.y = 255;
        col.z = 0;
    } else if ( k < 3 * 42 ) {
        col.x = 0;
        col.y = 255;
        col.z = float( k - 2 * 42 ) * 6;
    } else if ( k < 4 * 42 ) {
        col.x = 0;
        col.y = ( 42 - float( k - 3 * 42 ) ) * 6;
        col.z = 255;
    } else if ( k < 5 * 42 ) {
        col.x = float( k - 4 * 42 ) * 6;
        col.y = 0;
        col.z = 255;
    } else if ( k < 6 * 42 ) {
        col.x = 255;
        col.y = 0;
        col.z = ( 42 - float( k - 5 * 42 ) ) * 6;
    } else {
        col.x = 255;
        col.y = 0;
        col.z = 0;
    }

    return col / 255.0f;
}


////////////////////////////////////////////////////////////////////////////////
col_t saturate( const col_t& rgb )
{
    auto res = rgb;

    res.x = glm::clamp( rgb.x, 0.f, 1.f );
    res.y = glm::clamp( rgb.y, 0.f, 1.f );
    res.z = glm::clamp( rgb.z, 0.f, 1.f );

    return res;
}


////////////////////////////////////////////////////////////////////////////////
col_t clamp( const col_t& rgb ) {
    return tq::rgb::fromIndex( tq::index::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t spaceRoundtrip( const col_t& rgb_1 )
{
    const col_t xyz_1 = xyz::fromRgb( rgb_1 );
    const col_t lab_1 = lab::fromXyz( xyz_1 );
    const col_t lch_1 = hcl::fromLab( lab_1 );
    const col_t lab_2 = lab::fromHcl( lch_1 );
    const col_t xyz_2 = xyz::fromLab( lab_2 );
    const col_t rgb_2 = rgb::fromXyz( xyz_2 );

    std::cout << "color space roundtrip test" << std::endl;
    std::cout << "rgb_1: " << rgb_1 << std::endl;
    std::cout << "xyz_1: " << xyz_1 << std::endl;
    std::cout << "lab_1: " << lab_1 << std::endl;
    std::cout << "lch_1: " << lch_1 << std::endl;
    std::cout << "lab_2: " << lab_2 << std::endl;
    std::cout << "xyz_2: " << xyz_2 << std::endl;
    std::cout << "rgb_2: " << rgb_2 << std::endl;
    std::cout << std::endl;

    return rgb_2;
}


////////////////////////////////////////////////////////////////////////////////
col_t typeRoundtrip( const col_t& rgb1 )
{
    const auto rgb8 = rgb8::fromRgb( rgb1 );
    const auto rgb_2 = rgb::fromRgb8( rgb8 );

    std::cout << "color type roundtrip test" << std::endl;
    std::cout << "rgb_1: " << rgb1 << std::endl;
    std::cout << "rgb8:  " << rgb8 << std::endl;
    std::cout << "rgb_2: " << rgb_2 << std::endl;
    std::cout << std::endl;

    return rgb_2;
}


}   //  ::tq::rgb
