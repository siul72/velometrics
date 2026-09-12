#include "VideoRenderService.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QDebug>
#include "../../velometrics-designer/Canvas/CanvasScene.h"
#include "../VelometricsCore.h"


VideoRenderService::VideoRenderService(QObject* parent): QObject(parent){
}

VideoRenderService::~VideoRenderService(){
    end();
}

bool VideoRenderService::render(CanvasScene* scene, const int startIndex, const int endIndex, const QString& outputFile){

    if (!scene){
        qCritical() << "Invalid scene";
        return false;
    }

    if (!begin(outputFile, 3840, 2160, 25)){

        return false;
    }

    for (QGraphicsItem* item : scene->items()){
        item->setSelected(false);
    }
    scene->setHelpersVisible(false);
    scene->update();

    for (int index = startIndex; index <= endIndex;++index){
        VelometricsCore::instance().setPlaybackPosition(index);
        QApplication::processEvents();
        QApplication::sendPostedEvents();

        const QImage frame = scene->renderFrame(QSize(m_width, m_height),Qt::black);

        for (int i = 0; i < m_fps; ++i){
            if (!addFrame(frame)){
                qCritical()<< "Failed encoding frame";
                end();
                scene->setHelpersVisible(true);
                return false;
            }
        }
    }

    const auto rc = end();
    scene->setHelpersVisible(true);
    qDebug() << "Render finished " << "rc=" << rc;
    return rc;
}

bool VideoRenderService::begin(const QString& outputFile, const int width, const int height, const int fps)
{
    m_width = width;
    m_height = height;
    m_fps = fps;
    m_pts = 0;

    const AVCodec* codec =
        avcodec_find_encoder(AV_CODEC_ID_H264);

    if (!codec)
    {
        qCritical() << "Unable to find H264 encoder";
        return false;
    }

    if (avformat_alloc_output_context2(
            &m_formatContext,
            nullptr,
            "mp4",
            outputFile.toUtf8().constData()) < 0)
    {
        qCritical() << "Unable to create output context";
        return false;
    }

    m_stream =
        avformat_new_stream(
            m_formatContext,
            nullptr);

    if (!m_stream)
    {
        qCritical() << "Unable to create stream";
        return false;
    }

    m_codecContext =
        avcodec_alloc_context3(codec);

    if (!m_codecContext)
    {
        qCritical() << "Unable to allocate codec";
        return false;
    }

    m_codecContext->codec_id = AV_CODEC_ID_H264;
    m_codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
    m_codecContext->pix_fmt = AV_PIX_FMT_YUV420P;

    m_codecContext->width = width;
    m_codecContext->height = height;

    m_codecContext->time_base = AVRational{1, fps};
    m_codecContext->framerate = AVRational{fps, 1};

    m_codecContext->gop_size = fps;
    m_codecContext->max_b_frames = 0;

    av_opt_set(
        m_codecContext->priv_data,
        "preset",
        "medium",
        0);

    av_opt_set(
        m_codecContext->priv_data,
        "crf",
        "18",
        0);

    if (m_formatContext->oformat->flags &
        AVFMT_GLOBALHEADER)
    {
        m_codecContext->flags |=
            AV_CODEC_FLAG_GLOBAL_HEADER;
    }

    int rc =
        avcodec_open2(
            m_codecContext,
            codec,
            nullptr);

    if (rc < 0)
    {
        qCritical() << "Unable to open codec";
        return false;
    }

    rc =
        avcodec_parameters_from_context(
            m_stream->codecpar,
            m_codecContext);

    if (rc < 0)
    {
        qCritical()
            << "Unable to copy codec params";
        return false;
    }

    m_stream->time_base =
        m_codecContext->time_base;

    rc =
        avio_open(
            &m_formatContext->pb,
            outputFile.toUtf8().constData(),
            AVIO_FLAG_WRITE);

    if (rc < 0)
    {
        qCritical()
            << "Unable to open output file";
        return false;
    }

    rc =
        avformat_write_header(
            m_formatContext,
            nullptr);

    if (rc < 0)
    {
        qCritical()
            << "Unable to write header";
        return false;
    }

    m_swsContext =
        sws_getContext(
            width,
            height,
            AV_PIX_FMT_BGRA,
            width,
            height,
            AV_PIX_FMT_YUV420P,
            SWS_BICUBIC,
            nullptr,
            nullptr,
            nullptr);

    return m_swsContext != nullptr;
}

