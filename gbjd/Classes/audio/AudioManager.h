#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class AudioManager
{
public:
    enum SoundEffectType
    {
        SoundEffectJump,
        SoundEffectDie,
    };

public:
    static AudioManager *sharedAudioManager();
    
    void preloadBackgroundMusic(const char* pszFilePath);

    void playBackgroundMusic(const char* pszFilePath, bool bLoop);

    void playBackgroundMusic(const char* pszFilePath);

    void stopBackgroundMusic(bool bReleaseData);

    void stopBackgroundMusic();
    
    bool isBackgroundMusicPlaying();

    void preloadEffect(const char* pszFilePath);
    
    void preloadEffect(AudioManager::SoundEffectType se);

    unsigned int playEffect(const char* pszFilePath, bool bLoop);

    unsigned int playEffect(AudioManager::SoundEffectType se, bool bLoop);

    unsigned int playEffect(AudioManager::SoundEffectType se);
    
    const char *getEffectFilePath(AudioManager::SoundEffectType se);
};

#endif /* __AUDIO_MANAGER_H__ */
