/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: gamescene.cpp 
CreateTime: 2019-6-21 21:40
=========================================================================*/
#include "gamescene.h"
#include <QPainter>
#include <QGraphicsItem>

GameScene::GameScene(QObject* parent /*= Q_NULLPTR*/)
    :QGraphicsScene(parent)
{
    createNoticeBoard();
}

GameScene::GameScene(const QRectF& sceneRect, QObject* parent /*= Q_NULLPTR*/)
    :QGraphicsScene(sceneRect, parent)
{
    createNoticeBoard();
}

GameScene::GameScene(qreal x, qreal y, qreal width, qreal height, QObject* parent /*= nullptr*/)
	:QGraphicsScene(x, y, width, height)
{
    createNoticeBoard();
}

GameScene::~GameScene()
{
    removeItem(noticeboard_);
    delete noticeboard_;
    noticeboard_ = nullptr;
}

void GameScene::createNoticeBoard()
{
    noticeboard_ = new QGraphicsTextItem(nullptr);
    addItem(noticeboard_);
    noticeboard_->setDefaultTextColor(Qt::red);
    QFont ft(QStringLiteral("Î¢ÈíÑÅºÚ"));
    ft.setPixelSize(30);
    ft.setStyle(QFont::StyleNormal);
    ft.setBold(true);
    noticeboard_->setFont(ft); 
    noticeboard_->setVisible(false);
}

void GameScene::showNotice(const QString& text)
{    
    noticeboard_->setPlainText(text);
    noticeboard_->setVisible(true);
    update();
}

void GameScene::hideNotice()
{
    noticeboard_->setVisible(false);
    update();
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(!bkg_.isNull()) 
        painter->drawPixmap(rect, bkg_, bkg_.rect());
}
