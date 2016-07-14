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
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udar_controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UDAR_Controller_t {
    QByteArrayData data[43];
    char stringdata0[972];
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
QT_MOC_LITERAL(4, 47, 21), // "horzScrollBarIChanged"
QT_MOC_LITERAL(5, 69, 5), // "value"
QT_MOC_LITERAL(6, 75, 21), // "vertScrollBarIChanged"
QT_MOC_LITERAL(7, 97, 21), // "horzScrollBarQChanged"
QT_MOC_LITERAL(8, 119, 21), // "vertScrollBarQChanged"
QT_MOC_LITERAL(9, 141, 21), // "horzScrollBarCChanged"
QT_MOC_LITERAL(10, 163, 21), // "vertScrollBarCChanged"
QT_MOC_LITERAL(11, 185, 24), // "horzScrollBarFFTIChanged"
QT_MOC_LITERAL(12, 210, 24), // "vertScrollBarFFTIChanged"
QT_MOC_LITERAL(13, 235, 24), // "horzScrollBarFFTQChanged"
QT_MOC_LITERAL(14, 260, 24), // "vertScrollBarFFTQChanged"
QT_MOC_LITERAL(15, 285, 13), // "xAxisIChanged"
QT_MOC_LITERAL(16, 299, 8), // "QCPRange"
QT_MOC_LITERAL(17, 308, 5), // "range"
QT_MOC_LITERAL(18, 314, 13), // "yAxisIChanged"
QT_MOC_LITERAL(19, 328, 16), // "selectionChanged"
QT_MOC_LITERAL(20, 345, 10), // "mousePress"
QT_MOC_LITERAL(21, 356, 10), // "mouseWheel"
QT_MOC_LITERAL(22, 367, 29), // "on_tabWidget_a_currentChanged"
QT_MOC_LITERAL(23, 397, 21), // "on_testButton_clicked"
QT_MOC_LITERAL(24, 419, 22), // "on_writeButton_clicked"
QT_MOC_LITERAL(25, 442, 23), // "on_listenButton_clicked"
QT_MOC_LITERAL(26, 466, 39), // "on_chirpTuningWord_spinBox_va..."
QT_MOC_LITERAL(27, 506, 34), // "on_numSamples_spinBox_valueCh..."
QT_MOC_LITERAL(28, 541, 34), // "on_freqOffset_spinBox_valueCh..."
QT_MOC_LITERAL(29, 576, 31), // "on_chirpParamsGenButton_clicked"
QT_MOC_LITERAL(30, 608, 33), // "on_chirpParamsResetButton_cli..."
QT_MOC_LITERAL(31, 642, 34), // "on_clockFreq_dSpinBox_valueCh..."
QT_MOC_LITERAL(32, 677, 35), // "on_phaseAccLen_spinBox_valueC..."
QT_MOC_LITERAL(33, 713, 34), // "on_adcSamples_spinBox_valueCh..."
QT_MOC_LITERAL(34, 748, 33), // "on_chirpPRF_dSpinBox_valueCha..."
QT_MOC_LITERAL(35, 782, 25), // "on_readPcapButton_clicked"
QT_MOC_LITERAL(36, 808, 27), // "on_plotOutputButton_clicked"
QT_MOC_LITERAL(37, 836, 26), // "on_getThreadStatus_clicked"
QT_MOC_LITERAL(38, 863, 21), // "on_killThread_clicked"
QT_MOC_LITERAL(39, 885, 22), // "on_printExtBuf_clicked"
QT_MOC_LITERAL(40, 908, 35), // "on_promiscModeCheckBox_stateC..."
QT_MOC_LITERAL(41, 944, 5), // "state"
QT_MOC_LITERAL(42, 950, 21) // "fixTranscirptPosition"

    },
    "UDAR_Controller\0updateInterfaceFields\0"
    "\0if_name\0horzScrollBarIChanged\0value\0"
    "vertScrollBarIChanged\0horzScrollBarQChanged\0"
    "vertScrollBarQChanged\0horzScrollBarCChanged\0"
    "vertScrollBarCChanged\0horzScrollBarFFTIChanged\0"
    "vertScrollBarFFTIChanged\0"
    "horzScrollBarFFTQChanged\0"
    "vertScrollBarFFTQChanged\0xAxisIChanged\0"
    "QCPRange\0range\0yAxisIChanged\0"
    "selectionChanged\0mousePress\0mouseWheel\0"
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
    "on_killThread_clicked\0on_printExtBuf_clicked\0"
    "on_promiscModeCheckBox_stateChanged\0"
    "state\0fixTranscirptPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UDAR_Controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  194,    2, 0x08 /* Private */,
       4,    1,  197,    2, 0x08 /* Private */,
       6,    1,  200,    2, 0x08 /* Private */,
       7,    1,  203,    2, 0x08 /* Private */,
       8,    1,  206,    2, 0x08 /* Private */,
       9,    1,  209,    2, 0x08 /* Private */,
      10,    1,  212,    2, 0x08 /* Private */,
      11,    1,  215,    2, 0x08 /* Private */,
      12,    1,  218,    2, 0x08 /* Private */,
      13,    1,  221,    2, 0x08 /* Private */,
      14,    1,  224,    2, 0x08 /* Private */,
      15,    1,  227,    2, 0x08 /* Private */,
      18,    1,  230,    2, 0x08 /* Private */,
      19,    0,  233,    2, 0x08 /* Private */,
      20,    0,  234,    2, 0x08 /* Private */,
      21,    0,  235,    2, 0x08 /* Private */,
      22,    1,  236,    2, 0x08 /* Private */,
      23,    0,  239,    2, 0x08 /* Private */,
      24,    0,  240,    2, 0x08 /* Private */,
      25,    0,  241,    2, 0x08 /* Private */,
      26,    1,  242,    2, 0x08 /* Private */,
      27,    1,  245,    2, 0x08 /* Private */,
      28,    1,  248,    2, 0x08 /* Private */,
      29,    0,  251,    2, 0x08 /* Private */,
      30,    0,  252,    2, 0x08 /* Private */,
      31,    1,  253,    2, 0x08 /* Private */,
      32,    1,  256,    2, 0x08 /* Private */,
      33,    1,  259,    2, 0x08 /* Private */,
      34,    1,  262,    2, 0x08 /* Private */,
      35,    0,  265,    2, 0x08 /* Private */,
      36,    0,  266,    2, 0x08 /* Private */,
      37,    0,  267,    2, 0x08 /* Private */,
      38,    0,  268,    2, 0x08 /* Private */,
      39,    0,  269,    2, 0x08 /* Private */,
      40,    1,  270,    2, 0x08 /* Private */,
      42,    0,  273,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   41,
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
        case 1: _t->horzScrollBarIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->vertScrollBarIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->horzScrollBarQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->vertScrollBarQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->horzScrollBarCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->vertScrollBarCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->horzScrollBarFFTIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->vertScrollBarFFTIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->horzScrollBarFFTQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->vertScrollBarFFTQChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->xAxisIChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 12: _t->yAxisIChanged((*reinterpret_cast< QCPRange(*)>(_a[1]))); break;
        case 13: _t->selectionChanged(); break;
        case 14: _t->mousePress(); break;
        case 15: _t->mouseWheel(); break;
        case 16: _t->on_tabWidget_a_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_testButton_clicked(); break;
        case 18: _t->on_writeButton_clicked(); break;
        case 19: _t->on_listenButton_clicked(); break;
        case 20: _t->on_chirpTuningWord_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_numSamples_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_freqOffset_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_chirpParamsGenButton_clicked(); break;
        case 24: _t->on_chirpParamsResetButton_clicked(); break;
        case 25: _t->on_clockFreq_dSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->on_phaseAccLen_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_adcSamples_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_chirpPRF_dSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->on_readPcapButton_clicked(); break;
        case 30: _t->on_plotOutputButton_clicked(); break;
        case 31: _t->on_getThreadStatus_clicked(); break;
        case 32: _t->on_killThread_clicked(); break;
        case 33: _t->on_printExtBuf_clicked(); break;
        case 34: _t->on_promiscModeCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->fixTranscirptPosition(); break;
        default: ;
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
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
