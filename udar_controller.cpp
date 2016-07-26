#include "udar_controller.h"
#include "ui_udar_controller.h"

UDAR_Controller::UDAR_Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UDAR_Controller)
{
    ui->setupUi(this);

    setupPlotIQ();
    // configure scroll bars:
    // Since scroll bars only support integer values, we'll set a high default range of -500..500 and
    // divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
    // axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
    // just increase the the minimum/maximum values of the scroll bars as needed.
//    ui->horizontalScrollBarI->setRange(-500, 500);
//    ui->verticalScrollBarI->setRange(-500, 500);
//    ui->horizontalScrollBarQ->setRange(-500, 500);
//    ui->verticalScrollBarQ->setRange(-500, 500);
//    ui->horizontalScrollBarC->setRange(-500, 500);
//    ui->verticalScrollBarC->setRange(-500, 500);
//    ui->horizontalScrollBarFFTI->setRange(-500, 500);
//    ui->verticalScrollBarFFTI->setRange(-500, 500);
//    ui->horizontalScrollBarFFTQ->setRange(-500, 500);
//    ui->verticalScrollBarFFTQ->setRange(-500, 500);


    // initialize axis range (and scroll bar positions via signals we just connected):
    ui->plotI->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotI->yAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotQ->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotQ->yAxis->setRange(0, 60, Qt::AlignCenter);

    ui->plotI2->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotI2->yAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotQ2->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotQ2->yAxis->setRange(0, 60, Qt::AlignCenter);

    ui->plotC->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotC->yAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotC2->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotC2->yAxis->setRange(0, 60, Qt::AlignCenter);

    ui->plotFFTI->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotFFTI->yAxis->setRange(70, 140, Qt::AlignCenter);
    ui->plotFFTQ->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotFFTQ->yAxis->setRange(70, 140, Qt::AlignCenter);

    ui->plotFFTI2->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotFFTI2->yAxis->setRange(70, 140, Qt::AlignCenter);
    ui->plotFFTQ2->xAxis->setRange(0, 60, Qt::AlignCenter);
    ui->plotFFTQ2->yAxis->setRange(70, 140, Qt::AlignCenter);

    connectSignals();



    controllerInit();
}

UDAR_Controller::~UDAR_Controller()
{
    delete ui;
}

void UDAR_Controller::connectSignals()
{
    //connect(ui->tabWidget_a, SIGNAL(currentChanged(int)), this, SLOT(tab_aSelected()));

    connect(ui->networkInterfaces,SIGNAL(currentIndexChanged(const QString)),this,SLOT(updateInterfaceFields(const QString)));

    rx_status_timer = new QTimer(this);
    connect(rx_status_timer, SIGNAL(timeout()), this, SLOT(updateRXStatus()));
    rx_status_timer->start(1000);

    //QMetaObject::connectSlotsByName(this);

    // create connection between axes and scroll bars:
   // connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
  //  connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
   // connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
   // connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));


    // Plot Signals

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotI, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotI, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotI, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotI->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotI->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotI->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotI->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotI2, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotI2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotI2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotI2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotI->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotI2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotI->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotQ, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotQ, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotQ, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotQ->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotQ->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotQ->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotQ->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotQ2, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotQ2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotQ2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotQ2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotQ->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotQ2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotQ->yAxis2, SLOT(setRange(QCPRange)));


    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotC, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotC, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotC, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotC->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotC->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotC->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotC->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotC2, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotC2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotC2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotC2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotC2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotC2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotC2->yAxis2, SLOT(setRange(QCPRange)));


    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotFFTI, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotFFTI, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotFFTI, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotFFTI->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTI->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotFFTI->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTI->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotFFTQ, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotFFTQ, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotFFTQ, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotFFTQ->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTQ->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotFFTQ->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTQ->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotFFTI2, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotFFTI2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotFFTI2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotFFTI2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTI2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotFFTI2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTI2->yAxis2, SLOT(setRange(QCPRange)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->plotFFTQ2, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->plotFFTQ2, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->plotFFTQ2, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->plotFFTQ2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTQ2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotFFTQ2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotFFTQ2->yAxis2, SLOT(setRange(QCPRange)));
}


void UDAR_Controller::controllerInit()
{
    time(&start_time);
    gettimeofday(&start_tp, NULL);


    interfaceNames = getNetworkInterfaces();
    ui->networkInterfaces->addItems(interfaceNames);
    if (interfaceNames.contains(DEFAULT_IF_DEV1))
        ui->networkInterfaces->setCurrentIndex(interfaceNames.indexOf(DEFAULT_IF_DEV1));
    else if(interfaceNames.contains(DEFAULT_IF_DEV2))
        ui->networkInterfaces->setCurrentIndex(interfaceNames.indexOf(DEFAULT_IF_DEV2));
    else
        ui->networkInterfaces->setCurrentIndex(0);

    ui->recOutputDirectory->setText(DEFAULT_DIRECTORY);

   // ui->srcMacAddr->setText(DEFAULT_SRC_MAC);
    ui->destMacAddr->setText(DEFAULT_DEST_MAC);
   // ui->srcIpAddr->setText(DEFAULT_SRC_IP);
    ui->destIpAddr->setText(DEFAULT_DEST_IP);

    ui->fmc150RegisterAddr_spinBox->setRange(0,0xFFFF);

    ui->fmc150RegisterAddr_spinBox->setValue(0x0004);
    ui->fmc150RegisterData_spinBox->setValue(0x00000077);

    ui->fmc150_Clk_iDelay_spinBox->setRange(0,0x1F);
    ui->fmc150_CHA_Delay_spinBox->setRange(0,0x1F);
    ui->fmc150_CHB_Delay_spinBox->setRange(0,0x1F);

    ui->fmc150_Clk_iDelay_spinBox->setValue(0);
    ui->fmc150_CHA_Delay_spinBox->setValue(0x1e);
    ui->fmc150_CHB_Delay_spinBox->setValue(0);

    on_chirpParamsResetButton_clicked();

    calculateChirpParams();

    storeChirpParams();
    storeFMC150Params();

    global_pkt_counter = 0;

    ui->transcript->setText("Initialization Complete...Controller Ready");


}

void UDAR_Controller::setupDataPlot(QCustomPlot *plot, QPen pen){

    // The following plot setup is mostly taken from the plot demos:

    plot->addGraph();
  //  plot->graph()->setPen(QPen(Qt::blue));
    plot->graph()->setPen(pen);
    plot->xAxis->setTicks(true);
    plot->xAxis->setTickLabels(true);
    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 9));
    plot->yAxis->setTicks(true);
    plot->yAxis->setTickLabels(true);
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 9));

    plot->axisRect()->setupFullAxesBox(true);
   // plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
}

void UDAR_Controller::setupCounterPlot(QCustomPlot *plot, QPen pen){

    // The following plot setup is mostly taken from the plot demos:
    plot->addGraph();
    plot->graph()->setPen(pen);
    plot->xAxis->setTicks(true);
    plot->xAxis->setTickLabels(true);
    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 9));
    plot->yAxis->setTicks(true);
    plot->yAxis->setTickLabels(true);
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 9));

    plot->addGraph();
    plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 5));
    plot->graph()->setLineStyle(QCPGraph::lsNone);
    plot->graph()->setPen(QPen(QColor(120, 120, 120), 2));


    plot->axisRect()->setupFullAxesBox(true);
    //plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
}


void UDAR_Controller::setupPlotIQ(){
    setupDataPlot(ui->plotI,QPen(Qt::blue));
    setupDataPlot(ui->plotQ,QPen(Qt::red));
    setupDataPlot(ui->plotI2,QPen(Qt::blue));
    setupDataPlot(ui->plotQ2,QPen(Qt::red));
    setupDataPlot(ui->plotFFTI,QPen(Qt::blue));
    setupDataPlot(ui->plotFFTQ,QPen(Qt::red));
    setupDataPlot(ui->plotFFTI2,QPen(Qt::blue));
    setupDataPlot(ui->plotFFTQ2,QPen(Qt::red));

    setupCounterPlot(ui->plotC,QPen(Qt::green));
    setupCounterPlot(ui->plotC2,QPen(Qt::green));

}
void UDAR_Controller::updateDataPlot(QCustomPlot *plot,QVector<double> &dataX,QVector<double> &dataY,int graph_num){
    plot->graph(graph_num)->setData(dataX, dataY);
    plot->graph(graph_num)->rescaleAxes();

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    plot->replot();
}

void UDAR_Controller::updateDataPlotIQ(){
    updateDataPlot(ui->plotI,plotTimeVec,plotDataI,0);
    updateDataPlot(ui->plotQ,plotTimeVec,plotDataQ,0);
    updateDataPlot(ui->plotI2,plotTimeVec,plotDataI2,0);
    updateDataPlot(ui->plotQ2,plotTimeVec,plotDataQ2,0);
    updateDataPlot(ui->plotC,plotTimeVec,plotDataC,0);
    updateDataPlot(ui->plotC,ctrjumpsX,ctrjumpsY,1);
    updateDataPlot(ui->plotC2,plotTimeVec,plotDataC2,0);
    updateDataPlot(ui->plotC2,ctrjumpsX,ctrjumpsY2,1);
}

void UDAR_Controller::updateFFTPlotIQ(){
    updateDataPlot(ui->plotFFTI,plotfftVec,plotfftI,0);
    updateDataPlot(ui->plotFFTQ,plotfftVec,plotfftQ,0);
    updateDataPlot(ui->plotFFTI2,plotfftVec,plotfftI2,0);
    updateDataPlot(ui->plotFFTQ2,plotfftVec,plotfftQ2,0);
}

void UDAR_Controller::selectionChanged(QCustomPlot *plot)
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || plot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      plot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || plot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    plot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    plot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || plot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      plot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || plot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    plot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    plot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);

  }
}
void UDAR_Controller::selectionChanged()
{
    selectionChanged(ui->plotI);
    selectionChanged(ui->plotQ);
    selectionChanged(ui->plotI2);
    selectionChanged(ui->plotQ2);
    selectionChanged(ui->plotC);
    selectionChanged(ui->plotC2);
    selectionChanged(ui->plotFFTI);
    selectionChanged(ui->plotFFTQ);
    selectionChanged(ui->plotFFTI2);
    selectionChanged(ui->plotFFTQ2);

}

