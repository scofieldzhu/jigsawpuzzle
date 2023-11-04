/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: controlpanel.cpp 
CreateTime: 2019-6-18 22:04
=========================================================================*/
#include "controlpanel.h"
#include <QBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "controlpanelmediator.h"
#include "uiglo.h"
#include "appconf.h"

ControlPanel::ControlPanel(QWidget* parent, int32_t fixedwidth)
	:QWidget(parent)
{
    ui.setupUi(this);
// 	setFixedWidth(fixedwidth);
// 	createControls();
	mediator = new ControlPanelMediator(this);
	mediator->subscribeEvents();
}

ControlPanel::~ControlPanel()
{}

void ControlPanel::createControls()
{
	QVBoxLayout* mainlayout = new QVBoxLayout();
	mainlayout->setContentsMargins(10, 10, 10, 10);
	mainlayout->setSpacing(10);

	QHBoxLayout* row1layout = new QHBoxLayout();
	row1layout->setContentsMargins(0, 0, 0, 0);
	row1layout->setSpacing(0);
	originimglabel = new QLabel();
	originimglabel->setFixedSize({40, 20});
	originimglabel->setText(QObject::tr("Origin Image"));
	originimglabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	originimgcb = new QComboBox();	
	row1layout->addWidget(originimglabel);
	row1layout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Ignored));
	row1layout->addWidget(originimgcb);
	mainlayout->addLayout(row1layout);

	QHBoxLayout* row2layout = new QHBoxLayout();
	row2layout->setContentsMargins(0, 0, 0, 0);
	row2layout->setSpacing(0);
	difficultylabel = new QLabel();
	difficultylabel->setFixedSize(originimglabel->size());
	difficultylabel->setText(QObject::tr("Difficulty"));
	difficultylabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	difficultycb = new QComboBox();
    const AppConf& appconf = GetAppConf();
    for(auto level : appconf.gamelevels)
        difficultycb->addItem(QString::fromUtf8(level.name.cstr()));	
    difficultycb->setCurrentIndex(0);
	row2layout->addWidget(difficultylabel);
	row2layout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Ignored));
	row2layout->addWidget(difficultycb);
	mainlayout->addLayout(row2layout);

	QVBoxLayout* cmdbtnlayout = new QVBoxLayout();
	cmdbtnlayout->setContentsMargins(20, 20, 10, 0);
	cmdbtnlayout->setSpacing(10);

	startgametbtn = new QPushButton();
	//startgametbtn->setFixedSize(200, 80);
    startgametbtn->setFixedSize(112, 48);
	startgametbtn->setText(QObject::tr("Start Game"));
	cmdbtnlayout->addWidget(startgametbtn);

	giveupbtn = new QPushButton();
	giveupbtn->setFixedSize(200, 80);	
	giveupbtn->setText(QObject::tr("Give Up"));
	giveupbtn->setDisabled(true);
	cmdbtnlayout->addWidget(giveupbtn);

	hintbtn = new QPushButton();	
	hintbtn->setFixedSize(200, 80);
	hintbtn->setText(QObject::tr("Hint"));
	hintbtn->setDisabled(true);
	cmdbtnlayout->addWidget(hintbtn);
	
	mainlayout->addLayout(cmdbtnlayout);

	QHBoxLayout* lastrowlayout = new QHBoxLayout();
	lastrowlayout->setContentsMargins(0, 0, 0, 0);
	lastrowlayout->setSpacing(0);
	timelabel = new QLabel();
	timelabel->setFixedSize(originimglabel->size());
	timelabel->setText(QObject::tr("Cost Time:"));
	timelabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	timevallabel = new QLabel();
	timevallabel->setText("01:10:00 ms");
	lastrowlayout->addWidget(timelabel);
	lastrowlayout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Ignored));
	lastrowlayout->addWidget(timevallabel);
	mainlayout->addLayout(lastrowlayout);

	mainlayout->addStretch();

	setLayout(mainlayout);
}

void ControlPanel::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
