#ifndef GEPETTO_GUI_PYTHONWIDGET_HH
#define GEPETTO_GUI_PYTHONWIDGET_HH

#include <gepetto/gui/fwd.hh>
#include <gepetto/gui/config-dep.hh>

#if ! GEPETTO_GUI_HAS_PYTHONQT
# error "gepetto-viewer-corba was not compile with PythonQt dependency."
#endif

#include <QVariant>
#include <QDockWidget>
#include <QLayout>
#include <QPushButton>

class PythonQtObjectPtr;
class PythonQtScriptingConsole;

namespace gepetto {
  namespace gui {
    /// \ingroup plugin
    /// Python plugin interface
    ///
    /// ## Overview
    ///
    /// A Python plugin is a Python module containing a class Plugin, with a
    /// constructor taking a pointer to the MainWindow as input.
    ///
    /// For instance, if you have
    /// \code
    /// [pyplugins]
    /// module.submodule=true
    /// \endcode
    /// in your configuration file (Settings::readSettingFile), then the Plugin
    /// class will be accessed by the GUI in a way similar to:
    ///
    /// \code{py}
    /// from module.submodule import Plugin
    /// pluginInstance = Plugin(mainWindow)
    /// \endcode
    ///
    /// Plugin can interact with the interface in following ways.
    ///
    /// ### Dock widgets:
    ///
    /// Your plugin may inherits from class \c PythonQt.QtGui.QDockWidget.
    /// In this case, an instance of the Plugin  will be added to the MainWindow
    /// as a \c QDockWidget.
    ///
    /// ### Signals and slots:
    ///
    /// The most important signals and slots you should know about are listed here.
    /// A more up-to-date list of the \ref available_in_python
    ///
    /// The following method will be automatically connected to Qt signals:
    /// \li \c Plugin.osgWidget when a new OSGWidget is created (MainWindow::viewCreated(OSGWidget*)).
    /// \li \c Plugin.resetConnection triggered when CORBA connection should be reset. **This is mandatory is you have a CORBA Client**
    /// \li \c Plugin.refreshInterface triggered when users request to refresh the interface.
    ///
    /// ### Logging information
    ///
    /// Logging can be done from Python through:
    /// \li MainWindow::log(const QString&)
    /// \li MainWindow::logError(const QString&)
    /// \li MainWindow::logJobStarted, MainWindow::logJobDone and
    ///     MainWindow::logJobFailed to inform users when
    ///     starting and finishing (Done or Failed) actions that may take some time.
    ///
    /// \sa See examples \ref pyplugins/gepetto/gui/pythonwidget.py and
    ///     \ref pyplugins/gepetto/gui/matplotlib_example.py
    class PythonWidget : public QDockWidget
    {
      Q_OBJECT
    public:
      explicit PythonWidget(QWidget *parent = 0);
      void addToContext(QString const& name, QObject *obj);
      virtual ~PythonWidget();

      /// Calls a method on each plugin that has it.
      /// \return a list of QVariant returned by each call.
      QVariantList callPluginMethod (const QString& method,
          const QVariantList& args = QVariantList(),
          const QVariantMap& kwargs = QVariantMap()) const;

    public slots:
      /// Load a plugin by importing a module
      ///
      /// This is mostly equivalent to running the following code in the Python
      /// console
      /// \code{py}
      /// import modulename
      /// pluginInstance = modulename.Plugin(mainWindow)
      /// mainWindow.addDockWidget (1, pluginInstance)
      /// # Some extra code to add dock widget toggle button to the right place.
      /// \endcode
      ///
      /// \note The module must contain a class Plugin that inherits from
      /// class PythonQt.QtGui.QDockWidget
      void loadModulePlugin(QString moduleName);
      void unloadModulePlugin(QString moduleName);
      void loadScriptPlugin(QString moduleName, QString fileName);

    private:
      void loadPlugin(QString moduleName, PythonQtObjectPtr module);
      void unloadModulePlugin(PythonQtObjectPtr module);

      void addSignalHandlersToPlugin(PythonQtObjectPtr plugin);

      PythonQtScriptingConsole* console_;
      QPushButton* button_;
      QMap<QString, PythonQtObjectPtr> modules_;

    signals:

    public slots:
      void browseFile();
    };

    /// \example pyplugins/gepetto/gui/pythonwidget.py
    /// This is an example Python Plugin for \link hpp::gui::PythonWidget \endlink. Two classes are defined:
    /// \b _NodeCreator and \b Plugin. Two signals are used: \a mainWindow.refresh()
    /// and \a osgWidget.
    /// Add this to your configuration file to load this plugin
    /// \code
    /// [pyplugins]
    /// gepetto.gui=true
    /// \endcode
    /// Then right-click on a tool bar, menu bar or title bar of dock widgets
    /// to open your window.
  } // namespace gui
} // namespace gepetto

#endif // GEPETTO_GUI_PYTHONWIDGET_HH
