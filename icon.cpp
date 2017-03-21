#include "icon.h"
#include <QtWidgets>

Icon::Icon(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    curColor = Qt::black;
    zoom = 16;

    image = QImage(32, 32, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
}

Icon::~Icon()
{

}

void Icon::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

QColor Icon::penColor()
{
    return curColor;
}

void Icon::setIconImage(const QImage &newImage)
{
    if ( newImage != image ) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}

QImage Icon::iconImage()
{
    return image;
}

void Icon::setZoomFactor(int newZoom)
{
    if ( newZoom < 1 ) {
        newZoom = 1;
    }
    if ( newZoom != zoom ) {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

int Icon::zoomFactor()
{
    return zoom;
}

QSize Icon::sizeHint() const
{
    QSize size = zoom * image.size();

    if ( zoom >=3 ) {
       size += QSize(1, 1);
    }

    return size;
}

void Icon::setImagePixel(const QPoint &pos, bool opaque)
{
    int i=pos.x() / zoom;
    int j=pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {
            image.setPixel(i, j, penColor().rgba());
        } else {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }
        update(pixelRect(i, j));
    }
}

QRect Icon::pixelRect(int i, int j) const
{
    if (zoom >= 3) {
        return QRect(zoom * i + 1, zoom *j + 1, zoom - 1, zoom - 1);
    } else {
        return QRect(zoom * i, zoom * j, zoom , zoom);
    }
}


void Icon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos().x() << " " << event->pos().y() << endl;
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void Icon::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void Icon::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (zoom >=3) {
        painter.setPen(palette().foreground().color());
        for (int i=0; i<=image.width(); ++i) {
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        }
        for (int j=0; j<=image.height(); ++j) {
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
        }
    }

    for (int i=0; i<image.width(); ++i) {
        for (int j=0; j<image.height(); ++j) {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255) {
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}
