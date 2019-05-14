#include "contactimage.h"
#include "mauiandroid.h"
#include <QDebug>

ContactImage::ContactImage() : QQuickImageProvider(QQuickImageProvider::Image)
{
    this->no_image = QImage(":/portrait.jpg");
       this->blockSignals(false);
}

QImage ContactImage::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug()<< "requesting contact image with id "<< id;

    QImage result = MAUIAndroid::contactPhoto(id);

       if(result.isNull()) {
           result = this->no_image;
       }

       if(size) {
           *size = result.size();
       }

       if(requestedSize.width() > 0 && requestedSize.height() > 0) {
           result = result.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
       }

       return result;
}

void ContactImage::updateImage(const QImage &image)
{
    if(this->image != image) {
          this->image = image;
          emit imageChanged();
      }
}