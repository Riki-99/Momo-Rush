#include "loader.h"
#include "player.h"
#include "map.h"

Txt tiletxtr("./Assets/oak-resources/oak_woods_tileset.png");
void loadAllTextures() {
	TextureList<Background>::addTexture("./Assets/oak-resources/background/background_layer_1.png");
	TextureList<Background>::addTexture("./Assets/oak-resources/background/background_layer_2.png");
	TextureList<Background>::addTexture("./Assets/oak-resources/background/background_layer_3.png");
	TextureList<Player>::addTexture("./Assets/character-resources/png/blue/char_blue_1.png");
	TextureList<Enemy>::addTexture("./Assets/character-resources/png/red/char_red_1.png");
	TextureList<Tile>::addTexture("./Assets/oak-resources/oak_woods_tileset.png");

	/*standardTiles.push_back(Tile(0, 4, 0, 1, 1, 24));
	standardTiles.push_back(Tile(0, 12, 0, 1, 1, 24));
	standardTiles.push_back(Tile(0, 10, 0, 1, 1, 24));
	standardTiles.push_back(Tile(0, 15, 0, 1, 1, 24));
	standardTiles.push_back(Tile(0, 0, 11, 1, 1, 24));*/
}

    Element::Element(int index, int xthIdx, int ythIdx, int width, int height, int size, Txt& ref) : sprite(ref) {
        sprite.setTextureRect(intrect(
            { xthIdx * size, ythIdx * size },
            { size * width, size * height }
        ));
        sprite.setScale({ static_cast<float>(gd::tilesize / size), static_cast<float>(gd::tilesize / size) });
        hitbox = sprite.getGlobalBounds();
    }
    // Set position using absolute value
    void Element::setPosition(vec2f position) {
        sprite.setPosition(position);
        hitbox = sprite.getGlobalBounds();
    }
    // Set on tiles (world coords)
    void Element::setOnTile(int tileX, int tileY)
    {
        setPosition({ tileX * gd::tilesize, tileY * gd::tilesize });
    }

    // Draw on a sf::RenderWindow
    // cameraOffsetPx = how many pixels the world should be shifted to the left (camera world x - screen anchor x)
    void Element::draw(rw& window, float cameraOffsetPx) {
        Sprt newsprite = sprite;
        newsprite.move({ -cameraOffsetPx, 0.f });
        window.draw(newsprite);
    }

    floatrect Element::getHitBox() {
        return hitbox;
    }