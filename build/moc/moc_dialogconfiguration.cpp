/****************************************************************************
** Meta object code from reading C++ file 'dialogconfiguration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialogconfiguration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogconfiguration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogConfiguration_t {
    QByteArrayData data[8];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogConfiguration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogConfiguration_t qt_meta_stringdata_DialogConfiguration = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DialogConfiguration"
QT_MOC_LITERAL(1, 20, 15), // "LanguageChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "lang"
QT_MOC_LITERAL(4, 42, 16), // "PdfReaderChanged"
QT_MOC_LITERAL(5, 59, 4), // "Save"
QT_MOC_LITERAL(6, 64, 12), // "SetPDFReader"
QT_MOC_LITERAL(7, 77, 14) // "SelectLanguage"

    },
    "DialogConfiguration\0LanguageChanged\0"
    "\0lang\0PdfReaderChanged\0Save\0SetPDFReader\0"
    "SelectLanguage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogConfiguration[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void DialogConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogConfiguration *_t = static_cast<DialogConfiguration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LanguageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->PdfReaderChanged(); break;
        case 2: _t->Save(); break;
        case 3: _t->SetPDFReader(); break;
        case 4: _t->SelectLanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogConfiguration::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogConfiguration::LanguageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogConfiguration::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogConfiguration::PdfReaderChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogConfiguration::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogConfiguration.data,
      qt_meta_data_DialogConfiguration,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogConfiguration.stringdata0))
        return static_cast<void*>(const_cast< DialogConfiguration*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DialogConfiguration::LanguageChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DialogConfiguration::PdfReaderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
