#include "iconeditor.h"
#include "ui_iconeditor.h"
#include <QtWidgets>

IconEditor::IconEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IconEditor)
{
    ui->setupUi(this);

    editor = new Icon();

    setCentralWidget(editor);
    createAction();

    statusBar()->showMessage("Чё ты смотришь!");

}

IconEditor::~IconEditor()
{
    delete ui;
}

void IconEditor::iconColor()
{
    QColor color = QColorDialog::getColor(editor->penColor(), this, tr("IconColor"));

    if (!color.isValid()) {
        return;
    }

    editor->setPenColor(color);
    updateColor(color);
}

void IconEditor::updateColor(QColor &curColor)
{
    QPixmap pix(16, 16);
    pix.fill(curColor);
    colorAction->setIcon(pix);
}

void IconEditor::createAction()
{
    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    colorAction = new QAction(pix, tr("&Color..."), this);
    connect(colorAction, &QAction::triggered, this, &IconEditor::iconColor);

    ui->menu_Edit->addAction(colorAction);
    ui->fileToolBar->addSeparator();
    ui->fileToolBar->addAction(colorAction);

    comZoom = new QComboBox(ui->zoomToolBar);
    comZoom->addItem("Copy.png");
    comZoom->addItem("Cut.png");
    comZoom->addItem("New.png");
    comZoom->addItem("Open.png");
    comZoom->addItem("Paste.png");
    comZoom->addItem("Save.png");
    //connect(cmBox, SIGNAL(activated(int)), this, SLOT(comboxIndex(int)));



    connect(comZoom, SIGNAL(activated(int)), this, SLOT(comboxIndex(int)));
    ui->zoomToolBar->addWidget(comZoom);
}

void IconEditor::on_action_Exit_triggered()
{
    qApp->quit();
}

void IconEditor::comboxIndex(int comboIndex)
{
    switch(comboIndex)
    {
    case 0:
        editor->setIconImage(QImage(":/images/copy.png"));
        break;
    case 1:
        editor->setIconImage(QImage(":/images/cut.png"));
        break;
    case 2:
        editor->setIconImage(QImage(":/images/new.png"));
        break;
    case 3:
        editor->setIconImage(QImage(":/images/open.png"));
        break;
    case 4:
        editor->setIconImage(QImage(":/images/paste.png"));
        break;
    case 5:
        editor->setIconImage(QImage(":/images/save.png"));
        break;
    default:
        break;
    }
}


void IconEditor::on_action_Save_triggered()
{
    QImage img(width(),height(),QImage::Format_RGB32);
    img.save("my2.jpg","JPG");
}
