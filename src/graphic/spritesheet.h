#ifndef SPRITETILE_H
#define SPRITETILE_H

#include <vector>

#include "resource.h"
#include "texture2d.h"

#include "sprite2d.h"
#include "tracker_ptr.h"

namespace gdf {
namespace graphic {


class SpriteSheet    : public Resource
{
    public:
        SpriteSheet();
        SpriteSheet(const SpriteSheet& sprt_tile);
        ~SpriteSheet();

    public:
        void init( gdf::kernel::tracker_ptr<Texture2D> tex, int line_count, int col_count);
        void init( gdf::kernel::tracker_ptr<Texture2D> tex, int line_count, int col_count, int sprite_count);

    private:
        int sprite_count;
        int column_count;
        int row_count;
        int width;
        int height;

    public:
        //! The default origin for the the tile ( common ? °
        sf::Vector2f pivot_;

    public:
        std::vector< sf::IntRect > sheet_boundaries;

    public:
        gdf::kernel::tracker_ptr< Texture2D > texutre2d;
};

}}

#endif // SPRITETILE_H
