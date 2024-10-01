#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;
class TextureHolder
{
private:
    static TextureHolder* m_s_Instance;
    map <string, Texture> m_Textures;

public:
    TextureHolder();
//    void addTextures(string str, Texture t);
    static Texture& GetTexture(string const& filename);


};
#endif
