// Copyright (c) 2018 CNRS
// Authors: Joseph Mirabel
//
//
// This file is part of gepetto-viewer-corba
// gepetto-viewer-corba is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// gepetto-viewer-corba is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// gepetto-viewer-corba  If not, see
// <http://www.gnu.org/licenses/>.

#include <plugin.hh>

#include <decorator.hh>
#include <gepetto/gui/config-dep.hh>

namespace PyQCustomPlot {
  void Plugin::init() {
#if GEPETTO_GUI_HAS_PYTHONQT
    registerQCustomPlot();
#else
    qWarning() << "Cannot load pyqcustomplot plugin without PythonQt support.";
#endif
  }

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
  Q_EXPORT_PLUGIN2 (pyqcustomplot, Plugin)
#endif
} // namespace PyQCustomPlot
