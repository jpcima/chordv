/****************************************************************************
** Meta object code from reading C++ file 'fontchooser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fontchooser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fontchooser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FontChooser_t {
    QByteArrayData data[7];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FontChooser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FontChooser_t qt_meta_stringdata_FontChooser = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FontChooser"
QT_MOC_LITERAL(1, 12, 10), // "SelectFont"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "font"
QT_MOC_LITERAL(4, 29, 4), // "text"
QT_MOC_LITERAL(5, 34, 10), // "background"
QT_MOC_LITERAL(6, 45, 7) // "setFont"

    },
    "FontChooser\0SelectFont\0\0font\0text\0"
    "background\0setFont"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FontChooser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QFont, QMetaType::QColor, QMetaType::QColor,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FontChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FontChooser *_t = static_cast<FontChooser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SelectFont((*reinterpret_cast< QFont(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 1: _t->setFont(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FontChooser::*_t)(QFont , QColor , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FontChooser::SelectFont)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FontChooser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FontChooser.data,
      qt_meta_data_FontChooser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FontChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FontChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FontChooser.stringdata0))
        return static_cast<void*>(const_cast< FontChooser*>(this));
    return QDialog::qt_metacast(_clname);
}

int FontChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FontChooser::SelectFont(QFont _t1, QColor _t2, QColor _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