void UDAR_Controller::mousePress(QCustomPlot *plot)
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis)){
    plot->axisRect()->setRangeDrag(plot->xAxis->orientation());
  }
  else if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis)){
    plot->axisRect()->setRangeDrag(plot->yAxis->orientation());
  }
  else{
    plot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
  }
}
void UDAR_Controller::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

    mousePress(ui->plotI);
    mousePress(ui->plotQ);
    mousePress(ui->plotI2);
    mousePress(ui->plotQ2);
    mousePress(ui->plotC);
    mousePress(ui->plotC2);
    mousePress(ui->plotFFTI);
    mousePress(ui->plotFFTQ);
    mousePress(ui->plotFFTI2);
    mousePress(ui->plotFFTQ2);


}

void UDAR_Controller::mouseWheel(QCustomPlot *plot)
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    plot->axisRect()->setRangeZoom(plot->xAxis->orientation());
  else if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    plot->axisRect()->setRangeZoom(plot->yAxis->orientation());
  else
    plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void UDAR_Controller::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

    mouseWheel(ui->plotI);
    mouseWheel(ui->plotQ);
    mouseWheel(ui->plotI2);
    mouseWheel(ui->plotQ2);
    mouseWheel(ui->plotC);
    mouseWheel(ui->plotC2);
    mouseWheel(ui->plotFFTI);
    mouseWheel(ui->plotFFTQ);
    mouseWheel(ui->plotFFTI2);
    mouseWheel(ui->plotFFTQ2);


}

