#ifndef ICON_H
#define ICON_H

#include <QWidget>

class Icon : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit Icon(QWidget *parent = 0);
    ~Icon();

    void setPenColor(const QColor &newColor);
    QColor penColor();

    void setIconImage(const QImage &newImage);
    QImage iconImage();

    void setZoomFactor(int newZoom);
    int zoomFactor();

    QSize sizeHint() const;

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

//     QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    int zoom;
    QImage image;
    QColor curColor;
};

#endif // ICON_H
