#pragma once

#include "Packet.h"
#include <QJsonObject>
#include <QImage>

enum class ImageChannel : unsigned int {
    DEFAULT_OR_DUAL_LINEAR,
    DUAL_CONVEX
};

class FramePacket : public Packet
{
public:
    FramePacket(const QImage& image, const ImageChannel& channel);
    virtual QByteArray toBinary() override;
    void printfSelf() override;
    QImage getImage() const;
    ImageChannel getImageChannel() const;

    static const QString IMAGE_CHANNEL;
protected:
    QJsonObject generateData() override;
private:
    QImage m_image;
    ImageChannel m_imageChannel;
};