void UDAR_Controller::horzScrollBarChanged(QCustomPlot *plot,int value)
{
  if (qAbs(plot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    plot->xAxis->setRange(value/100.0, plot->xAxis->range().size(), Qt::AlignCenter);
    plot->replot();
  }
}
void UDAR_Controller::vertScrollBarChanged(QCustomPlot *plot, int value)
{
  if (qAbs(plot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    plot->yAxis->setRange(-value/100.0, plot->yAxis->range().size(), Qt::AlignCenter);
    plot->replot();
  }
}

void UDAR_Controller::horzScrollBarIChanged(int value)
{
  horzScrollBarChanged(ui->plotI,value);
}
void UDAR_Controller::horzScrollBarQChanged(int value)
{
  horzScrollBarChanged(ui->plotQ,value);
}
void UDAR_Controller::horzScrollBarCChanged(int value)
{
  horzScrollBarChanged(ui->plotC,value);
}
void UDAR_Controller::horzScrollBarFFTIChanged(int value)
{
  horzScrollBarChanged(ui->plotFFTI,value);
}
void UDAR_Controller::horzScrollBarFFTQChanged(int value)
{
  horzScrollBarChanged(ui->plotFFTQ,value);
}

void UDAR_Controller::vertScrollBarIChanged(int value)
{
  vertScrollBarChanged(ui->plotI,value);
}
void UDAR_Controller::vertScrollBarQChanged(int value)
{
  vertScrollBarChanged(ui->plotQ,value);
}
void UDAR_Controller::vertScrollBarCChanged(int value)
{
  vertScrollBarChanged(ui->plotC,value);
}
void UDAR_Controller::vertScrollBarFFTIChanged(int value)
{
  vertScrollBarChanged(ui->plotFFTI,value);
}
void UDAR_Controller::vertScrollBarFFTQChanged(int value)
{
  vertScrollBarChanged(ui->plotFFTQ,value);
}

void UDAR_Controller::xAxisIChanged(QCPRange range)
{
  ui->horizontalScrollBarI->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBarI->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void UDAR_Controller::yAxisIChanged(QCPRange range)
{
  ui->verticalScrollBarI->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
  ui->verticalScrollBarI->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}



u_char UDAR_Controller::GetRxDataFormat(){
    u_char select_adc_l = (u_char)ui->adc_data_l_radioButton->isChecked();
    u_char select_dac_l = (u_char)ui->dac_data_l_radioButton->isChecked();
    u_char select_adc_ctr_l = (u_char)ui->adc_counter_l_radioButton->isChecked();
    u_char select_glbl_ctr_l = (u_char)ui->global_counter_l_radioButton->isChecked();
    u_char select_adc_u = (u_char)ui->adc_data_u_radioButton->isChecked();
    u_char select_dac_u = (u_char)ui->dac_data_u_radioButton->isChecked();
    u_char select_adc_ctr_u = (u_char)ui->adc_counter_u_radioButton->isChecked();
    u_char select_glbl_ctr_u = (u_char)ui->global_counter_u_radioButton->isChecked();

    uint32_t select_data_l = 0*select_adc_l + select_dac_l + 2*select_adc_ctr_l + 3*select_glbl_ctr_l;
    uint32_t select_data_u = 0*select_adc_u + select_dac_u + 2*select_adc_ctr_u + 3*select_glbl_ctr_u;
    uint32_t select_data = (select_data_l & 0x0F) + ((select_data_u<<4) & 0xF0);

    u_char dataformat = (u_char)(select_data & 0x000000FF);

    return dataformat;
}



void UDAR_Controller::storeChirpParams(){
    double chirp_prf = ui->chirpPRF_dSpinBox->value();
//    uint32_t chirp_prf_int = (uint32_t)chirp_prf;
//    double chirp_prf_int_d = (double)chirp_prf_int;
//    double chirp_prf_frac_d = chirp_prf - chirp_prf_int_d;
//    chirp_prf_frac_d = 1000000.0*chirp_prf_frac_d;
//    uint32_t chirp_prf_frac = (uint32_t)round(chirp_prf_frac_d);

    // Changed so that chirp_prf_int and chirp_prf_frac are the upper and lower 32 bits of the
    // 64 bit counter to be used by the fpga

    double fClock = ui->clockFreq_dSpinBox->value();    //MHz
    double max_prf_d = fClock*1000000.0*chirp_prf;
    uint64_t max_chirp_prf_count = (uint64_t)round(max_prf_d);
    uint32_t chirp_prf_int = (uint32_t)((max_chirp_prf_count>>32) & 0xFFFFFFFF);
    uint32_t chirp_prf_frac = (uint32_t)(max_chirp_prf_count & 0xFFFFFFFF);

    chirp_params.prf_int = chirp_prf_int;
    chirp_params.prf_frac = chirp_prf_frac;
    chirp_params.adc_count = (uint32_t)ui->adcSamples_spinBox->value();
    chirp_params.freq_off = (uint32_t)ui->freqOffset_spinBox->value();
    chirp_params.tuning_word = (uint32_t)ui->chirpTuningWord_spinBox->value();
    chirp_params.num_samples = (uint32_t)ui->numSamples_spinBox->value();

//    u_char select_adc_l = (u_char)ui->adc_data_l_radioButton->isChecked();
//    u_char select_dac_l = (u_char)ui->dac_data_l_radioButton->isChecked();
//    u_char select_adc_ctr_l = (u_char)ui->adc_counter_l_radioButton->isChecked();
//    u_char select_glbl_ctr_l = (u_char)ui->global_counter_l_radioButton->isChecked();
//    u_char select_adc_u = (u_char)ui->adc_data_u_radioButton->isChecked();
//    u_char select_dac_u = (u_char)ui->dac_data_u_radioButton->isChecked();
//    u_char select_adc_ctr_u = (u_char)ui->adc_counter_u_radioButton->isChecked();
//    u_char select_glbl_ctr_u = (u_char)ui->global_counter_u_radioButton->isChecked();

//    uint32_t select_data_l = 0*select_adc_l + select_dac_l + 2*select_adc_ctr_l + 3*select_glbl_ctr_l;
//    uint32_t select_data_u = 0*select_adc_u + select_dac_u + 2*select_adc_ctr_u + 3*select_glbl_ctr_u;
//    uint32_t select_data = (select_data_l & 0x0F) + ((select_data_u<<4) & 0xF0);

//    chirp_params.control_word = (uint32_t)(select_data & 0x000000FF);
  //  u_char dataformat = GetRxDataFormat() ;
     chirp_params.control_word = (uint32_t)(GetRxDataFormat() & 0x000000FF);
    //chirp_params.control_word = (uint32_t)ui->dacLoopback_checkBox->isChecked();
}
void UDAR_Controller::storeFMC150Params(){

    u_char chA_delay = (u_char)(ui->fmc150_CHA_Delay_spinBox->hexValue() & 0x0000001F);
    u_char chB_delay = (u_char)(ui->fmc150_CHB_Delay_spinBox->hexValue() & 0x0000001F);
    u_char clk_delay = (u_char)(ui->fmc150_Clk_iDelay_spinBox->hexValue() & 0x0000001F);
    uint16_t reg_addr = (uint16_t)(ui->fmc150RegisterAddr_spinBox->hexValue() & 0x0000FFFF);
    uint32_t reg_data = (uint32_t)(ui->fmc150RegisterData_spinBox->hexValue() & 0xFFFFFFFF);
    u_char rw_val = (u_char)(ui->fmc150_read_radioButton->isChecked() & 0xFF);
    u_char cdc_val = (u_char)(ui->fmc150_CDC_radioButton->isChecked() & 0xFF);
    u_char ads_val = (u_char)(ui->fmc150_ADS_radioButton->isChecked() & 0xFF);
    u_char dac_val = (u_char)(ui->fmc150_DAC_radioButton->isChecked() & 0xFF);
    u_char amc_val = (u_char)(ui->fmc150_AMC_radioButton->isChecked() & 0xFF);

    fmc150_params.set_CH_A_iDelay = chA_delay;
    fmc150_params.set_CH_B_iDelay = chB_delay;
    fmc150_params.set_CLK_iDelay = clk_delay;
    fmc150_params.register_addres = reg_addr;
    fmc150_params.spi_register_data_to_fmc150 = reg_data;
    fmc150_params.rw = ((rw_val&0x000000FF)<<24) + ((rw_val&0x000000FF)<<16) + ((rw_val&0x000000FF)<<8) + (rw_val&0x000000FF);
    fmc150_params.cdce72010 = cdc_val;
    fmc150_params.ads62p49 = ads_val;
    fmc150_params.dac3283 = dac_val;
    fmc150_params.amc7823 = amc_val;

    fmc150_params.set_user8 = 0x00;
    fmc150_params.set_user16 = 0x0000;

    uint16_t chk_code = ((cdc_val&0x01))+((ads_val&0x01)<<4)+((dac_val&0x01)<<8)+((amc_val&0x01)<<12);
    u_char chk_code8 = ((cdc_val&0x01))+((ads_val&0x01)<<1)+((dac_val&0x01)<<2)+((amc_val&0x01)<<3);
    fmc150_params.code_check1 = cdc_val + ads_val + dac_val + amc_val;
    fmc150_params.code_check2 = chk_code8;
    fmc150_params.code_check16 = chk_code;
    fmc150_params.control_word = 0;
}

void UDAR_Controller::calculateChirpParams(){
//    --------------DDS Chirp Generation Parameters-------------------
//    -- period = 4.17 us, BW = 46.08 MHz
//    -- 491.52 Mhz clock, 4096 samples, 16 bit phase accumulator (n = 16)
//    -- tuning_word_coeff = 3      for BW = 46.08 MHz (2048 samples)
//    -- tuning_word_coeff = 4      for BW = 61.44 MHz (2048 samples)
//    -- tuning_word_coeff = 1.5    for BW = 46.08 MHz (4096 samples)
//    -- tuning_word_coeff = 2      for BW = 61.44 MHz (4096 samples)
//    -- Calculated Using:
//    --    tuning_word_coeff = BW*(2^n)/(num_samples*fClock)
//    -- Taken From:
//    --    tuning_word_coeff = period*slope*(2^n)/(num_samples*fClock)
//    -- Where:
//    --    slope = BW/period
//    --    num_samples = period*fclock
//    --
//    -- Note: Derived From:
//    --    tuning_word = rect[t/period] t*slope*(2^n)/fclock
//    -- And:
//    --     t = sample_count*period/num_samples
//    -- Therefore:
//    --    tuning_word = sample_count*tuning_coeff
//    -- Additoinally:
//    --    min_freq = freq_offset*fclock/2^n

    double tuning_word_coeff = (double) ui->chirpTuningWord_spinBox->value();
    double num_samples = (double)ui->numSamples_spinBox->value();
    double freq_offset = (double)ui->freqOffset_spinBox->value();
    int n = ui->phaseAccLen_spinBox->value();
    double fClock = ui->clockFreq_dSpinBox->value();    //MHz
    double two_pow_n = (double)(1<<n);



    double BW = (num_samples*fClock*tuning_word_coeff)/(two_pow_n);     //MHz
    double period = num_samples/fClock;                      //usec
    double slope = BW/period;                               //MHz/usec
    double min_freq = freq_offset*fClock/(two_pow_n);

    ui->chirpBW_dSpinBox->setValue(BW);
    ui->chirpTime_dSpinBox->setValue(period);
    ui->chirpSlope_dSpinBox->setValue(slope);
    ui->minFreq_dSpinBox->setValue(min_freq);

    chirp_params.freq_off = (uint32_t)freq_offset;
    chirp_params.tuning_word = (uint32_t)tuning_word_coeff;
    chirp_params.num_samples = (uint32_t)num_samples;
}


void UDAR_Controller::updateInterfaceFields(const QString if_name){
    NetInterface *currInterface = interfaceMap[if_name];
    ui->srcMacAddr->setText(currInterface->GetMacString());
    ui->srcIpAddr->setText(currInterface->GetIpString());
}
void UDAR_Controller::getMacArray(u_char mac[6],QString text){
    QByteArray ba = text.toLatin1();
    const char* str = ba.data();
    unsigned int maci[6];
    sscanf(str,"%02x:%02x:%02x:%02x:%02x:%02x",&maci[0],&maci[1],&maci[2],&maci[3],&maci[4],&maci[5]);
    for(int i=0;i<6;i++) mac[i] = (u_char)maci[i];
}
void UDAR_Controller::getIpArray(u_char ip[4],QString text){
    QByteArray ba = text.toLatin1();
    const char* str = ba.data();
    unsigned int ip_int[4];
    //sscanf(str,"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
    sscanf(str,"%d.%d.%d.%d",&ip_int[0],&ip_int[1],&ip_int[2],&ip_int[3]);
    for(int i=0;i<4;i++) ip[i] = (u_char)ip_int[i];
}

void UDAR_Controller::sendCommand(const QString name, uint32_t cmd)
{
    NetInterface *currInterface = interfaceMap[name];
    QByteArray ba = name.toLatin1();
    const char* if_name = ba.data();
    int i;
    //const char* if_name= "en0";//argv[1];
    const char* target_ip_string = "192.168.1.10"; //argv[2];
    u_char target_mac[6];
    u_char target_ip_addr_in[4];
    getMacArray(target_mac,ui->destMacAddr->text());
    getIpArray(target_ip_addr_in,ui->destIpAddr->text());

    uint16_t packet_size;
    u_char *packet_data;

    // chirp command: ascii WWCC
    if(cmd == CHIRP_WRITE_COMMAND){
        packet_size = 6+sizeof(struct chirp_parameters);
        packet_data = new u_char[packet_size];

        // global packet counter

        if(ui->byteReorderCheckBox->isChecked()){
            *(uint16_t *)packet_data =htons(global_pkt_counter++);
           // for (i=2;i<6;i++) packet_data[i] = 0x57; // Ascii W
            *(uint32_t*)(packet_data+2) = htonl(cmd);
            int j = 0;
            for (i=6;i<packet_size;i+=4)
                *(uint32_t*)(packet_data+i) = htonl(*((uint32_t*)(&chirp_params)+(j++)));
        }
        else {
            *(uint16_t *)packet_data = global_pkt_counter++;
           // for (i=2;i<6;i++) packet_data[i] = cmd;
            *(uint32_t*)(packet_data+2) = cmd;
            memcpy(packet_data+6,&chirp_params,sizeof(struct chirp_parameters));
        }
    }
    //fmc150 spi reg command: ascii WWFF
    else if(cmd == FMC150_WRITE_COMMAND){
        packet_size = 6+sizeof(struct fmc150_parameters);
        packet_data = new u_char[packet_size];

        // global packet counter

        if(ui->byteReorderCheckBox->isChecked()){
            *(uint16_t *)packet_data =htons(global_pkt_counter++);
            *(uint32_t*)(packet_data+2) = htonl(cmd);
            int j = 0;
            for (i=6;i<packet_size;i+=4)
                *(uint32_t*)(packet_data+i) = htonl(*((uint32_t*)(&fmc150_params)+(j++)));
        }
        else {
            *(uint16_t *)packet_data = global_pkt_counter++;
            *(uint32_t*)(packet_data+2) = cmd;
            memcpy(packet_data+6,&fmc150_params,sizeof(struct fmc150_parameters));
        }
    }
    // Unknown command - default case
    else{
        packet_size = 14;
        packet_data = new u_char[packet_size];

        uint32_t cmd_id = genCommandIdentifier();

        // global packet counter

        if(ui->byteReorderCheckBox->isChecked()){
            *(uint16_t *)packet_data =htons(global_pkt_counter++);
           // for (i=2;i<6;i++) packet_data[i] = 0x57; // Ascii W
            *(uint32_t*)(packet_data+2) = htonl(cmd);
            *(uint32_t*)(packet_data+6) = htonl(cmd_id);
            *(uint32_t*)(packet_data+10) = htonl(0xFEEDBEEF);
        }
        else {
            *(uint16_t *)packet_data = global_pkt_counter++;
            *(uint32_t*)(packet_data+2) = cmd;
            *(uint32_t*)(packet_data+6) = cmd_id;
            *(uint32_t*)(packet_data+10) = 0xFEEDBEEF;
        }
    }

    // Construct Ethernet header (except for source MAC address).
    // (Destination set to broadcast address, FF:FF:FF:FF:FF:FF.)
    struct ether_header header;
    //header.ether_type=htons(ETH_P_ARP);
    header.ether_type=htons(packet_size);
  //  memset(header.ether_dhost,0xff,sizeof(header.ether_dhost));
    for (i=0;i<6;i++) header.ether_dhost[i] = target_mac[i];

    // Convert target IP address from string, copy into ARP request.
    struct in_addr target_ip_addr={0};
//    if (!inet_aton(target_ip_string,&target_ip_addr)) {
//        fprintf(stderr,"%s is not a valid IP address",target_ip_string);
//        exit(1);
//    }
    memcpy(&target_ip_addr,target_ip_addr_in,4);

    //setTranscript( target_ip_addr_in,4);
   // setTranscript( (u_char *)&target_ip_addr,4);

    // Write the interface name to an ifreq structure,
    // for obtaining the source MAC and IP addresses.
    struct ifreq ifr;
    size_t if_name_len=strlen(if_name);
    if (if_name_len<sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name,if_name,if_name_len);
        ifr.ifr_name[if_name_len]=0;
    } else {
        fprintf(stderr,"interface name is too long");
        exit(1);
    }

    // Open an IPv4-family socket for use when calling ioctl.
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    if (fd==-1) {
        fprintf(stderr,"[SendCommand] Unable to open socket");
        perror(0);
        exit(1);
    }

    // Obtain the source IP address, copy into ARP request
    // if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
    //     perror(0);
    //     ::close(fd);
    //     exit(1);
    // }
    // struct sockaddr_in* source_ip_addr = (struct sockaddr_in*)&ifr.ifr_addr;

    //struct sockaddr_in* source_ip_addr=inet_addr("192.168.1.1");

    // Obtain the source MAC address, copy into Ethernet header and ARP request.
//     if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
//         fprintf(stderr,"[SendCommand] Unable to get source MAC. ioctl returned:\n");
//         perror(0);
//         ::close(fd);
//         exit(1);
//     }
//     if (ifr.ifr_addr.sa_family!=ARPHRD_ETHER) {
//         fprintf(stderr,"[SendCommand] not an Ethernet interface. Returned:\n");
//         ::close(fd);
//         exit(1);
//     }
//     const unsigned char* source_mac_addr=(unsigned char*)ifr.ifr_addr.sa_data;
//     memcpy(header.ether_shost,source_mac_addr,sizeof(header.ether_shost));

    //u_char source_mac[6]={0x98,0x5a,0xeb,0xdb,0x06,0x6f};
    u_char *source_mac = currInterface->GetMac();
    for (i=0;i<6;i++) header.ether_shost[i] = source_mac[i];


    ::close(fd);

    // Combine the Ethernet header and ARP request into a contiguous block.
    unsigned char frame[sizeof(struct ether_header)+ packet_size];
    memcpy(frame,&header,sizeof(struct ether_header));
    memcpy(frame+sizeof(struct ether_header),packet_data,packet_size);


//    for (i=0;i<sizeof(struct ether_header)+ packet_size;i++){
//      printf("%02x ",frame[i]);
//    }

    // Open a PCAP packet capture descriptor for the specified interface.
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    pcap_errbuf[0]='\0';
    pcap_t* pcap=pcap_open_live(if_name,96,0,0,pcap_errbuf);
    if (pcap_errbuf[0]!='\0') {
        fprintf(stderr,"[SendCommand] pcap_errbuf: %s\n",pcap_errbuf);
    }
    if (!pcap) {
        exit(1);
    }

    for(i=0;i<TX_PKT_CMD_REPEAT;i++){
        // Write the Ethernet frame to the interface.
        if (pcap_inject(pcap,frame,sizeof(frame))==-1) {
            pcap_perror(pcap,0);
            pcap_close(pcap);
            exit(1);
        }
    }
    char tempstr[STR_SIZE];
    sprintf(tempstr,"Packet Sent on Interface: %s",if_name);
    setTranscript(tempstr);
    setTranscript(frame,sizeof(struct ether_header)+ packet_size);

    // Close the PCAP descriptor.
    pcap_close(pcap);

    //Delete packet data
    delete[] packet_data;
  //  return 0;
}


void UDAR_Controller::sendCommand(const QString name)
{
    NetInterface *currInterface = interfaceMap[name];
    QByteArray ba = name.toLatin1();
    const char* if_name = ba.data();
    int i;
    //const char* if_name= "en0";//argv[1];
    const char* target_ip_string = "192.168.1.10"; //argv[2];
    u_char target_mac[6];
    u_char target_ip_addr_in[4];
    getMacArray(target_mac,ui->destMacAddr->text());
    getIpArray(target_ip_addr_in,ui->destIpAddr->text());

    uint16_t packet_size = 6+sizeof(struct chirp_parameters);

    //u_char *packet_data = (u_char *)malloc(packet_size*sizeof(u_char));
    u_char *packet_data = new u_char[packet_size];

    // global packet counter

    if(ui->byteReorderCheckBox->isChecked()){
        *(uint16_t *)packet_data =htons(global_pkt_counter++);
        for (i=2;i<6;i++) packet_data[i] = 0x57; // Ascii W
        int j = 0;
        for (i=6;i<packet_size;i+=4)
            *(uint32_t*)(packet_data+i) = htonl(*((uint32_t*)(&chirp_params)+(j++)));
    }
    else {
        *(uint16_t *)packet_data = global_pkt_counter++;
        for (i=2;i<6;i++) packet_data[i] = 0x57; // Ascii W
        memcpy(packet_data+6,&chirp_params,sizeof(struct chirp_parameters));
    }

    // Construct Ethernet header (except for source MAC address).
    // (Destination set to broadcast address, FF:FF:FF:FF:FF:FF.)
    struct ether_header header;
    //header.ether_type=htons(ETH_P_ARP);
    header.ether_type=htons(packet_size);
  //  memset(header.ether_dhost,0xff,sizeof(header.ether_dhost));
    for (i=0;i<6;i++) header.ether_dhost[i] = target_mac[i];

    // Convert target IP address from string, copy into ARP request.
    struct in_addr target_ip_addr={0};
//    if (!inet_aton(target_ip_string,&target_ip_addr)) {
//        fprintf(stderr,"%s is not a valid IP address",target_ip_string);
//        exit(1);
//    }
    memcpy(&target_ip_addr,target_ip_addr_in,4);

    //setTranscript( target_ip_addr_in,4);
   // setTranscript( (u_char *)&target_ip_addr,4);

    // Write the interface name to an ifreq structure,
    // for obtaining the source MAC and IP addresses.
    struct ifreq ifr;
    size_t if_name_len=strlen(if_name);
    if (if_name_len<sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name,if_name,if_name_len);
        ifr.ifr_name[if_name_len]=0;
    } else {
        fprintf(stderr,"interface name is too long");
        exit(1);
    }

    // Open an IPv4-family socket for use when calling ioctl.
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    if (fd==-1) {
        fprintf(stderr,"[SendCommand] Unable to open socket");
        perror(0);
        exit(1);
    }

    // Obtain the source IP address, copy into ARP request
    // if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
    //     perror(0);
    //     ::close(fd);
    //     exit(1);
    // }
    // struct sockaddr_in* source_ip_addr = (struct sockaddr_in*)&ifr.ifr_addr;

    //struct sockaddr_in* source_ip_addr=inet_addr("192.168.1.1");

    // Obtain the source MAC address, copy into Ethernet header and ARP request.
//     if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
//         fprintf(stderr,"[SendCommand] Unable to get source MAC. ioctl returned:\n");
//         perror(0);
//         ::close(fd);
//         exit(1);
//     }
//     if (ifr.ifr_addr.sa_family!=ARPHRD_ETHER) {
//         fprintf(stderr,"[SendCommand] not an Ethernet interface. Returned:\n");
//         ::close(fd);
//         exit(1);
//     }
//     const unsigned char* source_mac_addr=(unsigned char*)ifr.ifr_addr.sa_data;
//     memcpy(header.ether_shost,source_mac_addr,sizeof(header.ether_shost));

    //u_char source_mac[6]={0x98,0x5a,0xeb,0xdb,0x06,0x6f};
    u_char *source_mac = currInterface->GetMac();
    for (i=0;i<6;i++) header.ether_shost[i] = source_mac[i];


    ::close(fd);

    // Combine the Ethernet header and ARP request into a contiguous block.
    unsigned char frame[sizeof(struct ether_header)+ packet_size];
    memcpy(frame,&header,sizeof(struct ether_header));
    memcpy(frame+sizeof(struct ether_header),packet_data,packet_size);


//    for (i=0;i<sizeof(struct ether_header)+ packet_size;i++){
//      printf("%02x ",frame[i]);
//    }

    // Open a PCAP packet capture descriptor for the specified interface.
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    pcap_errbuf[0]='\0';
    pcap_t* pcap=pcap_open_live(if_name,96,0,0,pcap_errbuf);
    if (pcap_errbuf[0]!='\0') {
        fprintf(stderr,"[SendCommand] pcap_errbuf: %s\n",pcap_errbuf);
    }
    if (!pcap) {
        exit(1);
    }

    for(i=0;i<TX_PKT_CMD_REPEAT;i++){
        // Write the Ethernet frame to the interface.
        if (pcap_inject(pcap,frame,sizeof(frame))==-1) {
            pcap_perror(pcap,0);
            pcap_close(pcap);
            exit(1);
        }
    }
    char tempstr[STR_SIZE];
    sprintf(tempstr,"Packet Sent on Interface: %s",if_name);
    setTranscript(tempstr);
    setTranscript(frame,sizeof(struct ether_header)+ packet_size);

    // Close the PCAP descriptor.
    pcap_close(pcap);
  //  return 0;
}

void UDAR_Controller::sendTestCommand(const QString name)
{
    NetInterface *currInterface = interfaceMap[name];
    QByteArray ba = name.toLatin1();
    const char* if_name = ba.data();
    int i;
    //const char* if_name= "en0";//argv[1];
    const char* target_ip_string= "192.168.1.10";//argv[2];
    u_char target_mac[6];
    u_char target_ip_addr_in[4];
    getMacArray(target_mac,ui->destMacAddr->text());
    getIpArray(target_ip_addr_in,ui->destIpAddr->text());


    uint16_t packet_size = 482;

    uint32_t testword = 0xFEEDBEEF;
    //u_char *packet_data = (u_char *)malloc(packet_size*sizeof(u_char));
    u_char *packet_data = new u_char[packet_size];

    uint32_t counter = 0;
    for (i=0;i<2;i++) packet_data[i] = 0x54; // Ascii T
    if(ui->byteReorderCheckBox->isChecked()){
        for (i=2;i<packet_size;i+=8) {
            *(uint32_t *)(packet_data+i) = htonl(0xFEEDBEEF);
            *(uint32_t *)(packet_data+i+4) = htonl(counter++);
        }
    }
    else {
        for (i=2;i<packet_size;i+=8) {
            *(uint32_t *)(packet_data+i) = 0xFEEDBEEF;
            *(uint32_t *)(packet_data+i+4) = (counter++);
        }
    }


    // Construct Ethernet header (except for source MAC address).
    // (Destination set to broadcast address, FF:FF:FF:FF:FF:FF.)
    struct ether_header header;
    //header.ether_type=htons(ETH_P_ARP);
    header.ether_type=htons(packet_size+sizeof(ether_header));
  //  memset(header.ether_dhost,0xff,sizeof(header.ether_dhost));
    for (i=0;i<6;i++) header.ether_dhost[i] = target_mac[i];

    // Convert target IP address from string, copy into ARP request.
    struct in_addr target_ip_addr={0};
//    if (!inet_aton(target_ip_string,&target_ip_addr)) {
//        fprintf(stderr,"%s is not a valid IP address",target_ip_string);
//        exit(1);
//    }
    memcpy(&target_ip_addr,target_ip_addr_in,4);

    // Write the interface name to an ifreq structure,
    // for obtaining the source MAC and IP addresses.
    struct ifreq ifr;
    size_t if_name_len=strlen(if_name);
    if (if_name_len<sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name,if_name,if_name_len);
        ifr.ifr_name[if_name_len]=0;
    } else {
        fprintf(stderr,"interface name is too long");
        exit(1);
    }

    // Open an IPv4-family socket for use when calling ioctl.
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    if (fd==-1) {
        fprintf(stderr,"[SendCommand] Unable to open socket");
        perror(0);
        exit(1);
    }

    // Obtain the source IP address, copy into ARP request
    // if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
    //     perror(0);
    //     ::close(fd);
    //     exit(1);
    // }
    // struct sockaddr_in* source_ip_addr = (struct sockaddr_in*)&ifr.ifr_addr;

    //struct sockaddr_in* source_ip_addr=inet_addr("192.168.1.1");

    // Obtain the source MAC address, copy into Ethernet header and ARP request.
//     if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
//         fprintf(stderr,"[SendCommand] Unable to get source MAC. ioctl returned:\n");
//         perror(0);
//         ::close(fd);
//         exit(1);
//     }
//     if (ifr.ifr_addr.sa_family!=ARPHRD_ETHER) {
//         fprintf(stderr,"[SendCommand] not an Ethernet interface. Returned:\n");
//         ::close(fd);
//         exit(1);
//     }
//     const unsigned char* source_mac_addr=(unsigned char*)ifr.ifr_addr.sa_data;
//     memcpy(header.ether_shost,source_mac_addr,sizeof(header.ether_shost));

    //u_char source_mac[6]={0x98,0x5a,0xeb,0xdb,0x06,0x6f};
    u_char *source_mac = currInterface->GetMac();
    for (i=0;i<6;i++) header.ether_shost[i] = source_mac[i];


    ::close(fd);

    // Combine the Ethernet header and ARP request into a contiguous block.
    unsigned char frame[sizeof(struct ether_header)+ packet_size];
    memcpy(frame,&header,sizeof(struct ether_header));
    memcpy(frame+sizeof(struct ether_header),packet_data,packet_size);


//    for (i=0;i<sizeof(struct ether_header)+ packet_size;i++){
//      printf("%02x ",frame[i]);
//    }

    // Open a PCAP packet capture descriptor for the specified interface.
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    pcap_errbuf[0]='\0';
    pcap_t* pcap=pcap_open_live(if_name,96,0,0,pcap_errbuf);
    if (pcap_errbuf[0]!='\0') {
        fprintf(stderr,"[SendCommand] pcap_errbuf: %s\n",pcap_errbuf);
    }
    if (!pcap) {
        exit(1);
    }

    for(i=0;i<10;i++){
        // Write the Ethernet frame to the interface.
        if (pcap_inject(pcap,frame,sizeof(frame))==-1) {
            pcap_perror(pcap,0);
            pcap_close(pcap);
            exit(1);
        }
    }
    char tempstr[STR_SIZE];
    sprintf(tempstr,"Packet Sent on Interface: %s",if_name);
    setTranscript(tempstr);
    setTranscript(frame,sizeof(struct ether_header)+ packet_size);

    // Close the PCAP descriptor.
    pcap_close(pcap);
  //  return 0;
}

