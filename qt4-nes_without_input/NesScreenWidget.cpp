#include "NesScreenWidget.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../InfoNES_System.h"
#include "../InfoNES.h"
#include "../InfoNES_pAPU.h"

#include <QMutexLocker>
#include <QPainter>
#include <QPoint>
#include <QThread>
#include <QDebug>
#include "NesEmulateWindow.h"

#define USE_ORIGIN_SIZE 1

#define lcd_width 512
#define lcd_height 480

#define TRY_HIGH_SPEED

#ifdef TRY_HIGH_SPEED
    WORD WorkFrameX[ lcd_height ][ lcd_width ];
#else
    WORD WorkFrameX[ lcd_width * lcd_height ];
#endif
NesScreenWidget::NesScreenWidget(QWidget *parent):QWidget(parent), isGray(false)
{
    make_zoom_tab();
    image = QImage((uchar *)WorkFrame, NES_DISP_WIDTH, NES_DISP_HEIGHT, QImage::Format_RGB555); //QImage::Format_RGB16);
    image1 = QImage((uchar *)WorkFrameX, lcd_width, lcd_height, QImage::Format_RGB555);// QImage::Format_RGB16);
    timer.start(1, this);
}

NesScreenWidget::~NesScreenWidget()
{

}
void NesScreenWidget::timerEvent(QTimerEvent *event)
{
    if(NesEmulateWindow::flag_load>0)
    {
        InfoNES_LoadFrame();
        update();
    }
}
void NesScreenWidget::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"resize width:" << width() << " height:" << height();
}

void NesScreenWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter;
        painter.begin(this);
#if USE_ORIGIN_SIZE
        painter.drawImage(QPoint(0, 0), image); //smaller
#else
        painter.drawImage(QPoint(0, 0), image1); //larger
#endif
        painter.end();
        NesEmulateWindow::flag_load=0;
}


static int *zoom_x_tab;
static int *zoom_y_tab;
static int *lcd_w_y;
static int *zoom_y_tab_NES_DISP_WIDTH;
int NesScreenWidget::make_zoom_tab()
{
    int i;
    zoom_x_tab = (int *)malloc(sizeof(int) * lcd_width);

    if(NULL == zoom_x_tab)
    {
        printf("make zoom_x_tab error\n");
        return -1;
    }
    for(i=0; i<lcd_width; i++)
    {
        zoom_x_tab[i] = i*NES_DISP_WIDTH/lcd_width;
    }
    zoom_y_tab = (int *)malloc(sizeof(int) * lcd_height);
    if(NULL == zoom_y_tab)
    {
        printf("make zoom_y_tab error\n");
        return -1;
    }
    for(i=0; i<lcd_height; i++)
    {
        zoom_y_tab[i] = i*NES_DISP_HEIGHT/lcd_height;
    }

    lcd_w_y =  (int *)malloc(sizeof(int) * lcd_height); //lcd_width*(1----lcd_height)
    if(NULL == lcd_w_y)
    {
        printf("lcd_width mul 1 up lcd_height error\n");
        return -1;
    }
    for(i=0;i<lcd_height;i++)
    {
     lcd_w_y[i]=lcd_width*i;
    }
    zoom_y_tab_NES_DISP_WIDTH=(int *)malloc(sizeof(int) * lcd_height);//zoom_y_tab[y] * NES_DISP_WIDTH;
    if(NULL == zoom_y_tab_NES_DISP_WIDTH)
    {
        printf("zoom_y_tab[y] * NES_DISP_WIDTH error\n");
        return -1;
    }
    for(i=0;i<lcd_height;i++)
    {
     zoom_y_tab_NES_DISP_WIDTH[i]=zoom_y_tab[i] * NES_DISP_WIDTH;
    }
    return 1;
}
#define TIME_GO
#ifdef TIME_GO
    #ifdef TRY_HIGH_SPEED
void NesScreenWidget::InfoNES_LoadFrame()
{
    int x,y;
    int buffx;
    int *p=&buffx;
    for (y = 0; y < NES_DISP_HEIGHT; y++ )
    {
        for (x = 0; x < NES_DISP_WIDTH; x++ )
        {
            *p=*(WorkFrame+(y*NES_DISP_WIDTH)+x);
            *(*(WorkFrameX+(y<<1))+(x<<1))=*p;
            *(*(WorkFrameX+(y<<1))+((x<<1)+1))=*p;
            *(*(WorkFrameX+((y<<1)+1))+(x<<1))=*p;
            *(*(WorkFrameX+((y<<1)+1))+((x<<1)+1))=*p;
        }
    }
}
    #else
void NesScreenWidget::InfoNES_LoadFrame()
{
    int x,y;
    int line_width;
    for (y = 0; y < lcd_height; y++ )
    {
        line_width = *(zoom_y_tab_NES_DISP_WIDTH+y);
        for (x = 0; x < lcd_width; x++ )
        {
            *(WorkFrameX+(lcd_w_y[y])+x)=*(WorkFrame+line_width  + zoom_x_tab[x]);
        }
    }
}
    #endif

#else
void NesScreenWidget::InfoNES_LoadFrame()
{
    int x,y;
    int line_width;
    WORD wColor;
    for (y = 0; y < lcd_height; y++ )
    {
        line_width = zoom_y_tab[y] * NES_DISP_WIDTH;
        for (x = 0; x < lcd_width; x++ )
        {
            wColor = WorkFrame[line_width  + zoom_x_tab[x]];
            WorkFrameX[lcd_width*y+x]=wColor;
        }
    }
    //qDebug()<<"1";
}
#endif
void NesScreenWidget::loadFrame()
{
    qDebug()<<"1";
}


