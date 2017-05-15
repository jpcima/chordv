/****************************************************************************
** Meta object code from reading C++ file 'dialogchorddefinition.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialogchorddefinition.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogchorddefinition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogChordDefinition_t {
    QByteArrayData data[14];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogChordDefinition_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogChordDefinition_t qt_meta_stringdata_DialogChordDefinition = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DialogChordDefinition"
QT_MOC_LITERAL(1, 22, 5), // "Error"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "message"
QT_MOC_LITERAL(4, 37, 10), // "ShowChords"
QT_MOC_LITERAL(5, 48, 10), // "chordnames"
QT_MOC_LITERAL(6, 59, 12), // "chortdstring"
QT_MOC_LITERAL(7, 72, 9), // "ShowChord"
QT_MOC_LITERAL(8, 82, 5), // "index"
QT_MOC_LITERAL(9, 88, 6), // "Import"
QT_MOC_LITERAL(10, 95, 12), // "ChordClicked"
QT_MOC_LITERAL(11, 108, 11), // "ModifyChord"
QT_MOC_LITERAL(12, 120, 11), // "DeleteChord"
QT_MOC_LITERAL(13, 132, 8) // "AddChord"

    },
    "DialogChordDefinition\0Error\0\0message\0"
    "ShowChords\0chordnames\0chortdstring\0"
    "ShowChord\0index\0Import\0ChordClicked\0"
    "ModifyChord\0DeleteChord\0AddChord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogChordDefinition[] = {

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
       4,    2,   57,    2, 0x09 /* Protected */,
       7,    1,   62,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,
      12,    0,   70,    2, 0x08 /* Private */,
      13,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QModelIndex,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogChordDefinition::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogChordDefinition *_t = static_cast<DialogChordDefinition *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ShowChords((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->ShowChord((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->Import(); break;
        case 4: _t->ChordClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->ModifyChord(); break;
        case 6: _t->DeleteChord(); break;
        case 7: _t->AddChord(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogChordDefinition::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogChordDefinition::Error)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DialogChordDefinition::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogChordDefinition.data,
      qt_meta_data_DialogChordDefinition,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogChordDefinition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogChordDefinition::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogChordDefinition.stringdata0))
        return static_cast<void*>(const_cast< DialogChordDefinition*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogChordDefinition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DialogChordDefinition::Error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