QStringList UDAR_Controller::getNetworkInterfaces(){
    QStringList ifNames;
    NetInterface *tempNetInterface;
    char name_prev[128];
    QString nameqstr;

    // Head of the interface address linked list
    ifaddrs* ifap = NULL;

    int r = getifaddrs(&ifap);

    if (r != 0) {
        // Non-zero return code means an error
        printf("return code = %d\n", r);
        exit(r);
    }

    ifaddrs* current = ifap;

    if (current == NULL) {
        printf("No interfaces found\n");
    }

    while (current != NULL) {
        if(current->ifa_flags & IFF_UP){
            if(strcmp(name_prev,current->ifa_name)){
                if (interfaceMap.contains(current->ifa_name)){
                     tempNetInterface = interfaceMap[current->ifa_name];
                }
                else{
                    nameqstr = QString::fromUtf8(current->ifa_name);
                   // tempNetInterface = new NetInterface(nameqstr);
                    tempNetInterface = new NetInterface(this,nameqstr);
                    interfaceMap[current->ifa_name] = tempNetInterface;
                }
            }

            const sockaddr_in* interfaceAddress = castToIP4(current->ifa_addr);
            const sockaddr_in* broadcastAddress = castToIP4(current->ifa_dstaddr);
            const sockaddr_in* subnetMask       = castToIP4(current->ifa_netmask);

    //        printf("Interface %s", current->ifa_name);
    //        if (current->ifa_addr != NULL) {
    //            printf(" %s", levelToString(current->ifa_addr->sa_family));
    //        }
    //        printf("\nStatus    = %s\n", (current->ifa_flags & IFF_UP) ? "Online" : "Down");
    //        printIP("IP       ", interfaceAddress);
    //        printIP("Broadcast", broadcastAddress);
    //        printIP("Subnet   ", subnetMask);

            if(interfaceAddress != NULL){
                int addr = ntohl(interfaceAddress->sin_addr.s_addr);
                uint8_t temp_ip[4];
                temp_ip[0] = (addr >> 24) & 0xFF;
                temp_ip[1] = (addr >> 16) & 0xFF;
                temp_ip[2] = (addr >> 8) & 0xFF;
                temp_ip[3] = addr & 0xFF;
                tempNetInterface->setIp(temp_ip);
            }


            // The MAC address and the interfaceAddress come in as
            // different interfaces with the same name.

            if ((current->ifa_addr != NULL) && (current->ifa_addr->sa_family == AF_LINK)) {
#ifdef __linux__
                // Linux
                struct ifreq ifr;

                int fd = socket(AF_INET, SOCK_DGRAM, 0);

                ifr.ifr_addr.sa_family = AF_INET;
                strcpy(ifr.ifr_name, current->ifa_name);
                ioctl(fd, SIOCGIFHWADDR, &ifr);
                ::close(fd);

                uint8_t* MAC = reinterpret_cast<uint8_t*>(ifr.ifr_hwaddr.sa_data);

#else
                // Posix/FreeBSD/Mac OS
                sockaddr_dl* sdl = (struct sockaddr_dl *)current->ifa_addr;
                uint8_t* MAC = reinterpret_cast<uint8_t*>(LLADDR(sdl));

#endif
                char temp_stats[128];
                sprintf(temp_stats,"%s", (current->ifa_flags & IFF_UP) ? "Online" : "Down");
                tempNetInterface->setMac(MAC);
                tempNetInterface->setStatus(temp_stats);

               // printf("MAC       = %02x:%02x:%02x:%02x:%02x:%02x\n", MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]);
            }

            //printf("\n");
            strcpy(name_prev,current->ifa_name);
        }
        current = current->ifa_next;
    }

    freeifaddrs(ifap);
    ifap = NULL;

    ifNames = interfaceMap.keys();
    return ifNames;
}

