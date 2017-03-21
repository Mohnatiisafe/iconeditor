#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QMainWindow>
#include <QComboBox>
#include "icon.h"

namespace Ui {
class IconEditor;
}

class IconEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit IconEditor(QWidget *parent = 0);
    ~IconEditor();

public slots:
    void comboxIndex(int comboIndex);

private slots:
    void iconColor();

    void on_action_Exit_triggered();

    void on_action_Save_triggered();

private:
    void updateColor(QColor &curColor);
    void createAction();

private:
    Ui::IconEditor *ui;
    Icon *editor;
    QAction *colorAction;

    QComboBox *comZoom;
};

#endif // ICONEDITOR_H
