#include "qMokkaCoreApplication.h"
#include "qMokkaCoreApplication_p.h"

#ifndef MOKKA_USE_PYTHON
#define MOKKA_USE_PYTHON 0
#endif

#if MOKKA_USE_PYTHON
  #include "qMokkaCorePythonManager.h"
  #include <PythonQt.h>
#endif

#include "qMokkaCoreDataManager.h"
#include "qMokkaAcquisition.h"
#include "qMokkaPoint.h"

#include <QProcess>

// Constructor
qMokkaCoreApplication::qMokkaCoreApplication(QObject* parent)
  : QObject(parent),
    d_ptr(new qMokkaCoreApplicationPrivate(this))
{
}

// Destructor
qMokkaCoreApplication::~qMokkaCoreApplication() {}

// Example initialization method
void qMokkaCoreApplication::initialize()
{
  Q_D(qMokkaCoreApplication);
#if MOKKA_USE_PYTHON
  // Only enabled when Python support is compiled in
  d->setPythonManager(new qMokkaCorePythonManager(this));
#endif
  d->setDataManager(new qMokkaCoreDataManager(this));
}