void UDAR_Controller::decode_plot(int argc, char *argv[], char *outdir){
    FILE *fp,*fp_c,*fp_iq;
    int i;    // 0: dump udp packet, 1: dump data at offset
    char *filenameC,*filenameIQ;
    u_char *packet_data;
    uint32_t *counter = NULL;
    uint32_t *dataIQ = NULL;

    uint32_t *dataU = NULL;
    uint32_t *dataL = NULL;

    int *cjumps = NULL;
    int count,wcount,datasize,p_datasize,file_len,mode_select;

    /* We expect exactly one argument, the name of the file to dump. */
    if ( argc < 1 )
    {
      fprintf(stderr, "program requires one argument, the trace file to dump\n");
      exit(1);
    }

     if (argc<3) {
      mode_select = 0;
     } else {
      mode_select = 1;
      filenameC = argv[1];
      filenameIQ = argv[2];
    }

    fp = fopen(argv[0], "rb" );
    if (!fp){
        //fprintf(stderr,"Unable to open file\n");
        //exit(1);
        setTranscript("Error: Unable to open file..");
        return;
    }
    fseek(fp, 0, SEEK_END);
    file_len = ftell(fp);
    rewind(fp);

    if (file_len==0){
        //fprintf(stderr,"Unable to open file\n");
        //exit(1);
        setTranscript("File is empty... No data found");
        fclose(fp);
        return;
    }

    packet_data = new u_char[file_len];
    if(fread(packet_data,1,file_len,fp)!=file_len){
        fprintf(stderr, "File read error\n");
        fclose(fp);
        exit(1);
    }
    fclose(fp);
    int psize = RX_PKT_SIZE-RX_HEADER_SIZE;
    wcount = file_len/(RX_PKT_SIZE-RX_HEADER_SIZE);

    int set_counteroffset = 1;
    int set_sindex = 0;

//    datasize = decodePacket(&dataIQ,&counter,packet_data,psize,wcount,set_counteroffset,set_sindex);

    datasize = decodeDataPacket(&dataU,&dataL,packet_data,psize,wcount,set_counteroffset,set_sindex);

    if (datasize == -1) {
      //fprintf(stderr, "Decode Packet failed. Returned: %i\n" ,datasize);
      //exit(1);
      setTranscript("Decode Packet failed. Returned: -1");
      return;
    }

   // int numjumps = counterJumps(&cjumps,counter,datasize);
    int numjumps = decodeDataJumps(&cjumps,dataU,dataL, datasize);
    int nchirps = numjumps/2;

     // printf("Decoded %i out of %i packets \n",wcount,count);
     // printf("datasize: %i, counter[0]: %u, counter[end-1]: %u, numjumps: %i\n",datasize,counter[0],counter[datasize-1],numjumps);
      char statstr[128];
      sprintf(statstr,"datasize: %i,dataU[0]: %u, dataU[end-1]: %u, dataL[0]: %u, dataL[end-1]: %u, numjumps: %i\n",datasize,dataU[0],dataU[datasize-1],dataL[0],dataL[datasize-1],numjumps);
      setTranscript(statstr);

      if (mode_select == 1){
          fp_c = fopen(filenameC, "wb" );
          fp_iq = fopen(filenameIQ, "wb" );

          fwrite (dataU,sizeof(uint32_t),datasize,fp_c);
          fwrite (dataL,sizeof(uint32_t),datasize,fp_iq);

          fclose(fp_c);
          fclose(fp_iq);
      }

      int plotrng = PLOT_RANGE_LIMIT;
      if (plotrng > datasize) plotrng = datasize;

//      std::vector<uint32_t> tempVector;
//      tempVector.assign(counter, counter + plotrng);
//      plotDataC.fromStdVector(tempVector);

      plotDataI.clear();
      plotDataQ.clear();
      plotDataI2.clear();
      plotDataQ2.clear();
      plotTimeVec.clear();
      plotDataC.clear();
      plotDataC2.clear();

      u_char data_format = GetRxDataFormat();

      int cjump_ind = 0;
      int cjump_off = 0;
      if (numjumps >2) {
          cjump_ind = 1;
          cjump_off = cjumps[1];
      }

      int time_ind = 0;
      //for(i=0;i<plotrng;i++){
      for(i=cjump_off;i<plotrng;i++){
          if (i == cjumps[cjump_ind]){
              cjump_ind++;
          }
          else {
              plotDataC.append((double)dataL[i]);
              plotDataI.append((double)(*((int16_t *)dataL+2*i+1)));
              plotDataQ.append((double)(*((int16_t *)dataL+2*i)));
              plotDataC2.append((double)dataU[i]);
              plotDataI2.append((double)(*((int16_t *)dataU+2*i+1)));
              plotDataQ2.append((double)(*((int16_t *)dataU+2*i)));
              plotTimeVec.append((double)time_ind);
              time_ind++;

          }
      }

      ctrjumpsX.clear();
      ctrjumpsY.clear();
      ctrjumpsY2.clear();
      for(i=0;i<numjumps;i++){
          if (cjumps[i]>plotrng) break;
          ctrjumpsX.append((double)cjumps[i]);
          ctrjumpsY.append((double)dataL[cjumps[i]]);
          ctrjumpsY2.append((double)dataU[cjumps[i]]);
      }

      updateDataPlotIQ();

     int start_offset = 0;
     int fft_plotlen = datasize;
     if(numjumps>6){
        start_offset = cjumps[5]+1;
        fft_plotlen = cjumps[6]-1 - start_offset;
     }
     else if(numjumps>4){
        start_offset = cjumps[3]+1;
        fft_plotlen = cjumps[4]-1 - start_offset;
     }
     else if(numjumps>2){
        start_offset = cjumps[1]+1;
        fft_plotlen = cjumps[2]-1 - start_offset;
     }
     else if(numjumps>1){
        start_offset = cjumps[0]+1;
        fft_plotlen = cjumps[1]-1 - start_offset;
     }

     double *fftI, *fftQ,*fftI2, *fftQ2;;
     int lenI = fftDataI(&fftI,dataL+start_offset,fft_plotlen);
   //  int lenI = fftData(&fftI, plotDataI, fft_plotlen);     // with vectors
     int lenQ = fftDataQ(&fftQ,dataL+start_offset,fft_plotlen);
     int lenI2 = fftDataI(&fftI2,dataU+start_offset,fft_plotlen);
     int lenQ2 = fftDataQ(&fftQ2,dataU+start_offset,fft_plotlen);

     int lenIQ;
     if(lenI != lenQ){
         setTranscript("IQ Vector Length Mismatch!");
         if (lenI >lenQ) lenIQ = lenQ;
         else lenIQ = lenI;
     }
     else {
         lenIQ = lenI;
     }

     int lenIQ2;
     if(lenI2 != lenQ2){
         setTranscript("IQ Vector Length Mismatch!");
         if (lenI2 >lenQ2) lenIQ2 = lenQ2;
         else lenIQ2 = lenI2;
     }
     else {
         lenIQ2 = lenI2;
     }

     if(lenIQ != lenIQ2){
         setTranscript("IQ and IQ2 Vector Length Mismatch!");
         if (lenIQ >lenIQ2) lenIQ = lenIQ2;
         else lenIQ2 = lenIQ;
     }

     double freqstep = (double)2.0*SAMPLING_FREQ/lenIQ;

     plotfftI.clear();
     plotfftQ.clear();
     plotfftI2.clear();
     plotfftQ2.clear();
     plotfftVec.clear();
     double absI,absQ,absI2,absQ2;
     for(i=1;i<(lenIQ/2);i+=2){
         absI = sqrt(fftI[i-1]*fftI[i-1]+fftI[i]*fftI[i]);
         absQ = sqrt(fftQ[i-1]*fftQ[i-1]+fftQ[i]*fftQ[i]);
         absI2 = sqrt(fftI2[i-1]*fftI2[i-1]+fftI2[i]*fftI2[i]);
         absQ2 = sqrt(fftQ2[i-1]*fftQ2[i-1]+fftQ2[i]*fftQ2[i]);
          plotfftI.append(20.0*log10(absI));
          plotfftQ.append(20.0*log10(absQ));
          plotfftI2.append(20.0*log10(absI2));
          plotfftQ2.append(20.0*log10(absQ2));
          plotfftVec.append((double)((i-1)/2) * freqstep);
     }

     updateFFTPlotIQ();

     delete[] fftI;
     delete[] fftQ;
     delete[] fftI2;
     delete[] fftQ2;
//     delete[] counter;
//     delete[] dataIQ;
     delete[] dataU;
     delete[] dataL;
     delete[] cjumps;
//      free(counter);
//      free(dataIQ);
//      free(cjumps);

}

