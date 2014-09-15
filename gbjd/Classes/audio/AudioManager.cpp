#include "AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

AudioManager *AudioManager::sharedAudioManager()
{
    static AudioManager s_audioManager;
    return &s_audioManager;
}

void AudioManager::preloadBackgroundMusic(const char* pszFilePath)
{
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(pszFilePath);
}

void AudioManager::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, bLoop);
}

void AudioManager::playBackgroundMusic(const char* pszFilePath)
{
    this->playBackgroundMusic(pszFilePath, true);
}

void AudioManager::stopBackgroundMusic(bool bReleaseData)
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
}

void AudioManager::stopBackgroundMusic()
{
    this->stopBackgroundMusic(true);
}

bool AudioManager::isBackgroundMusicPlaying()
{
    return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void AudioManager::preloadEffect(const char* pszFilePath)
{
    SimpleAudioEngine::sharedEngine()->preloadEffect(pszFilePath);
}

void AudioManager::preloadEffect(AudioManager::SoundEffectType se)
{
    const char *pszFilePath = this->getEffectFilePath(se);
    if (pszFilePath)
    {
        this->preloadEffect(pszFilePath);
    }
}

unsigned int AudioManager::playEffect(const char* pszFilePath, bool bLoop)
{
    return SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath, bLoop);
}

unsigned int AudioManager::playEffect(AudioManager::SoundEffectType se, bool bLoop)
{
    const char *pszFilePath = getEffectFilePath(se);
    if (pszFilePath)
    {
        return this->playEffect(pszFilePath, bLoop);
    }
    else
    {
        return 0;
    }
}

unsigned int AudioManager::playEffect(AudioManager::SoundEffectType se)
{
    return this->playEffect(se, false);
}

const char *AudioManager::getEffectFilePath(AudioManager::SoundEffectType se)
{
    char *filename = NULL;
    switch (se)
    {
        case AudioManager::SoundEffectJump:
            filename = "Audio_jump.mp3";
            break;
        case AudioManager::SoundEffectDie:
            filename = "Audio_boos.mp3";
            break;
    }
    return filename;
}
