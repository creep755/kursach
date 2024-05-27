#include "record_audio.h"

int record(char *data, int length) {
    // Открываем устройство звука для записи
    snd_pcm_t *handle;
    snd_pcm_open(&handle, "plughw:1,0", SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK);

    // Устанавливаем параметры устройства звука
    snd_pcm_hw_params_t *params;
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 1);
    snd_pcm_hw_params_set_rate_near(handle, params, &(wav.sampleRate), 0);

    // Записываем звук
    snd_pcm_sframes_t frames;
    char *buffer = (char *)malloc(length);
    while (1) {
        frames = snd_pcm_readi(handle, buffer, length);
        if (frames < 0) {
            printf("Error reading from device: %s\n", snd_strerror(frames));
            break;
        }
        memcpy(data, buffer, frames);
    }

    // Закрываем устройство звука
    snd_pcm_close(handle);

    return 0;
}