int UDAR_Controller::fftData(double **fft, QVector<double> &data, int datasize){
    int i;
    uint64_t n, nn, nz, len;

    nn = (uint64_t) datasize;

    // Construct double array with I at even indices and 0 at odd indices
    len = ceiling2(nn<<2);
    nz = len>>1;
    n = nn<<1;

    double *arrayIQ = new double[len];

    // generate sequences of length n with nn complex data points
    for(i=1;i<n;i+=2){
        arrayIQ[i-1] = data[((i-1)>>1)];
        arrayIQ[i] = 0;
    }
    zeroPad(arrayIQ,n,len);

    //fftCT_v2(arrayIQ,nz);

    fftR_v3(arrayIQ,nz);

    *fft = arrayIQ;
    return len;
}


int UDAR_Controller::fftDataIQ(double **fftIQ, uint32_t *dataIQ, int datasize){
    int i;
    uint64_t n, nn, nz, len;

    nn = (uint64_t) datasize;

    // Construct double array with I at even indices and Q at odd indices
    len = ceiling2(nn<<2);
    nz = len>>1;
    n = nn<<1;

    double *arrayIQ = new double[len];

    // generate sequences of length n with nn complex data points
    for(i=1;i<n;i+=2){
        arrayIQ[i-1] = (double)(*((int16_t *)dataIQ+i));
        arrayIQ[i] = (double)(*((int16_t *)dataIQ+i-1));
    }
    zeroPad(arrayIQ,n,len);

    //fftCT_v2(arrayIQ,nz);

    fftR_v3(arrayIQ,nz);

    *fftIQ = arrayIQ;

    return len;
}
int UDAR_Controller::fftDataI(double **fftI, uint32_t *dataIQ, int datasize){
    int i;
    uint64_t n, nn, nz, len;

    nn = (uint64_t) datasize;

    // Construct double array with I at even indices and 0 at odd indices
    len = ceiling2(nn<<2);
    nz = len>>1;
    n = nn<<1;

    double *arrayIQ = new double[len];

    // generate sequences of length n with nn complex data points
    for(i=1;i<n;i+=2){
        arrayIQ[i-1] = (double)(*((int16_t *)dataIQ+i));
        arrayIQ[i] = 0;
    }
    zeroPad(arrayIQ,n,len);

    //fftCT_v2(arrayIQ,nz);

    fftR_v3(arrayIQ,nz);

    *fftI = arrayIQ;
    return len;
}
int UDAR_Controller::fftDataQ(double **fftQ, uint32_t *dataIQ, int datasize){
    int i;
    uint64_t n, nn, nz, len;

    nn = (uint64_t) datasize;

    // Construct double array with Q at even indices and 0 at odd indices
    len = ceiling2(nn<<2);
    nz = len>>1;
    n = nn<<1;

    double *arrayIQ = new double[len];

    // generate sequences of length n with nn complex data points
    for(i=1;i<n;i+=2){
        arrayIQ[i-1] = (double)(*((int16_t *)dataIQ+i-1));
        arrayIQ[i] = 0;
    }
    zeroPad(arrayIQ,n,len);

    //fftCT_v2(arrayIQ,nz);

    fftR_v3(arrayIQ,nz);

    *fftQ = arrayIQ;

    return len;
}

