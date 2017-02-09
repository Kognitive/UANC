/*
 * ImportWindow.cpp
 *
 *  Created on: 06.02.2017
 *      Author: Vladimir Roskin
 */

#include <Code/UANC/gui/ImportWindow.h>

namespace uanc {
namespace gui {

std::shared_ptr<ImportWindow> ImportWindow::get() {
  if (!_instance) {
    _instance = std::shared_ptr<ImportWindow>(new ImportWindow());
  }

  return _instance;

}

void ImportWindow::applyCancel() {
  this->close();
}

void ImportWindow::addSignal() {
}

void ImportWindow::loadRecentlyUsedSignals() {
}

ImportWindow::ImportWindow() {
  signalMapper = new QSignalMapper(this);
  this->setupGUI();
}

void ImportWindow::setupGUI() {

  if (this->objectName().isEmpty())
    this->setObjectName(QString::fromUtf8("MainWindow"));
  this->resize(347, 429);
  QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  this->setSizePolicy(sizePolicy);
  centralWidget = new QWidget(this);
  centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
  mainWidgetVerticalLayout = new QVBoxLayout(centralWidget);
  mainWidgetVerticalLayout->setSpacing(6);
  mainWidgetVerticalLayout->setContentsMargins(11, 11, 11, 11);
  mainWidgetVerticalLayout->setObjectName(
      QString::fromUtf8("mainWidgetVerticalLayout"));
  filesGroupBox = new QGroupBox(centralWidget);
  filesGroupBox->setObjectName(QString::fromUtf8("filesGroupBox"));
  mainWidgetGroupLayout = new QVBoxLayout(filesGroupBox);
  mainWidgetGroupLayout->setSpacing(6);
  mainWidgetGroupLayout->setContentsMargins(11, 11, 11, 11);
  mainWidgetGroupLayout->setObjectName(
      QString::fromUtf8("mainWidgetGroupLayout"));
  filesMainVerticalLayout = new QVBoxLayout();
  filesMainVerticalLayout->setSpacing(6);
  filesMainVerticalLayout->setObjectName(
      QString::fromUtf8("filesMainVerticalLayout"));

  //Button for adding new files
  addSelectedFilesButton = new QPushButton(filesGroupBox);
  addSelectedFilesButton->setObjectName(
      QString::fromUtf8("addSelectedFilesButton"));
  addSelectedFilesButton->setToolTip(
      QApplication::translate("MainWindow", "Select new input files", 0));
  addSelectedFilesButton->setStatusTip(
      QApplication::translate("MainWindow", "Select new input files", 0));
  addSelectedFilesButton->setText(
      QApplication::translate("MainWindow", "Select Wave File", 0));
  filesMainVerticalLayout->addWidget(addSelectedFilesButton);
  connect(addSelectedFilesButton, SIGNAL(clicked()), this, SLOT(addFilesToSelectes()));


  //Layout for the list of files to import
  filesInnerVertivalLayout = new QVBoxLayout();
  filesInnerVertivalLayout->setSpacing(6);
  filesInnerVertivalLayout->setObjectName(
      QString::fromUtf8("filesInnerVertivalLayout"));
  selectedFilesScrollArea = new QScrollArea(filesGroupBox);
  selectedFilesScrollArea->setObjectName(
      QString::fromUtf8("selectedFilesScrollArea"));
  selectedFilesScrollArea->setWidgetResizable(true);
  scrollAreaWidgetContents = new QWidget();
  scrollAreaWidgetContents->setObjectName(
      QString::fromUtf8("scrollAreaWidgetContents"));
  scrollAreaWidgetContents->setGeometry(QRect(0, 0, 299, 101));
  scrollAreaVerticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
  scrollAreaVerticalLayout->setSpacing(6);
  scrollAreaVerticalLayout->setContentsMargins(11, 11, 11, 11);
  scrollAreaVerticalLayout->setObjectName(QString::fromUtf8("verticalLayout_13"));

  selectedFilesScrollArea->setWidget(scrollAreaWidgetContents);
  filesInnerVertivalLayout->addWidget(selectedFilesScrollArea);

  filesMainVerticalLayout->addLayout(filesInnerVertivalLayout);

  mainWidgetGroupLayout->addLayout(filesMainVerticalLayout);

  mainWidgetVerticalLayout->addWidget(filesGroupBox);

  RecentlyUsedGroupBox = new QGroupBox(centralWidget);
  RecentlyUsedGroupBox->setObjectName(
      QString::fromUtf8("RecentlyUsedGroupBox"));
  verticalLayout_10 = new QVBoxLayout(RecentlyUsedGroupBox);
  verticalLayout_10->setSpacing(6);
  verticalLayout_10->setContentsMargins(11, 11, 11, 11);
  verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
  recentlyUsedCombo = new QComboBox(RecentlyUsedGroupBox);
  recentlyUsedCombo->setObjectName(QString::fromUtf8("recentlyUsedCombo"));

  verticalLayout_10->addWidget(recentlyUsedCombo);

  mainWidgetVerticalLayout->addWidget(RecentlyUsedGroupBox);

  importGroupBox = new QGroupBox(centralWidget);
  importGroupBox->setObjectName(QString::fromUtf8("importGroupBox"));
  verticalLayout_7 = new QVBoxLayout(importGroupBox);
  verticalLayout_7->setSpacing(6);
  verticalLayout_7->setContentsMargins(11, 11, 11, 11);
  verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
  normalizeCheckBox = new QCheckBox(importGroupBox);
  normalizeCheckBox->setObjectName(QString::fromUtf8("normalizeCheckBox"));

  verticalLayout_7->addWidget(normalizeCheckBox);

  mainWidgetVerticalLayout->addWidget(importGroupBox);

  //Layout for Cancel and Import button
  actionsGroupBox = new QGroupBox(centralWidget);
  actionsGroupBox->setObjectName(QString::fromUtf8("actionsGroupBox"));
  actonLayout = new QHBoxLayout(actionsGroupBox);
  actonLayout->setSpacing(6);
  actonLayout->setContentsMargins(11, 11, 11, 11);
  actonLayout->setObjectName(QString::fromUtf8("actonLayout"));

  //ImportButton
  importButton = new QPushButton(actionsGroupBox);
  importButton->setObjectName(QString::fromUtf8("importButton"));
  importButton->setEnabled(false);
  importButton->setToolTip(QApplication::translate("MainWindow", "Import", 0));
  importButton->setStatusTip(
      QApplication::translate("MainWindow", "Import selected files", 0));
  importButton->setWhatsThis(QString());
  importButton->setText(QApplication::translate("MainWindow", "Import", 0));
  actonLayout->addWidget(importButton);
  connect(importButton, SIGNAL(clicked()), this, SLOT(importFiles()));


  //Cancel Button
  cancelButton = new QPushButton(actionsGroupBox);
  cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
  cancelButton->setToolTip(QApplication::translate("MainWindow", "Cancel", 0));
  cancelButton->setStatusTip(
      QApplication::translate("MainWindow", "Cancel", 0));
  cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(applyCancel()));
  actonLayout->addWidget(cancelButton);

