/****************************************************************************
** Meta object code from reading C++ file 'containerserver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../containerserver/containerserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'containerserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContainerServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      42,   29,   16,   16, 0x05,
      81,   67,   16,   16, 0x05,
     128,  106,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     161,   16,   16,   16, 0x08,
     179,   16,   16,   16, 0x08,
     205,  193,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ContainerServer[] = {
    "ContainerServer\0\0listening()\0errorMessage\0"
    "connectionError(QString)\0clientAddress\0"
    "clientConnected(QString)\0message,clientAddress\0"
    "messageReceived(QString,QString)\0"
    "onNewConnection()\0onReadyRead()\0"
    "socketError\0onError(QAbstractSocket::SocketError)\0"
};

void ContainerServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ContainerServer *_t = static_cast<ContainerServer *>(_o);
        switch (_id) {
        case 0: _t->listening(); break;
        case 1: _t->connectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->clientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onNewConnection(); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ContainerServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ContainerServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ContainerServer,
      qt_meta_data_ContainerServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContainerServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContainerServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContainerServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContainerServer))
        return static_cast<void*>(const_cast< ContainerServer*>(this));
    return QObject::qt_metacast(_clname);
}

int ContainerServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ContainerServer::listening()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ContainerServer::connectionError(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ContainerServer::clientConnected(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ContainerServer::messageReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