void UDAR_Controller::read_pcap(int argc, char *argv[], char *outdir)
{
  pcap_t *pcap;
  FILE *fp,*fp_c,*fp_iq;
  const unsigned char *packet;
  char errbuf[PCAP_ERRBUF_SIZE];
  struct pcap_pkthdr header;
  int i,mode_select;    // 0: dump udp packet, 1: dump data at offset
  int offset = PCAP_HEADER_SIZE;
  int trim = 0;
  char *filename,*filenameC,*filenameIQ;
  unsigned char *packet_data;
  uint32_t *counter = NULL;
  uint32_t *dataIQ = NULL;
  int *cjumps = NULL;
  int count,wcount,datasize,p_datasize;

  /* We expect exactly one argument, the name of the file to dump. */
  if ( argc < 1 )
  {
    fprintf(stderr, "program requires one argument, the trace file to dump\n");
    exit(1);
  }

  if (argc < 2){
    mode_select = 0;
  } else if (argc<3) {
    mode_select = 1;
    filename = argv[1];
    printf("%s",argv[1]);
  }  else if (argc<4){
    mode_select = 2;
    filenameC = argv[1];
    filenameIQ = argv[2];
  } else {
    mode_select = 3;
    filename = argv[1];
    filenameC = argv[2];
    filenameIQ = argv[3];
  }

  pcap = pcap_open_offline(argv[0], errbuf);
  if (pcap == NULL) {
    fprintf(stderr, "error reading pcap file: %s\n", errbuf);
    exit(1);
  }

  /* Now just loop through extracting packets as long as we have
  * some to read.
  */
  if(mode_select==0){
    while ((packet = pcap_next(pcap, &header)) != NULL){
      dump_UDP_packet(packet, header.ts, header.caplen);
    }
  } else {
    count = 0;
    wcount = 0;
    p_datasize = PCAP_PKT_SIZE - offset - trim;
    //packet_data = (unsigned char *)malloc(PCAP_WRITE_LIM*p_datasize*sizeof(unsigned char));
    packet_data = new unsigned char[PCAP_WRITE_LIM*p_datasize];

    while ((count<PCAP_WRITE_LIM)&&((packet = pcap_next(pcap, &header)) != NULL)){
      if (header.caplen==PCAP_PKT_SIZE){
        memcpy (packet_data+wcount*p_datasize,packet+offset,header.caplen-offset-trim);
        wcount++;
      }
      count++;
    }
    if ((mode_select == 1)||(mode_select == 3)){
      fp = fopen(filename, "wb" );
      fwrite (packet_data,sizeof(char),p_datasize*wcount,fp);
      fclose(fp);

      printf("Wrote %i out of %i packets \n",wcount,count);
    }

    if ((mode_select == 2)||(mode_select == 3)){
      datasize = decodePacket(&dataIQ,&counter,packet_data,p_datasize,wcount);
      if (datasize == -1) {
        fprintf(stderr, "Decode Packet failed. Returned: %i\n" ,datasize);
        exit(1);
      }

      int numjumps = counterJumps(&cjumps,counter,datasize);

     // printf("Decoded %i out of %i packets \n",wcount,count);
     // printf("datasize: %i, counter[0]: %u, counter[end-1]: %u, numjumps: %i\n",datasize,counter[0],counter[datasize-1],numjumps);
      char statstr[128];
      sprintf(statstr,"Decoded %i out of %i packets \n",wcount,count);
      setTranscript(statstr);
      sprintf(statstr,"datasize: %i, counter[0]: %u, counter[end-1]: %u, numjumps: %i\n",datasize,counter[0],counter[datasize-1],numjumps);
      setTranscript(statstr);

      fp_c = fopen(filenameC, "wb" );
      fp_iq = fopen(filenameIQ, "wb" );

      fwrite (counter,sizeof(uint32_t),datasize,fp_c);
      fwrite (dataIQ,sizeof(uint32_t),datasize,fp_iq);

      fclose(fp_c);
      fclose(fp_iq);

      int plotrng = PLOT_RANGE_LIMIT;
      if (plotrng > datasize) plotrng = datasize;

//      std::vector<uint32_t> tempVector;
//      tempVector.assign(counter, counter + plotrng);
//      plotDataC.fromStdVector(tempVector);

      plotDataI.clear();
      plotDataQ.clear();
      plotTimeVec.clear();
      for(i=0;i<plotrng;i++){
          plotDataC.append((double)counter[i]);
          plotDataI.append((double)(*((int16_t *)dataIQ+2*i+1)));
          plotDataQ.append((double)(*((int16_t *)dataIQ+2*i)));
          plotTimeVec.append((double)i);
      }

      ctrjumpsX.clear();
      ctrjumpsY.clear();
      for(i=0;i<numjumps;i++){
          ctrjumpsX.append((double)cjumps[i]);
          ctrjumpsY.append((double)counter[cjumps[i]]);
      }

      updateDataPlotIQ();

      int start_offset = 0;
      int fft_plotlen = datasize;
      if(numjumps>3){
         start_offset = cjumps[1];
         fft_plotlen = cjumps[2] - start_offset;
      }
      else if(numjumps>2){
         start_offset = cjumps[0];
         fft_plotlen = cjumps[1] - start_offset;
      }

      double *fftI, *fftQ;
      int lenI = fftDataI(&fftI,dataIQ+start_offset,fft_plotlen);
      int lenQ = fftDataQ(&fftQ,dataIQ+start_offset,fft_plotlen);

      int lenIQ;
      if(lenI != lenQ){
          setTranscript("IQ Vector Length Mismatch!");
          if (lenI >lenQ) lenIQ = lenQ;
          else lenIQ = lenI;
      }
      else {
          lenIQ = lenI;
      }


      double freqstep = (double)SAMPLING_FREQ/lenIQ;
      plotfftI.clear();
      plotfftQ.clear();
      plotfftVec.clear();
      double absI,absQ;
      for(i=1;i<(lenIQ/2);i+=2){
          absI = sqrt(fftI[i-1]*fftI[i-1]+fftI[i]*fftI[i]);
          absQ = sqrt(fftQ[i-1]*fftQ[i-1]+fftQ[i]*fftQ[i]);
           plotfftI.append(20.0*log10(absI));
           plotfftQ.append(20.0*log10(absQ));
           plotfftVec.append((double)((i-1) * freqstep));
      }


      updateFFTPlotIQ();

      delete[] fftI;
      delete[] fftQ;
      delete[] counter;
      delete[] dataIQ;
      delete[] cjumps;
    }
    setTranscript("Data payload from pcap file:");
    setTranscript(packet_data,p_datasize);

    //free(packet_data);
  }
  // terminate
}


void UDAR_Controller::on_readPcapButton_clicked(){
    QString in_fname_qstr = ui->inputPcapFilename->text();
    QString out_fname_qstr = ui->outputPcapFilename->text();
    QString out_dir_qstr = ui->outputDirectory->text();
    QByteArray in_ba = in_fname_qstr.toLatin1();
    QByteArray out_ba = out_fname_qstr.toLatin1();
     QByteArray dir_ba = out_dir_qstr.toLatin1();
    const char* in_fname = in_ba.data();
    const char* out_fname = out_ba.data();
    char* out_dir = dir_ba.data();
    char in_fname_pcap[STR_SIZE];
    char out_fname_bin[STR_SIZE];
    char out_fname_C[STR_SIZE];
    char out_fname_IQ[STR_SIZE];

    sprintf(in_fname_pcap,"%s",in_fname);
    sprintf(out_fname_bin,"%s%s.bin",out_dir,out_fname);
    sprintf(out_fname_C,"%s%sC.bin",out_dir,out_fname);
    sprintf(out_fname_IQ,"%s%sIQ.bin",out_dir,out_fname);

    int numargs = 4;
    char *strptr[numargs];
    strptr[0] = in_fname_pcap;
    strptr[1] = out_fname_bin;
    strptr[2] = out_fname_C;
    strptr[3] = out_fname_IQ;

    read_pcap(numargs,strptr,out_dir);
}

void UDAR_Controller::on_tabWidget_a_currentChanged(int value)
{
    if (value == 0){
        ui->injectChirp_radioButton->setChecked(1);
    }
    else if (value == 1){
        ui->injectFmc150_radioButton->setChecked(1);
    }
}

void UDAR_Controller::on_chirpTuningWord_spinBox_valueChanged(int value){
    calculateChirpParams();
}
void UDAR_Controller::on_numSamples_spinBox_valueChanged(int value){
    calculateChirpParams();
}
void UDAR_Controller::on_freqOffset_spinBox_valueChanged(int value){
    calculateChirpParams();
}
void UDAR_Controller::on_clockFreq_dSpinBox_valueChanged(double value){
    calculateChirpParams();
}
void UDAR_Controller::on_phaseAccLen_spinBox_valueChanged(int value){
    calculateChirpParams();
}
void UDAR_Controller::on_adcSamples_spinBox_valueChanged(int value){
    //storeChirpParams();
}
void UDAR_Controller::on_chirpPRF_dSpinBox_valueChanged(double value){
    //storeChirpParams();
}

void UDAR_Controller::on_chirpParamsGenButton_clicked(){
    //    --------------DDS Chirp Generation Parameters-------------------
    //    -- period = 4.17 us, BW = 46.08 MHz
    //    -- 491.52 Mhz clock, 4096 samples, 16 bit phase accumulator (n = 16)
    //    -- tuning_word_coeff = 3      for BW = 46.08 MHz (2048 samples)
    //    -- tuning_word_coeff = 4      for BW = 61.44 MHz (2048 samples)
    //    -- tuning_word_coeff = 1.5    for BW = 46.08 MHz (4096 samples)
    //    -- tuning_word_coeff = 2      for BW = 61.44 MHz (4096 samples)
    //    -- Calculated Using:
    //    --    tuning_word_coeff = BW*(2^n)/(num_samples*fClock)
    //    -- Taken From:
    //    --    tuning_word_coeff = period*slope*(2^n)/(num_samples*fClock)
    //    -- Where:
    //    --    slope = BW/period
    //    --    num_samples = period*fclock
    //    --
    //    -- Note: Derived From:
    //    --    tuning_word = rect[t/period] t*slope*(2^n)/fclock
    //    -- And:
    //    --     t = sample_count*period/num_samples
    //    -- Therefore:
    //    --    tuning_word = sample_count*tuning_coeff
    //    -- Additoinally:
    //    --    min_freq = freq_offset*fclock/2^n

    int n = ui->phaseAccLen_spinBox->value();
    double fClock = ui->clockFreq_dSpinBox->value();    //MHz

    double BW = ui->chirpBW_dSpinBox->value();      //MHz
    double period = ui->chirpTime_dSpinBox->value();                      //usec
    double min_freq = ui->minFreq_dSpinBox->value();

    double two_pow_n = (double)(1<<n);
    double slope = BW/period;                               //MHz/usec

    int num_samples = (int)round(period*fClock);
    int tuning_word_coeff = (int)round((BW*two_pow_n)/(num_samples*fClock));
    int freq_offset = (int)round(two_pow_n*min_freq/fClock);

    ui->chirpTuningWord_spinBox->setValue(tuning_word_coeff);
    ui->numSamples_spinBox->setValue(num_samples);
    ui->freqOffset_spinBox->setValue(freq_offset);
}
void UDAR_Controller::on_chirpParamsResetButton_clicked(){
    int n = DEFAULT_CHIRP_PHASE_ACCUM_LEN;
    double fClock = SAMPLING_FREQ;    //MHz
    double chirp_prf = DEFAULT_CHIRP_PRF;
    int adc_sample_count = DEFAULT_ADC_SAMPLES;

    int tuning_word_coeff = DEFAULT_CHIRP_TUNING_WORD;
    int num_samples = DEFAULT_NUM_SAMPLES;
    int freq_offset = DEFAULT_FREQ_OFFSET;

    ui->chirpTuningWord_spinBox->setValue(tuning_word_coeff);
    ui->numSamples_spinBox->setValue(num_samples);
    ui->freqOffset_spinBox->setValue(freq_offset);
    ui->phaseAccLen_spinBox->setValue(n);
    ui->clockFreq_dSpinBox->setValue(fClock);

    ui->chirpPRF_dSpinBox->setValue(chirp_prf);
    ui->adcSamples_spinBox->setValue(adc_sample_count);
}

