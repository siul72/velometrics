#pragma once

#include <QObject>
#include <QImage>
#include <QString>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libavutil/opt.h>
}

class CanvasScene;

class VideoRenderService : public QObject
{
    Q_OBJECT

public:
    explicit VideoRenderService(QObject* parent = nullptr);
    ~VideoRenderService() override;

    bool render(
        CanvasScene* scene,
        int startIndex,
        int endIndex,
        const QString& outputFile);

    signals:
        void progressChanged(int currentFrame, int totalFrames);
    void completed();
    void failed(const QString& reason);

private:
    bool begin(
        const QString& outputFile,
        int width,
        int height,
        int fps);
    bool flushEncoder() const;

    bool addFrame(const QImage& image);

    bool end();

private:
    AVFormatContext* m_formatContext {};
    AVCodecContext* m_codecContext {};
    AVStream* m_stream {};
    SwsContext* m_swsContext {};

    int64_t m_pts {};

    int m_width {};
    int m_height {};
    int m_fps {};
};
