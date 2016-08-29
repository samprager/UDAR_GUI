/****************************************************************************
** Meta object code from reading C++ file 'udar_controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../udar_controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udar_controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UDAR_Controller_t {
    QByteArrayData data[60];
    char stringdata0[1285];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UDAR_Controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UDAR_Controller_t qt_meta_stringdata_UDAR_Controller = {
    {
QT_MOC_LITERAL(0, 0, 15), // "UDAR_Controller"
QT_MOC_LITERAL(1, 16, 21), // "updateInterfaceFields"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 7), // "if_name"
QT_MOC_LITERAL(4, 47, 14), // "updateRXStatus"
QT_MOC_LITERAL(5, 62, 14), // "updateDataPlot"
QT_MOC_LITERAL(6, 77, 12), // "QCustomPlot*"
QT_MOC_LITERAL(7, 90, 4), // "plot"
QT_MOC_LITERAL(8, 95, 16), // "QVector<double>&"
QT_MOC_LITERAL(9, 112, 5), // "dataX"
QT_MOC_LITERAL(10, 118, 5), // "dataY"
QT_MOC_LITERAL(11, 124, 9), // "graph_num"
QT_MOC_LITERAL(12, 134, 4), // "name"
QT_MOC_LITERAL(13, 139, 20), // "horzScrollBarChanged"
QT_MOC_LITERAL(14, 160, 5), // "value"
QT_MOC_LITERAL(15, 166, 20), // "vertScrollBarChanged"
QT_MOC_LITERAL(16, 187, 16), // "selectionChanged"
QT_MOC_LITERAL(17, 204, 10), // "mousePress"
QT_MOC_LITERAL(18, 215, 10), // "mouseWheel"
QT_MOC_LITERAL(19, 226, 21), // "horzScrollBarIChanged"
QT_MOC_LITERAL(20, 248, 21), // "vertScrollBarIChanged"
QT_MOC_LITERAL(21, 270, 21), // "horzScrollBarQChanged"
QT_MOC_LITERAL(22, 292, 21), // "vertScrollBarQChanged"
QT_MOC_LITERAL(23, 314, 21), // "horzScrollBarCChanged"
QT_MOC_LITERAL(24, 336, 21), // "vertScrollBarCChanged"
QT_MOC_LITERAL(25, 358, 24), // "horzScrollBarFFTIChanged"
QT_MOC_LITERAL(26, 383, 24), // "vertScrollBarFFTIChanged"
QT_MOC_LITERAL(27, 408, 24), // "horzScrollBarFFTQChanged"
QT_MOC_LITERAL(28, 433, 24), // "vertScrollBarFFTQChanged"
QT_MOC_LITERAL(29, 458, 13), // "xAxisIChanged"
QT_MOC_LITERAL(30, 472, 8), // "QCPRange"
QT_MOC_LITERAL(31, 481, 5), // "range"
QT_MOC_LITERAL(32, 487, 13), // "yAxisIChanged"
QT_MOC_LITERAL(33, 501, 29), // "on_tabWidget_a_currentChanged"
QT_MOC_LITERAL(34, 531, 21), // "on_testButton_clicked"
QT_MOC_LITERAL(35, 553, 22), // "on_writeButton_clicked"
QT_MOC_LITERAL(36, 576, 23), // "on_listenButton_clicked"
QT_MOC_LITERAL(37, 600, 39), // "on_chirpTuningWord_spinBox_va..."
QT_MOC_LITERAL(38, 640, 34), // "on_numSamples_spinBox_valueCh..."
QT_MOC_LITERAL(39, 675, 34), // "on_freqOffset_spinBox_valueCh..."
QT_MOC_LITERAL(40, 710, 31), // "on_chirpParamsGenButton_clicked"
QT_MOC_LITERAL(41, 742, 33), // "on_chirpParamsResetButton_cli..."
QT_MOC_LITERAL(42, 776, 34), // "on_clockFreq_dSpinBox_valueCh..."
QT_MOC_LITERAL(43, 811, 35), // "on_phaseAccLen_spinBox_valueC..."
QT_MOC_LITERAL(44, 847, 34), // "on_adcSamples_spinBox_valueCh..."
QT_MOC_LITERAL(45, 882, 33), // "on_chirpPRF_dSpinBox_valueCha..."
QT_MOC_LITERAL(46, 916, 25), // "on_readPcapButton_clicked"
QT_MOC_LITERAL(47, 942, 27), // "on_plotOutputButton_clicked"
QT_MOC_LITERAL(48, 970, 26), // "on_getThreadStatus_clicked"
QT_MOC_LITERAL(49, 997, 21), // "on_killThread_clicked"
QT_MOC_LITERAL(50, 1019, 29), // "on_calibrateIndexZero_pressed"
QT_MOC_LITERAL(51, 1049, 25), // "on_resetIndexZero_pressed"
QT_MOC_LITERAL(52, 1075, 22), // "on_printExtBuf_clicked"
QT_MOC_LITERAL(53, 1098, 35), // "on_promiscModeCheckBox_stateC..."
QT_MOC_LITERAL(54, 1134, 5), // "state"
QT_MOC_LITERAL(55, 1140, 36), // "on_plotWaveformPreviewButton_..."
QT_MOC_LITERAL(56, 1177, 29), // "on_sendWaveformButton_clicked"
QT_MOC_LITERAL(57, 1207, 27), // "on_dec2hex_in_returnPressed"
QT_MOC_LITERAL(58, 1235, 27), // "on_hex2dec_in_returnPressed"
QT_MOC_LITERAL(59, 1263, 21) // "fixTranscriptPosition"

    },
    "UDAR_Controller\0updateInterfaceFields\0"
    "\0if_name\0updateRXStatus\0updateDataPlot\0"
    "QCustomPlot*\0plot\0QVector<double>&\0"
    "dataX\0dataY\0graph_num\0name\0"
    "horzScrollBarChanged\0value\0"
    "vertScrollBarChanged\0selectionChanged\0"
    "mousePress\0mouseWheel\0horzScrollBarIChanged\0"
    "vertScrollBarIChanged\0horzScrollBarQChanged\0"
    "vertScrollBarQChanged\0horzScrollBarCChanged\0"
    "vertScrollBarCChanged\0horzScrollBarFFTIChanged\0"
    "vertScrollBarFFTIChanged\0"
    "horzScrollBarFFTQChanged\0"
    "vertScrollBarFFTQChanged\0xAxisIChanged\0"
    "QCPRange\0range\0yAxisIChanged\0"
    "on_tabWidget_a_currentChanged\0"
    "on_testButton_clicked\0on_writeButton_clicked\0"
    "on_listenButton_clicked\0"
    "on_chirpTuningWord_spinBox_valueChanged\0"
    "on_numSamples_spinBox_valueChanged\0"
    "on_freqOffset_spinBox_valueChanged\0"
    "on_chirpParamsGenButton_clicked\0"
    "on_chirpParamsResetButton_clicked\0"
    "on_clockFreq_dSpinBox_valueChanged\0"
    "on_phaseAccLen_spinBox_valueChanged\0"
    "on_adcSamples_spinBox_valueChanged\0"
    "on_chirpPRF_dSpinBox_valueChanged\0"
    "on_readPcapButton_clicked\0"
    "on_plotOutputButton_clicked\0"
    "on_getThreadStatus_clicked\0"
    "on_killThread_clicked\0"
    "on_calibrateIndexZero_pressed\0"
    "on_resetIndexZero_pressed\0"
    "on_printExtBuf_clicked\0"
    "on_promiscModeCheckBox_stateChanged\0"
    "state\0on_plotWaveformPreviewButton_clicked\0"
    "on_sendWaveformButton_clicked\0"
    "on_dec2hex_in_returnPressed\0"
    "on_hex2dec_in_returnPressed\0"
    "fixTranscriptPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UDAR_Controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      50,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  264,    2, 0x08 /* Private */,
       4,    0,  267,    2, 0x08 /* Private */,
       5,    4,  268,    2, 0x08 /* Private */,
       5,    5,  277,    2, 0x08 /* Private */,
      13,    2,  288,    2, 0x08 /* Private */,
      15,    2,  293,    2, 0x08 /* Private */,
      16,    1,  298,    2, 0x08 /* Private */,
      17,    1,  301,    2, 0x08 /* Private */,
      18,    1,  304,    2, 0x08 /* Private */,
      19,    1,  307,    2, 0x08 /* Private */,
      20,    1,  310,    2, 0x08 /* Private */,
      21,    1,  313,    2, 0x08 /* Private */,
      22,    1,  316,    2, 0x08 /* Private */,
      23,    1,  319,    2, 0x08 /* Private */,
      24,    1,  322,    2, 0x08 /* Private */,
      25,    1,  325,    2, 0x08 /* Private */,
      26,    1,  328,    2, 0x08 /* Private */,
      27,    1,  331,    2, 0x08 /* Private */,
      28,    1,  334,    2, 0x08 /* Private */,
      29,    1,  337,    2, 0x08 /* Private */,
      32,    1,  340,    2, 0x08 /* Private */,
      16,    0,  343,    2, 0x08 /* Private */,
      17,    0,  344,    2, 0x08 /* Private */,
      18,    0,  345,    2, 0x08 /* Private */,
      33,    1,  346,    2, 0x08 /* Private */,
      34,    0,  349,    2, 0x08 /* Private */,
      35,    0,  350,    2, 0x08 /* Private */,
      36,    0,  351,    2, 0x08 /* Private */,
      37,    1,  352,    2, 0x08 /* Private */,
      38,    1,  355,    2, 0x08 /* Private */,
      39,    1,  358,    2, 0x08 /* Private */,
      40,    0,  361,    2, 0x08 /* Private */,
      41,    0,  362,    2, 0x08 /* Private */,
      42,    1,  363,    2, 0x08 /* Private */,
      43,    1,  366,    2, 0x08 /* Private */,
      44,    1,  369,    2, 0x08 /* Private */,
      45,    1,  372,    2, 0x08 /* Private */,
      46,    0,  375,    2, 0x08 /* Private */,
      47,    0,  376,    2, 0x08 /* Private */,
      48,    0,  377,    2, 0x08 /* Private */,
      49,    0,  378,    2, 0x08 /* Private */,
      50,    0,  379,    2, 0x08 /* Private */,
      51,    0,  380,    2, 0x08 /* Private */,
      52,    0,  381,    2, 0x08 /* Private */,
      53,    1,  382,    2, 0x08 /* Private */,
      55,    0,  385,    2, 0x08 /* Private */,
      56,    0,  386,    2, 0x08 /* Private */,
      57,    0,  387,    2, 0x08 /* Private */,
      58,    0,  388,    2, 0x08 /* Private */,
      59,    0,  389,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 8, QMetaType::Int,    7,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 8, QMetaType::Int, QMetaType::QString,    7,    9,   10,   11,   12,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,   14,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,   14,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   54,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UDAR_Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UDAR_Controller *_t = static_cast<UDAR_Controller *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateInterfaceFields((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateRXStatus(); break;
        case 2: _t->updateDataPlot((*reinterpret_cast< QCustomPlot*(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])),(*reinterpret_cast< QVector<double>(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->updateDataPlot((*reinterpret_cast< QCustomPlot*(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])),(*reinterpret_cast< QVector<double>(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 4: _t->horzScrollBarChanged((*reinterpret_cast< QCustomPlot*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->vertScrollBarChanged((*reinterpret_cast< QCustomPlot*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->selectionChanged((*reinterpret_cast< QCustomPlot*(*)>(_a[1]))); break;
        case 7: _t->mousePress((*reinterpret_cast< QCustomPlot*(*)>(_a[1]))); break;
        case 8: _t->mouseWheel((*reinterpret_cast< QCustomPlot*(*)>(_a[1]))); break;
        case 9: _t->horzScrollBarIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->vertScrollBarIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->horzScrollBarQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->vertScrollBarQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->horzScrollBarCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->vertScrollBarCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->horzScrollBarFFTIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->vertScrollBarFFTIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->horzScrollBarFFTQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->vertScrollBarFFTQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->xAxisIChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 20: _t->yAxisIChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 21: _t->selectionChanged(); break;
        case 22: _t->mousePress(); break;
        case 23: _t->mouseWheel(); break;
        case 24: _t->on_tabWidget_a_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_testButton_clicked(); break;
        case 26: _t->on_writeButton_clicked(); break;
        case 27: _t->on_listenButton_clicked(); break;
        case 28: _t->on_chirpTuningWord_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_numSamples_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_freqOffset_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->on_chirpParamsGenButton_clicked(); break;
        case 32: _t->on_chirpParamsResetButton_clicked(); break;
        case 33: _t->on_clockFreq_dSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 34: _t->on_phaseAccLen_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_adcSamples_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->on_chirpPRF_dSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 37: _t->on_readPcapButton_clicked(); break;
        case 38: _t->on_plotOutputButton_clicked(); break;
        case 39: _t->on_getThreadStatus_clicked(); break;
        case 40: _t->on_killThread_clicked(); break;
        case 41: _t->on_calibrateIndexZero_pressed(); break;
        case 42: _t->on_resetIndexZero_pressed(); break;
        case 43: _t->on_printExtBuf_clicked(); break;
        case 44: _t->on_promiscModeCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->on_plotWaveformPreviewButton_clicked(); break;
        case 46: _t->on_sendWaveformButton_clicked(); break;
        case 47: _t->on_dec2hex_in_returnPressed(); break;
        case 48: _t->on_hex2dec_in_returnPressed(); break;
        case 49: _t->fixTranscriptPosition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
            }
            break;
        }
    }
}

const QMetaObject UDAR_Controller::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UDAR_Controller.data,
      qt_meta_data_UDAR_Controller,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UDAR_Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UDAR_Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UDAR_Controller.stringdata0))
        return static_cast<void*>(const_cast< UDAR_Controller*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UDAR_Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
