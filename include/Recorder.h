#pragma once

#include <Arduino.h>
#include <Audio.h>
#include <SD.h>

class Recorder
{
public:

    bool begin();

    bool start(const char* filename);

    void stop();

    void update();

    bool isRecording() const;

private:

    AudioInputI2S           m_input;
    AudioRecordQueue        m_queue;

    AudioConnection         m_patchCord{m_input, 0, m_queue, 0};

    File m_file;

    bool m_recording = false;

    uint32_t m_dataSize = 0;

    void writeWavHeader();
    void updateWavHeader();

    elapsedMillis m_recordTimer;

    uint32_t m_maxRecordTime = 180000; 
};