/****************************************************************************
** Meta object code from reading C++ file 'formconfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../formconfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormConfig_t {
    QByteArrayData data[15];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormConfig_t qt_meta_stringdata_FormConfig = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FormConfig"
QT_MOC_LITERAL(1, 11, 7), // "sendLog"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "message"
QT_MOC_LITERAL(4, 28, 8), // "setCover"
QT_MOC_LITERAL(5, 37, 11), // "displayFont"
QT_MOC_LITERAL(6, 49, 4), // "font"
QT_MOC_LITERAL(7, 54, 4), // "text"
QT_MOC_LITERAL(8, 59, 10), // "background"
QT_MOC_LITERAL(9, 70, 12), // "displayThumb"
QT_MOC_LITERAL(10, 83, 5), // "image"
QT_MOC_LITERAL(11, 89, 11), // "SizeChanged"
QT_MOC_LITERAL(12, 101, 4), // "size"
QT_MOC_LITERAL(13, 106, 8), // "FindSize"
QT_MOC_LITERAL(14, 115, 16) // "deleteCoverImage"

    },
    "FormConfig\0sendLog\0\0message\0setCover\0"
    "displayFont\0font\0text\0background\0"
    "displayThumb\0image\0SizeChanged\0size\0"
    "FindSize\0deleteCoverImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x08 /* Private */,
       5,    3,   60,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      11,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,
      13,    1,   76,    2, 0x08 /* Private */,
      14,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QFont, QMetaType::QColor, QMetaType::QColor,    6,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void FormConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormConfig *_t = static_cast<FormConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setCover((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->displayFont((*reinterpret_cast< QFont(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 3: _t->displayThumb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SizeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->SizeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->FindSize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->deleteCoverImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormConfig::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormConfig::sendLog)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FormConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormConfig.data,
      qt_meta_data_FormConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FormConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FormConfig.stringdata0))
        return static_cast<void*>(const_cast< FormConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FormConfig::sendLog(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
