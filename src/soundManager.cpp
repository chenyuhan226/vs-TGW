#include "soundManager.hpp"

SoundManager::SoundManager() {
    // set default volume for all sounds
    setVolume(70.f);
}

bool SoundManager::loadSound(const std::string &name, const std::string &filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error loading sound from " << filePath << std::endl;
        return false;
    }
    // 将加载成功的 buffer 拷贝到 map 中
    soundBuffers[name] = buffer;
    // 为该 buffer 创建对应的 sf::Sound 对象
    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = sound;
    return true;
}

void SoundManager::playSound(const std::string &name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    } else {
        std::cerr << "Sound " << name << " not found!" << std::endl;
    }
}

void SoundManager::setVolume(float volume) {
    for (auto &pair : sounds) {
        pair.second.setVolume(volume);
    }
}
