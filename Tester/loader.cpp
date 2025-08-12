#include "loader.h"
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

