#pragma once

//  colormaps from [1], great job guys!

/*
    [9] https://github.com/BIDS/colormap

    mpl-colormaps by Nathaniel Smith & Stefan van der Walt

    To the extent possible under law, the persons who associated CC0 with
    mpl-colormaps have waived all copyright and related or neighboring rights
    to mpl-colormaps.

    You should have received a copy of the CC0 legalcode along with this
    work. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include "vivid/types.h"
#include <vector>

namespace vivid {


class ColorMap
{
    public:

        enum Preset {
            PresetBlueYellow,
            PresetCoolWarm,
            PresetInferno,
            PresetMagma,
            PresetPlasma,
            PresetRainbow,
            PresetHsl,
            PresetHslPastel,
            PresetViridis,
            PresetVivid
        };

        enum Interpolation {
            InterpolationNearest,
            InterpolationLinear,
            InterpolationHsv,
            InterpolationHsl,
            InterpolationLch
        };

        ColorMap() = default;
        ColorMap( const Preset type );
        ColorMap( const std::string& file );

        bool empty() const { return stops_.empty(); }
        size_t numStops() const { return stops_.size(); }
        col_t at( const float t ) const;
        const std::vector<col_t>& stops() const { return stops_; }

        Interpolation interpolation = InterpolationLinear;

        static std::string nameForPreset( const Preset type );

    private:

        static std::vector<col_t> loadFromFile( const std::string& filename );
        std::vector<col_t> stops_;
};


}   //  ::vivid
