#include "Recorder.h"

#include "Logger.h"

bool Recorder::begin()
{
    return true;
}

bool Recorder::start(const char* filename)
{
    if(m_recording)
        return false;
    m_recordTimer = 0;
    Logger::info("Recording...");

    m_file = SD.open(filename, FILE_WRITE);

    if(!m_file)
    {
        Logger::error("Cannot create recording.");
        return false;
    }

    writeWavHeader();

    m_dataSize = 0;

    m_queue.begin();

    m_recording = true;

    return true;
}

void Recorder::stop()
{
    if(!m_recording)
        return;

    m_queue.end();

    while(m_queue.available())
    {
        byte *buffer = (byte*)m_queue.readBuffer();

        m_file.write(buffer,256);

        m_dataSize += 256;

        m_queue.freeBuffer();
    }

    updateWavHeader();

    m_file.close();

    m_recording = false;

    Logger::info("Recording finished.");
}

void Recorder::update()
{
    if(!m_recording)
    return;
    
    if(m_recordTimer > m_maxRecordTime)
    {
        Logger::info("Maximum recording time reached.");
        stop();
        return;
    }

    while(m_queue.available() >= 2)
    {
        byte *buffer = (byte*)m_queue.readBuffer();

        m_file.write(buffer,256);

        m_dataSize += 256;

        m_queue.freeBuffer();
    }
}

bool Recorder::isRecording() const
{
    return m_recording;
}

void Recorder::writeWavHeader()
{
    uint8_t header[44] =
    {
        'R','I','F','F',
        0,0,0,0,
        'W','A','V','E',
        'f','m','t',' ',
        16,0,0,0,
        1,0,
        1,0,
        0x44,0xAC,0x00,0x00,
        0x88,0x58,0x01,0x00,
        2,0,
        16,0,
        'd','a','t','a',
        0,0,0,0
    };

    m_file.write(header,44);
}

void Recorder::updateWavHeader()
{
    uint32_t fileSize = m_dataSize + 36;

    m_file.seek(4);
    m_file.write((uint8_t*)&fileSize,4);

    m_file.seek(40);
    m_file.write((uint8_t*)&m_dataSize,4);
}