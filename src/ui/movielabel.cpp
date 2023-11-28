#include "movielabel.h"
#include <QPainter>
#include <QStyle>
#include <QMovie>

MovieLabel::MovieLabel(QWidget* parent)
    :QLabel(parent)
{}

MovieLabel::~MovieLabel()
{}

void MovieLabel::paintEvent(QPaintEvent *)
{
    QStyle *style = QWidget::style();
    QPainter painter(this);
    QRect cr = contentsRect();
    cr.adjust(margin(), margin(), -margin(), -margin());
    int align = QStyle::visualAlignment(text() == "" ? Qt::LeftToRight : layoutDirection(), alignment());
     if(movie()){
         if(hasScaledContents())
             style->drawItemPixmap(&painter, cr, align, movie()->currentPixmap().scaled(cr.size()));
         else
             style->drawItemPixmap(&painter, cr, align, movie()->currentPixmap());
     }
}
