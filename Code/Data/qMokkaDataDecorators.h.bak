/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2013, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __qMokkaDataDecorators_h
#define __qMokkaDataDecorators_h

#include "qMokkaAcquisition.h"
#include "qMokkaPoint.h"
#include "qMokkaAnalog.h"
#include "qMokkaEvent.h"
#include "qMokkaForcePlate.h"
#include "qMokkaIMU.h"
#include "qMokkaVideo.h"

#include <QObject>

// --- Disable Python bits when MOKKA_USE_PYTHON is OFF ---
#ifndef MOKKA_USE_PYTHON
#define MOKKA_USE_PYTHON 0
#endif

#if MOKKA_USE_PYTHON
  #include <PythonQt.h>
#endif

#if MOKKA_USE_PYTHON

class qMokkaDataDecorators : public QObject
{
  Q_OBJECT
public:
  qMokkaDataDecorators()
  {
    PythonQt::self()->registerClass(&qMokkaAcquisition::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaPoint::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaAnalog::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaEvent::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaForcePlate::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaIMU::staticMetaObject);
    PythonQt::self()->registerClass(&qMokkaVideo::staticMetaObject);
  }
};

#else  // MOKKA_USE_PYTHON == 0

// Stub that satisfies the rest of the code when Python is disabled
class qMokkaDataDecorators : public QObject
{
  Q_OBJECT
public:
  qMokkaDataDecorators() {}
};

#endif // MOKKA_USE_PYTHON

#endif // __qMokkaDataDecorators_h
