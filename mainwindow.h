#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class Renderer;
class TileManager;
class TileMgrDataModel;
class TileDataModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addtile();

    void testClicked(const QModelIndex index);
    void updateTileManager();
signals:
    void needRepaint();
private:
    Ui::MainWindow *ui;
    Renderer *m_renderer;
    TileManager *m_tileManager;
    TileMgrDataModel *m_tileMgrModel;
    TileDataModel *m_tileDataModel;
};

#endif // MAINWINDOW_H
