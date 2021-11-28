#include "TextureManager.h"

using namespace std;
// Re-declaring the variable so the file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	// if texture doesn't exist.. load it first
	if (textures.find(textureName) == textures.end()) { // cannot find texture
		LoadTexture(textureName);
	}
	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear(); // gets rid of all stored objects
}