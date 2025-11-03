#ifndef MOKKA_USE_PYTHON
#define MOKKA_USE_PYTHON 0
#endif

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QKeySequence>

#include "qMokkaConfigure.h"
#include "qMokkaApplication.h"

// ---- BTK ----
#include <btkAcquisitionFileReader.h>
#include <btkAcquisition.h>

class MiniMainWindow : public QMainWindow
{
public:
  MiniMainWindow(QWidget* parent = 0)
  : QMainWindow(parent), label_(new QLabel(this))
  {
    setWindowTitle("Mokka (arm64 minimal build)");
    resize(1100, 700);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    label_->setAlignment(Qt::AlignCenter);
    label_->setText("File ▸ Open… to load a C3D");
    layout->addWidget(label_);
    central->setLayout(layout);
    setCentralWidget(central);

    QMenuBar* mb = new QMenuBar(this);
    setMenuBar(mb);
    QMenu* fileMenu = mb->addMenu("&File");

    QAction* openAct = fileMenu->addAction("Open…");
    openAct->setShortcut(QKeySequence::Open);
    QObject::connect(openAct, &QAction::triggered, this, [this]{ this->openFile(); });

    QAction* quitAct = fileMenu->addAction("Quit");
    quitAct->setShortcut(QKeySequence::Quit);
    QObject::connect(quitAct, &QAction::triggered, this, [this]{ this->close(); });

    statusBar()->showMessage("Ready");
  }

private:
  void openFile()
  {
    QString path = QFileDialog::getOpenFileName(
        this, "Open acquisition", QString(),
        "C3D files (*.c3d);;All files (*.*)");
    if (path.isEmpty()) return;

    try
    {
      btk::AcquisitionFileReader::Pointer reader = btk::AcquisitionFileReader::New();
      reader->SetFilename(path.toStdString());
      reader->Update();

      btk::Acquisition::Pointer acq = reader->GetOutput();

      int pts     = acq->GetPointNumber();
      int anas    = acq->GetAnalogNumber();
      int frames  = acq->GetPointFrameNumber();
      double rate = acq->GetPointFrequency();
      int first   = acq->GetFirstFrame();

      QString summary = QString(
          "Loaded: %1\n\n"
          "Points: %2\n"
          "Analogs: %3\n"
          "Frames: %4\n"
          "Rate: %5 Hz\n"
          "First frame: %6")
          .arg(path)
          .arg(pts)
          .arg(anas)
          .arg(frames)
          .arg(rate, 0, 'f', 3)
          .arg(first);

      label_->setText(summary);
      statusBar()->showMessage("Loaded " + path.section('/', -1), 3000);
    }
    catch (std::exception& e)
    {
      QMessageBox::critical(this, "BTK error",
                            QString("Failed to load file:\n%1").arg(e.what()));
    }
    catch (...)
    {
      QMessageBox::critical(this, "BTK error", "Failed to load file (unknown error).");
    }
  }

  QLabel* label_;
};

#if defined(_MSC_VER)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  int argc = __argc;
  char** argv = __argv;
#else
int main(int argc, char* argv[])
{
#endif
  qMokkaApplication app(argc, argv);

  MiniMainWindow win;
  win.show();

  return app.exec();
}