void UDAR_Controller::on_writeButton_clicked(){
    QString if_name_qstr = ui->networkInterfaces->currentText();
    //QByteArray ba = if_name_qstr.toLatin1();
    //const char* if_name = ba.data();
    //sendCommand(if_name);
    if (ui->injectWriteCmd_radioButton->isChecked()){
        if (ui->injectChirp_radioButton->isChecked()){
            storeChirpParams();
            chirp_params.command_id = genCommandIdentifier();
            sendCommand(if_name_qstr,CHIRP_WRITE_COMMAND);
        }
        else if(ui->injectFmc150_radioButton->isChecked()){
            storeFMC150Params();
            fmc150_params.command_id = genCommandIdentifier();
            sendCommand(if_name_qstr,FMC150_WRITE_COMMAND);

            // save param values
            uint32_t cmd_id = fmc150_params.command_id;
            u_char cdc_val = fmc150_params.cdce72010;
            u_char ads_val = fmc150_params.ads62p49;
            u_char dac_val = fmc150_params.dac3283;
            u_char amc_val = fmc150_params.amc7823;
            u_char chk_code1 = fmc150_params.code_check1;
            u_char chk_code2 = fmc150_params.code_check2;
            uint16_t chk_code16 = fmc150_params.code_check16;

             // Must send second command to write 0 to these registers so that later commands will be accepted
            fmc150_params.cdce72010 = 0;
            fmc150_params.ads62p49 = 0;
            fmc150_params.dac3283 = 0;
            fmc150_params.amc7823 = 0;
            fmc150_params.code_check1 = 0;
            fmc150_params.code_check2 = 0;
            fmc150_params.code_check16 = 0;

            uint32_t new_cmd_id = genCommandIdentifier();
            if (new_cmd_id == cmd_id) new_cmd_id ++;
            fmc150_params.command_id = new_cmd_id;
            sendCommand(if_name_qstr,FMC150_WRITE_COMMAND);

            // restore param values
            fmc150_params.cdce72010 = cdc_val;
            fmc150_params.ads62p49 = ads_val;
            fmc150_params.dac3283 = dac_val;
            fmc150_params.amc7823 = amc_val;
            fmc150_params.code_check1 = chk_code1;
            fmc150_params.code_check2 = chk_code2;
            fmc150_params.code_check16 = chk_code16;

        }
    }
    else if(ui->injectReadCmd_radioButton->isChecked()){
        if (ui->injectChirp_radioButton->isChecked()){
            sendCommand(if_name_qstr,CHIRP_READ_COMMAND);
        }
        else if(ui->injectFmc150_radioButton->isChecked()){
            sendCommand(if_name_qstr,FMC150_READ_COMMAND);
        }
    }
}
void UDAR_Controller::on_listenButton_clicked(){
    QString if_name_qstr = ui->networkInterfaces->currentText();
    QString out_dir_qstr = ui->recOutputDirectory->text();
    QString fname_qstr = ui->recOutputFilename->text();
    QByteArray ba = if_name_qstr.toLatin1();
    QByteArray dir_ba = out_dir_qstr.toLatin1();
    QByteArray fname_ba = fname_qstr.toLatin1();
    char* if_name = ba.data();
    char* out_dir = dir_ba.data();

    int writeToFile = ui->pktRecordCheckBox->isChecked();
    int writelimit = ui->writeLimit_spinBox->value();

    char fname[STR_SIZE];
    char outdir[STR_SIZE];
    //sprintf(fname,"readout.bin");
    if (ui->appendInterfaceCheckBox->isChecked())
        sprintf(fname,"%s_%s",if_name,fname_ba.data());
    else
        sprintf(fname,"%s",fname_ba.data());

    sprintf(outdir,"%s",dir_ba.data());

    int thread_err = interfaceMap[if_name_qstr]->initRxThreads(fname,outdir,writeToFile,writelimit);
    interfaceMap[if_name_qstr]->setPromiscMode(ui->promiscModeCheckBox->isChecked());
    if (thread_err == 0){
        char tempstr[STR_SIZE];
        sprintf(tempstr,"Started Listening on device %s...",if_name);
        setTranscript(tempstr);
     }
    else if (thread_err == 1){
        char tempstr[STR_SIZE];
        sprintf(tempstr,"Already listening on device %s",if_name);
        setTranscript(tempstr);
    }
    else
    {
        char tempstr[STR_SIZE];
        sprintf(tempstr,"Read Thread Init Failed for device %s. Returned %i",if_name,thread_err);
        setTranscript(tempstr);
    }
}
uint32_t UDAR_Controller::genCommandIdentifier(){
//    time_t rawtime;
//    time(&rawtime );
//    uint32_t seconds = (uint32_t)difftime(rawtime,start_time);
//    return seconds;
    struct timeval tp;
    gettimeofday(&tp, NULL);
    uint32_t ms_start = start_tp.tv_sec * 1000 + start_tp.tv_usec / 1000;
    uint32_t ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    ms = ms - ms_start;
    return ms;
}

void UDAR_Controller::updateRXStatus(){
 //   if (interfaceMap[ui->networkInterfaces->currentText()]->IsListening()){
        QString qstr = interfaceMap[ui->networkInterfaces->currentText()]->GetThreadStatus();
        setStatusTranscript(qstr);
//    }
}

void UDAR_Controller::on_promiscModeCheckBox_stateChanged(int state){
    interfaceMap[ui->networkInterfaces->currentText()]->setPromiscMode(state);
}

void UDAR_Controller::on_getThreadStatus_clicked(){
    QString qstr = interfaceMap[ui->networkInterfaces->currentText()]->GetThreadStatus();
    setTranscript(qstr);
}

void UDAR_Controller::on_printExtBuf_clicked(){
   int offset = RX_HEADER_SIZE;
   if (ui->printHeaderCheckBox->isChecked()) offset = 0;
   int err = interfaceMap[ui->networkInterfaces->currentText()]->PrintExtBuffer(offset);
}

void UDAR_Controller::on_killThread_clicked(){
   int err = interfaceMap[ui->networkInterfaces->currentText()]->KillThreads();
}

void UDAR_Controller::on_testButton_clicked(){
    sendTestCommand(ui->networkInterfaces->currentText());
}

void UDAR_Controller::on_plotOutputButton_clicked(){
    QString in_fname_qstr = ui->recOutputFilename->text();
    QString out_dir_qstr = ui->recOutputDirectory->text();
    QByteArray in_ba = in_fname_qstr.toLatin1();
     QByteArray dir_ba = out_dir_qstr.toLatin1();
    const char* in_fn = in_ba.data();
    const char* if_name = ui->networkInterfaces->currentText().toLatin1().data();
    char* out_dir = dir_ba.data();
    char root_fname[STR_SIZE];
    char in_fname[STR_SIZE];
    char out_fname_C[STR_SIZE];
    char out_fname_IQ[STR_SIZE];

    sscanf(in_fn,"%[^.]",root_fname);

    if (ui->appendInterfaceCheckBox->isChecked()){
        sprintf(in_fname,"%s%s_%s.bin",out_dir,if_name,root_fname);
        sprintf(out_fname_C,"%s%s_%sC.bin",out_dir,if_name,root_fname);
        sprintf(out_fname_IQ,"%s%s_%sIQ.bin",out_dir,if_name,root_fname);
    }
    else{
    sprintf(in_fname,"%s%s.bin",out_dir,root_fname);
    sprintf(out_fname_C,"%s%sC.bin",out_dir,root_fname);
    sprintf(out_fname_IQ,"%s%sIQ.bin",out_dir,root_fname);
    }

    setTranscript(in_fname);
    setTranscript(out_fname_C);
    setTranscript(out_fname_IQ);

    int numargs = 3;
    char *strptr[numargs];
    strptr[0] = in_fname;
    strptr[1] = out_fname_C;
    strptr[2] = out_fname_IQ;

    decode_plot(numargs,strptr,out_dir);

    if (ui->tabWidget_c->currentIndex() == 0){
        ui->tabWidget_c->setCurrentIndex(1);
    }
}

void UDAR_Controller::setStatusTranscript(QString text){
    ui->statusTranscript->setText(text);
}

void UDAR_Controller::setTranscript(QString text){
    ui->transcript->append(text);
    fixTranscriptPosition();
}

void UDAR_Controller::setTranscript(char * text){
    ui->transcript->append(text);
    fixTranscriptPosition();
}

void UDAR_Controller::setTranscript(int data){
    QString text = QString::number(data);
    ui->transcript->append(text);
    fixTranscriptPosition();
}
void UDAR_Controller::setTranscript(unsigned int data){
    QString text = QString::number(data);
    ui->transcript->append(text);
    fixTranscriptPosition();
}
void UDAR_Controller::setTranscript(double data){
    QString text = QString::number(data);
    ui->transcript->append(text);
    fixTranscriptPosition();
}
void UDAR_Controller::setTranscript(u_char *data, int len){
    char text[STR_SIZE];
    int i;
    sprintf(text," %02x",data[0]);
    for (i=1;i<len;i++){
        sprintf(text,"%s %02x",text,data[i]);
        if ((i+1)%16 == 0){
            ui->transcript->append(text);
            sprintf(text,"");
        }
        else if((i+1)%8==0){
            sprintf(text,"%s  ",text);
        }

    }
   ui->transcript->append(text);
   fixTranscriptPosition();
}
void UDAR_Controller::setTranscript(u_char * text){
    QString s;
    QString result = "";
    int rev = strlen(reinterpret_cast<const char*>(text));

    // Print String in Reverse order....
    for ( int i = 0; i<rev; i++)
        {
           s = QString("%1").arg(text[i],0,16);

           if(s == "0"){
              s="00";
             }
         result.append(s);

         }
   ui->transcript->append(result);
   fixTranscriptPosition();
}
void UDAR_Controller::fixTranscriptPosition(){
    //ui->transcript->moveCursor(QTextCursor::End);
    //ui->transcript->verticalScrollBar()->setValue(ui->transcript->verticalScrollBar()->maximum());
}

void UDAR_Controller::on_hex2dec_in_returnPressed(){
    QString str = ui->hex2dec_in->text();
    bool ok;
    int dec = str.toInt(&ok, 16);
    QString decstr = QString("%1").arg(dec , 0, 10);
    ui->hex2dec_out->setText(decstr);
}

void UDAR_Controller::on_dec2hex_in_returnPressed(){
    QString str = ui->dec2hex_in->text();
    bool ok;
    int hex = str.toInt(&ok, 10);
    QString hexstr = QString("%1").arg(hex , 0, 16);
    ui->dec2hex_out->setText(hexstr);


}