bool VideoRenderService::flushEncoder() const{
    int rc = avcodec_send_frame(m_codecContext, nullptr);

    if (rc < 0) {
        return false;
    }

    while (true)
    {
        AVPacket* packet =
            av_packet_alloc();

        rc =
            avcodec_receive_packet(
                m_codecContext,
                packet);

        if (rc == AVERROR_EOF ||
            rc == AVERROR(EAGAIN))
        {
            av_packet_free(&packet);
            break;
        }

        if (rc < 0)
        {
            av_packet_free(&packet);
            return false;
        }

        av_packet_rescale_ts(
            packet,
            m_codecContext->time_base,
            m_stream->time_base);

        packet->stream_index =
            m_stream->index;

        av_interleaved_write_frame(
            m_formatContext,
            packet);

        av_packet_free(&packet);
    }

    return true;
}

bool VideoRenderService::end()
{
    if (!m_codecContext)
    {
        return true;
    }

    flushEncoder();

    av_write_trailer(
        m_formatContext);

    if (m_swsContext)
    {
        sws_freeContext(
            m_swsContext);
        m_swsContext = nullptr;
    }

    if (m_codecContext)
    {
        avcodec_free_context(
            &m_codecContext);
        m_codecContext = nullptr;
    }

    if (m_formatContext)
    {
        if (m_formatContext->pb)
        {
            avio_closep(
                &m_formatContext->pb);
        }

        avformat_free_context(
            m_formatContext);

        m_formatContext = nullptr;
    }

    m_stream = nullptr;

    return true;
}

bool VideoRenderService::addFrame(const QImage& image) {
    if (!m_codecContext || !m_formatContext || !m_stream || !m_swsContext){
        return false;
    }
    const QImage bgraImage = image.convertToFormat(QImage::Format_ARGB32);
    AVFrame* frame = av_frame_alloc();
    if (!frame) {
        return false;
    }

    frame->format = AV_PIX_FMT_YUV420P;
    frame->width = m_width;
    frame->height = m_height;
    frame->pts = m_pts++;

    if (av_frame_get_buffer(frame, 32) < 0) {
        av_frame_free(&frame);
        return false;
    }

    if (av_frame_make_writable(frame) < 0) {
        av_frame_free(&frame);
        return false;
    }

    const uint8_t* srcData[1] = { bgraImage.constBits()};
    const int srcStride[1] = {static_cast<int>(bgraImage.bytesPerLine())};
    sws_scale(m_swsContext,srcData,srcStride,0,m_height,frame->data,frame->linesize);
    const int rc = avcodec_send_frame( m_codecContext,frame);

    av_frame_free(&frame);

    if (rc < 0){
        qCritical()
            << "avcodec_send_frame failed:"
            << rc;

        return false;
    }

    while (true)
    {
        AVPacket* packet =
            av_packet_alloc();

        if (!packet)
        {
            return false;
        }

        const int result =
            avcodec_receive_packet(
                m_codecContext,
                packet);

        if (result == AVERROR(EAGAIN) ||
            result == AVERROR_EOF)
        {
            av_packet_free(&packet);
            break;
        }

        if (result < 0)
        {
            av_packet_free(&packet);

            qCritical()
                << "avcodec_receive_packet failed:"
                << result;

            return false;
        }

        av_packet_rescale_ts(
            packet,
            m_codecContext->time_base,
            m_stream->time_base);

        packet->stream_index =
            m_stream->index;

        const int writeRc =
            av_interleaved_write_frame(
                m_formatContext,
                packet);

        av_packet_free(&packet);

        if (writeRc < 0)
        {
            qCritical()
                << "av_interleaved_write_frame failed:"
                << writeRc;

            return false;
        }
    }

    return true;
}


