#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 64

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData) {
    const float *in = (const float*)inputBuffer;
    float *out = (float*)outputBuffer;

    for (unsigned int i = 0; i < framesPerBuffer; i++) {
        out[i] = in[i];
    }

    return paContinue;
}

int main(void) {
    PaStream *stream;
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError) goto error;

    // добавить поддержку ASIO
    err = Pa_OpenDefaultStream(&stream,
                               1, // входной канал
                               1, // выходной канал
                               paFloat32, // формат
                               SAMPLE_RATE,
                               FRAMES_PER_BUFFER,
                               audioCallback,
                               NULL); // без пользовательских данных
    if (err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;

    printf("Сквозной звук запущен. Нажмите Enter для выхода...\n");
    getchar(); // ждём ввода Enter

    // Остановка и очистка
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    return 0;

error:
    fprintf(stderr, "Ошибка: %s\n", Pa_GetErrorText(err));
    Pa_Terminate();
    return -1;
}
