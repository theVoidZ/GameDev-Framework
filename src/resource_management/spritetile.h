#ifndef SPRITETILE_H
#define SPRITETILE_H

#include <vector>

#include "resource_management/resource.h"

class SpriteTile    : public Resource
{
    Q_OBJECT
    public:
        SpriteTile();
        SpriteTile(const SpriteTile& sprt_tile);
        ~SpriteTile();

    public:
        void init(std::string file_name, int line_count, int col_count);
        void init(std::string file_name, int line_count, int col_count, int sprite_count);

    private:
        int sprite_count;
        int column_count;
        int row_count;
        int width;
        int height;

        sf::Image img_buffer;

    public:
        std::vector< sf::Texture* > tex_tile;
};

#endif // SPRITETILE_H
