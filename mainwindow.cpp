#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderer.h"
#include "canvas.h"
#include "tilemanager.h"
#include "atest.h"
#include "tilemgrdatamodel.h"
#include <iostream>
#include <QModelIndex>
#include "tiledatamodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,m_renderer(new Renderer)
    ,m_tileManager(new TileManager)
    ,m_tileMgrModel(new TileMgrDataModel(m_tileManager))
    ,m_tileDataModel(new TileDataModel())
{
    // Setup some default tiles for testing:
    m_tileManager->AddTile();
    m_tileManager->AddTile();
    Tile &tileref = m_tileManager->GetTile(0);
    tileref.SetCount(10);
    tileref.SetHeight(1.f);
    tileref.SetWidth(1.f);

    Tile &tileref2 = m_tileManager->GetTile(1);
    tileref2.SetCount(20);
    tileref2.SetHeight(1.f);
    tileref2.SetWidth(1.f);
    // ----

    // Setup renderer
    // This may need to happen as part of the render
    // action, as it preps the item array in the Tile
    m_renderer->SetTileManager(m_tileManager);

    canvas *myCanvas = new canvas(m_renderer, parent);
    ui->setupUi(this);

    ui->displayLayout->addWidget(myCanvas);
    //connect(ui->renderButton,SIGNAL(released()), myCanvas, SLOT(draw()));
    connect(this,SIGNAL(needRepaint()), myCanvas, SLOT(draw()));
    connect(ui->renderButton,SIGNAL(released()), this, SLOT(updateTileManager()));
    connect(ui->addTileButton,SIGNAL(released()), this, SLOT(addtile()));
    // Setup the model for the tile stack view
    m_tileMgrModel = new TileMgrDataModel(m_tileManager, parent);
    connect(ui->addTileButton,SIGNAL(released()),m_tileMgrModel, SLOT(resetInternalData()));
    connect(ui->addTileButton,SIGNAL(released()),ui->TileStack, SLOT(reset()));
    connect(ui->TileStack,SIGNAL(clicked(QModelIndex)), this, SLOT(testClicked(QModelIndex)));
    connect(ui->TileStack,SIGNAL(clicked()),ui->tileInfo,SLOT(reset()));
    ui->TileStack->setModel(m_tileMgrModel);
    // Test test test
    atest myAtest;
    myAtest.printIt();

}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_renderer;
    delete m_tileManager;
    delete m_tileMgrModel;
}

void MainWindow::addtile()
{
    std::cout << "add tile:" << std::endl;
    m_tileManager->AddTile();
}
void MainWindow::testClicked(const QModelIndex index)
{
    std::cout << "click"  << std::endl;
    //QVariant data = m_tileMgrModel->data(index,1);
    Tile &tile = m_tileMgrModel->GetTile(index);
    std::cout << "tile:" << tile.GetName() << "<-:" <<std::endl;
    m_tileDataModel->m_tile = &tile;
    ui->tileInfo->setModel(m_tileDataModel);
    ui->tileInfo->reset();
}

void MainWindow::updateTileManager()
{
    m_tileManager->Prep();
    emit needRepaint();
}
