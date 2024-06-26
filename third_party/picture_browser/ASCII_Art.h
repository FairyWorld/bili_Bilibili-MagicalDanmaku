#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <QPixmap>
#include <QPainter>

class ASCIIArt
{
public:
    const int limit_max_pixmap_cache = 5;
    char toChar(int g)
    {
        int one = 30; // 通用
        // one = 24; // 人像（偏白）
        int val = g / one;
        if (val == 1) {
            return '#';
        }
        else if (val == 2) {
            return '&';
        }
        else if (val == 3 || val == 4) {
            return '$';
        }
        else if (val == 5) {
            return '*';
        }
        else if (val == 6) {
            return 'o';
        }
        else if (val == 7) {
            return '!';
        }
        else {
            return ' ';
        }
    }

    int rgbtoGray(int r, int g, int b)
    {
        return (int)((((quint32)((r << 5) + (r << 2) + (r << 1))) + (quint32)((g << 6) + (g << 3) + (g << 1) + g)
            + (quint32)((b << 4) - b)) >> 7);
    }

    QPixmap setImage(const QImage &image, QColor bg = Qt::transparent)
    {
        const int ih = image.height();
        const int iw = image.width();

        QPixmap txtImage(iw, ih);
        txtImage.fill(bg);
        QPainter painter(&txtImage);
        painter.setBrush(Qt::NoBrush);
        // painter.setPen(QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200));
        painter.setPen(Qt::darkGray);
        QFont font = painter.font();
        font.setPixelSize(7);
        font.setFamily("Microsoft YaHei");
        painter.setFont(font);

        for (int i = 0; i < iw; i+= 7)
        {
            for (int j = 0; j < ih; j+= 7)
            {
                const QRgb&& pixel = image.pixel(i, j);
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);
                int gray = rgbtoGray(r, g, b);
                char c = toChar((int)gray);
                painter.drawText(i, j, QChar(c));
            }
        }
        return txtImage;
    }

};

#endif // ASCII_ART_H