  //Add the group Box for actions
  mainWidgetVerticalLayout->addWidget(actionsGroupBox);

  this->setCentralWidget(centralWidget);
  statusBar = new QStatusBar(this);
  statusBar->setObjectName(QString::fromUtf8("statusBar"));
  this->setStatusBar(statusBar);

  //Set the captions
  this->setWindowTitle(QApplication::translate("MainWindow", "Import", 0));
  filesGroupBox->setTitle(QApplication::translate("MainWindow", "Files", 0));
  RecentlyUsedGroupBox->setTitle(
      QApplication::translate("MainWindow", "Recently used", 0));
  importGroupBox->setTitle(
      QApplication::translate("MainWindow", "Import Options", 0));
  normalizeCheckBox->setToolTip(
      QApplication::translate("MainWindow", "Normalize", 0));
  normalizeCheckBox->setStatusTip(
      QApplication::translate("MainWindow", "Normalize the amplitude to 1", 0));
  normalizeCheckBox->setText(
      QApplication::translate("MainWindow", "Normalize Input", 0));
  actionsGroupBox->setTitle(
      QApplication::translate("MainWindow", "Actions", 0));

  Qt::WindowFlags flags = windowFlags();
  this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

  //QMetaObject::connectSlotsByName(this);
}

/*
 void retranslateUi(QMainWindow *MainWindow)
 {

 } // retranslateUi
 }*/

/** \brief Shared pointer of the one and only instance of MainWindow.
 *
 * This field wraps a MainWindow inside of a shared_ptr. The main goal is that
 * there are no dangling pointer referring to MainWindow.
 */
std::shared_ptr<ImportWindow> ImportWindow::_instance = NULL;

void ImportWindow::importFiles() {

}

void ImportWindow::addFilesToSelectes() {
  // get path to multiple openable files
  util::DialogUtil dialogUtil(this);
  auto path = dialogUtil.chooseLoadableFiles();
  //Create new buttons and line edits for every input file
  for (int i = 0; i < path.length(); i++) {

    //Generate hash from the filename for the map. So every file can be only imported once.
    size_t currentHash = pathHash(path[i].toUtf8().constData());

    //Separate the path and the filename
    QFileInfo fileInfo(path[i]);
    std::string currentFilename = fileInfo.fileName().toUtf8().constData();

    //Create new elements to add to the scroll area
    std::shared_ptr<selectedPathLoadedElements> currentSelectedPath =
        std::shared_ptr<selectedPathLoadedElements>(
            new selectedPathLoadedElements { new QHBoxLayout(), new QLineEdit(
                scrollAreaWidgetContents), new QPushButton(
                scrollAreaWidgetContents) });

    //Save the element in the hashmap
    std::pair<size_t, std::shared_ptr<selectedPathLoadedElements>> currentHashPathPair(
        currentHash, currentSelectedPath);
    selectedPathHashMap.insert(currentHashPathPair);

    //Set properties of the horizontal layout
    currentSelectedPath->selectedEntryHorizontalLayout->setSpacing(6);

    //Add new entry to the scroll area
    scrollAreaVerticalLayout->addLayout(
        currentSelectedPath->selectedEntryHorizontalLayout);

    //Set properties of the line edit
    currentSelectedPath->selectedEntryHorizontalLayout->addWidget(
        currentSelectedPath->selectedEntryPathLineEdit);
    currentSelectedPath->selectedEntryPathLineEdit->setText(path[i]);
    currentSelectedPath->selectedEntryPathLineEdit->setToolTip(
    QApplication::translate("MainWindow","Path to file" , 0));
    currentSelectedPath->selectedEntryPathLineEdit->setStatusTip(
    QApplication::translate("MainWindow", ("Path to file " + currentFilename).c_str(), 0));

    //Set properties of the remove Button
    currentSelectedPath->selectedEntryHorizontalLayout->addWidget(
        currentSelectedPath->selectEntryRemoveButton);
    currentSelectedPath->selectEntryRemoveButton->setToolTip(
        QApplication::translate("MainWindow", "Remove selected file", 0));
    currentSelectedPath->selectEntryRemoveButton->setStatusTip(
        QApplication::translate("MainWindow", "Remove selected wave file", 0));
    currentSelectedPath->selectEntryRemoveButton->setText(
        QApplication::translate("MainWindow", "Remove", 0));
    //Connect the remove button using the signal mapper and the hash
    connect(currentSelectedPath->selectEntryRemoveButton, SIGNAL(clicked()),
            signalMapper, SLOT(map()));
    signalMapper->setMapping(currentSelectedPath->selectEntryRemoveButton,
                             QString::number(currentHash));
    connect(signalMapper, SIGNAL(mapped(QString)), this,
            SLOT(removeSelectedSignal(QString)));



  }
}

void ImportWindow::removeSelectedSignal(QString signalIndex) {
  //Remove the widget and the signal mapping

  //TODO: Why is there a segfault?!
  //signalMapper->removeMappings(
  //    selectedPathHashMap[static_cast<size_t>(signalIndex.toULong())]
  //        ->selectEntryRemoveButton);*/
  selectedPathHashMap.erase(static_cast<size_t> (signalIndex.toULong()));

}

}
}
