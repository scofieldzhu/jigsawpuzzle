#pragma once
#include <QLabel>

class MovieLabel : public QLabel
{
    Q_OBJECT
public:
    MovieLabel(QWidget* parent = NULL);
    ~MovieLabel();
    
private:
    void paintEvent(QPaintEvent *) override;
};

