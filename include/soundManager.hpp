#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>

class SoundManager {
public:
    SoundManager();
    bool loadSound(const std::string &name, const std::string &filePath);
    void playSound(const std::string &name);
    void setVolume(float volume);

private:
    // Store sound buffers and sounds in maps for easy access
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
};
