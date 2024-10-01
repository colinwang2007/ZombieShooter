#include "TextureHolder.h"
#include <assert.h>
#include <iostream>
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    // ensure that m_s_Instance is equal to nullptr
    assert(m_s_Instance == nullptr);
    // assign the pointer to this instance
    m_s_Instance = this;

}
Texture& TextureHolder::GetTexture(string const& filename)
{
    auto& m = m_s_Instance->m_Textures;
    //cout<<"1"<<endl;
    auto keyValuePair = m.find(filename);
    //cout<<"2"<<endl;
    if (keyValuePair != m.end())
    {
        return keyValuePair->second;
    }
    else
    {
        auto& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}
//void addTextures(string str, Texture t){
//
//}

