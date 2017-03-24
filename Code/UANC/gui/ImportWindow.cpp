/*
 * ImportWindow.cpp
 *
 *  Created on: 06.02.2017
 *      Author: Vladimir Roskin
 */

#include <Code/UANC/gui/ImportWindow.h>

namespace uanc {
namespace gui {

void ImportWindow::applyCancel() {
  this->close();
}

ImportWindow::ImportWindow(QWidget* parent) : QDialog(parent) {
  //Initialiaze the QSettings Object with default values
  recentlyUsedSettings = std::shared_ptr<QSettings>(
      new QSettings("Gruppe 2", "Understanding Active Noise Cancelling"));
  signalMapper = std::shared_ptr<QSignalMapper>(new QSignalMapper(this));
  loadRecentlyUsedDirectory();
  this->setModal(true);
  this->setupGUI();
}

void ImportWindow::setupGUI() {

  if (this->objectName().isEmpty())
    this->setObjectName(QString::fromUtf8("MainWindow"));
  this->resize(347, 429);
  this->setGeometry(
          QStyle::alignedRect(
                  Qt::LeftToRight,
                  Qt::AlignCenter,
                  this->size(),
                  parentWidget()->window()->frameGeometry()
          )
  );
  QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  this->setSizePolicy(sizePolicy);

  mainWidgetVerticalLayout = new QVBoxLayout();
  mainWidgetVerticalLayout->setSpacing(6);
  mainWidgetVerticalLayout->setContentsMargins(11, 11, 11, 11);
  mainWidgetVerticalLayout->setObjectName(
      QString::fromUtf8("mainWidgetVerticalLayout"));

  this->setLayout(mainWidgetVerticalLayout);

  filesGroupBox = new QGroupBox();
  filesGroupBox->setObjectName(QString::fromUtf8("filesGroupBox"));
  mainWidgetVerticalLayout->addWidget(filesGroupBox);

  mainWidgetGroupLayout = new QVBoxLayout();
  mainWidgetGroupLayout->setSpacing(6);
  mainWidgetGroupLayout->setContentsMargins(11, 11, 11, 11);
  mainWidgetGroupLayout->setObjectName(
      QString::fromUtf8("mainWidgetGroupLayout"));
  filesGroupBox->setLayout(mainWidgetGroupLayout);

  filesMainVerticalLayout = new QVBoxLayout();
  filesMainVerticalLayout->setSpacing(6);
  filesMainVerticalLayout->setObjectName(
      QString::fromUtf8("filesMainVerticalLayout"));

  //Button for adding new files
  addSelectedFilesButton = new QPushButton(&*filesGroupBox);
  addSelectedFilesButton->setObjectName(
      QString::fromUtf8("addSelectedFilesButton"));
  addSelectedFilesButton->setToolTip(
      QApplication::translate("MainWindow", "Select new input files", 0));
  addSelectedFilesButton->setStatusTip(
      QApplication::translate("MainWindow", "Select new input files", 0));
  addSelectedFilesButton->setText(
      QApplication::translate("MainWindow", "Select Wave File", 0));
  filesMainVerticalLayout->addWidget(&*addSelectedFilesButton);
  connect(&*addSelectedFilesButton, SIGNAL(clicked()), this,
          SLOT(selectFilesFromFS()));
  //Layout for the list of files to import
  filesInnerVertivalLayout = new QVBoxLayout();
  //filesGroupBox->setLayout(filesInnerVertivalLayout);
  filesInnerVertivalLayout->setSpacing(6);
  filesInnerVertivalLayout->setObjectName(
      QString::fromUtf8("filesInnerVertivalLayout"));
  selectedFilesScrollArea = new QScrollArea(&*filesGroupBox);
  selectedFilesScrollArea->setObjectName(
      QString::fromUtf8("selectedFilesScrollArea"));
  selectedFilesScrollArea->setWidgetResizable(true);
  scrollAreaWidgetContents = new QWidget();
  scrollAreaWidgetContents->setObjectName(
      QString::fromUtf8("scrollAreaWidgetContents"));
  scrollAreaWidgetContents->setGeometry(QRect(0, 0, 299, 101));
  scrollAreaVerticalLayout = new QVBoxLayout(&*scrollAreaWidgetContents);
  scrollAreaVerticalLayout->setSpacing(6);
  scrollAreaVerticalLayout->setContentsMargins(11, 11, 11, 11);
  scrollAreaVerticalLayout->setObjectName(
      QString::fromUtf8("verticalLayout_13"));

  selectedFilesScrollArea->setWidget(&*scrollAreaWidgetContents);
  filesInnerVertivalLayout->addWidget(&*selectedFilesScrollArea);

  filesMainVerticalLayout->addLayout(&*filesInnerVertivalLayout);

  mainWidgetGroupLayout->addLayout(&*filesMainVerticalLayout);

  mainWidgetVerticalLayout->addWidget(&*filesGroupBox);

  //Set comboBox for recently used files
  RecentlyUsedGroupBox = new QGroupBox();
  mainWidgetVerticalLayout->addWidget(RecentlyUsedGroupBox);
  RecentlyUsedGroupBox->setObjectName(
      QString::fromUtf8("RecentlyUsedGroupBox"));
  verticalLayout_10 = new QVBoxLayout(&*RecentlyUsedGroupBox);
  verticalLayout_10->setSpacing(6);
  verticalLayout_10->setContentsMargins(11, 11, 11, 11);
  verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
  recentlyUsedCombo = new QComboBox(&*RecentlyUsedGroupBox);
  recentlyUsedCombo->setInsertPolicy(QComboBox::InsertAtTop);
  recentlyUsedCombo->setMaxCount(RECENTLY_USED_MAX_LENGTH);
  loadRecentlyUsedSignals();
  connect(&*recentlyUsedCombo, SIGNAL(activated(int)), this,
          SLOT(selectRecentlyUsedFile(int)));

  verticalLayout_10->addWidget(&*recentlyUsedCombo);

  mainWidgetVerticalLayout->addWidget(&*RecentlyUsedGroupBox);

  //Layout for Cancel and Import button
  actionsGroupBox = new QGroupBox();
  mainWidgetVerticalLayout->addWidget(actionsGroupBox);
  actionsGroupBox->setObjectName(QString::fromUtf8("actionsGroupBox"));
  actonLayout = new QHBoxLayout(&*actionsGroupBox);
  actonLayout->setSpacing(6);
  actonLayout->setContentsMargins(11, 11, 11, 11);
  actonLayout->setObjectName(QString::fromUtf8("actonLayout"));

  //ImportButton
  importButton = new QPushButton(&*actionsGroupBox);
  importButton->setObjectName(QString::fromUtf8("importButton"));
  importButton->setEnabled(false);
  importButton->setToolTip(QApplication::translate("MainWindow", "Import", 0));
  importButton->setStatusTip(
      QApplication::translate("MainWindow", "Import selected files", 0));
  importButton->setWhatsThis(QString());
  importButton->setText(QApplication::translate("MainWindow", "Import", 0));
  actonLayout->addWidget(&*importButton);
  connect(&*importButton, SIGNAL(clicked()), this, SLOT(importFiles()));

  //Cancel Button
  cancelButton = new QPushButton(&*actionsGroupBox);
  cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
  cancelButton->setToolTip(QApplication::translate("MainWindow", "Cancel", 0));
  cancelButton->setStatusTip(
      QApplication::translate("MainWindow", "Cancel", 0));
  cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
  connect(&*cancelButton, SIGNAL(clicked()), this, SLOT(applyCancel()));
  actonLayout->addWidget(&*cancelButton);

  //Add the group Box for actions
  mainWidgetVerticalLayout->addWidget(&*actionsGroupBox);


  //Set the captions
  this->setWindowTitle(QApplication::translate("MainWindow", "Import", 0));
  filesGroupBox->setTitle(QApplication::translate("MainWindow", "Files", 0));
  RecentlyUsedGroupBox->setTitle(
      QApplication::translate("MainWindow", "Recently used", 0));
  actionsGroupBox->setTitle(
      QApplication::translate("MainWindow", "Actions", 0));

  Qt::WindowFlags flags = windowFlags();
  this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
}

/** \brief Shared pointer of the one and only instance of ImportWindow.
 *
 */
std::shared_ptr<ImportWindow> ImportWindow::_instance = NULL;

void ImportWindow::importFiles() {

  std::vector<int> loadedIndices;

  //Iterate over all selected paths
  for (auto selectedFileItem : selectedPathHashMap) {
    std::string path =
        selectedFileItem.second->selectedEntryPathLineEdit->text().toUtf8()
            .constData();

    struct stat sb = {0};
    if (!stat(path.c_str(), &sb)) {
      util::SignalFileActor fileActor(path);
      auto signal = fileActor.loadData();

      // save the signal inside of the main widget
      loadedIndices.push_back(util::SignalManager::get()->addSignal(signal));
    } else {
      // if the wave file is lost an error will be shown
      QMessageBox::warning(this, "Error loading file", "Cannot find file", "", "");
      if (recentlyUsedFiles.contains(QString::fromStdString(path)))
        recentlyUsedFiles.removeOne(QString::fromStdString(path));
      saveRecentlyUsedSignals();
    }
  }

  //Remove all signals from the selected items, since they have been imported
  selectedPathHashMap.clear();

  //Send the Signal indicating that the loading was successful.
  emit indicesLoaded(loadedIndices);
  importButton->setEnabled(false);

  this->close();
}

void ImportWindow::selectFilesFromFS() {
  // get path to multiple openable files
  util::DialogUtil dialogUtil(this);
  auto path = dialogUtil.chooseLoadableFiles(recentlyUsedDirectory);
  if (path.size() > 0) {
    //Save the recently used directory
    QFileInfo fileInfo(path[0]);
    recentlyUsedDirectory = fileInfo.absolutePath();
    saveRecentlyUsedDirectory();
    addFilesToSelected(path);
  }
}

void ImportWindow::addFilesToSelected(QStringList selectedFiles) {

  //Create new buttons and line edits for every input file
  for (int i = 0; i < selectedFiles.length(); i++) {

    //Generate hash from the filename for the map. So every file can be only imported once.
    size_t currentHash = pathHash(selectedFiles[i].toUtf8().constData());

    //Check if path already in map - then do nothing
    if (selectedPathHashMap.find(currentHash) != selectedPathHashMap.end()) {
      continue;
    }

    //Separate the path and the filename
    QFileInfo fileInfo(selectedFiles[i]);
    std::string currentFilename = fileInfo.fileName().toUtf8().constData();

    //Create new elements to add to the scroll area
    std::shared_ptr<selectedPathLoadedElements> currentSelectedPath =
        std::shared_ptr<selectedPathLoadedElements>(
            new selectedPathLoadedElements { new QHBoxLayout(), new QLineEdit(
                &*scrollAreaWidgetContents), new QPushButton(
                &*scrollAreaWidgetContents) });

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
    currentSelectedPath->selectedEntryPathLineEdit->setText(selectedFiles[i]);
    currentSelectedPath->selectedEntryPathLineEdit->setToolTip(
        QApplication::translate("MainWindow", "Path to file", 0));
    currentSelectedPath->selectedEntryPathLineEdit->setStatusTip(
        QApplication::translate("MainWindow",
                                ("Path to file " + currentFilename).c_str(),
                                0));

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
            &*signalMapper, SLOT(map()));
    signalMapper->setMapping(currentSelectedPath->selectEntryRemoveButton,
                             QString::number(currentHash));
    connect(&*signalMapper, SIGNAL(mapped(QString)), this,
            SLOT(removeSelectedSignal(QString)));

  }
  //Activate the import button and update the recently used list, if new files have been added.
  if (selectedPathHashMap.size() > 0) {
    importButton->setEnabled(true);
    updateRecentlyUsed(selectedFiles);
  }
}

void ImportWindow::updateRecentlyUsed(QStringList &newElements) {
  for (int i = 0; i < newElements.size() && i < RECENTLY_USED_MAX_LENGTH; ++i) {
    //If not already in the list, push to front.
    if (recentlyUsedFiles.indexOf(newElements[i]) != -1) {
      continue;
    }
    recentlyUsedFiles.push_front(newElements[i]);

    //Insert item into combo box.
    QFileInfo fileInfo(newElements[i]);
    QString currentFilename = fileInfo.fileName();
    recentlyUsedCombo->insertItem(0, currentFilename);
    //Delete last element, if over maximum queue length
    if (recentlyUsedFiles.size() > RECENTLY_USED_MAX_LENGTH) {
      recentlyUsedFiles.erase(recentlyUsedFiles.end() - 1);
    }
  }
  saveRecentlyUsedSignals();
}

void ImportWindow::loadRecentlyUsedSignals() {
  QStringList elementsBuffer;

  //Try to load the length of the recentlyUsedSettings array
  int size = recentlyUsedSettings->beginReadArray("RecentlyUsedItems");
  for (int i = 0; i < size && i < RECENTLY_USED_MAX_LENGTH; ++i) {
    recentlyUsedSettings->setArrayIndex(i);
    //Revert the order, since it is going to be reverted during insertion
    elementsBuffer.push_front(
        recentlyUsedSettings->value("FullPath").toString());
  }
  recentlyUsedSettings->endArray();
  updateRecentlyUsed(elementsBuffer);
}

void ImportWindow::saveRecentlyUsedSignals() {
  if (recentlyUsedSettings->isWritable()) {

    //Save the recently used files, so that they can be used again.
    recentlyUsedSettings->beginWriteArray("RecentlyUsedItems");
    for (int i = 0; i < recentlyUsedFiles.size(); ++i) {
      recentlyUsedSettings->setArrayIndex(i);
      recentlyUsedSettings->setValue("FullPath", recentlyUsedFiles[i]);
    }
    recentlyUsedSettings->endArray();
    //Save the setting permanently
    recentlyUsedSettings->sync();
  }
}


void ImportWindow::removeSelectedSignal(QString signalIndex) {
  //Remove the widget and the signal mapping

  //TODO: Why is there a segfault?!
  //signalMapper->removeMappings(
  //    selectedPathHashMap[static_cast<size_t>(signalIndex.toULong())]
  //        ->selectEntryRemoveButton);*/
  selectedPathHashMap.erase(static_cast<size_t>(signalIndex.toULong()));
  //Check if there are still files which could be imported:
  if (selectedPathHashMap.size() == 0) {
    importButton->setEnabled(false);
  }
}

void ImportWindow::saveRecentlyUsedDirectory() {
  if (recentlyUsedSettings->isWritable()) {
    recentlyUsedSettings->setValue("RecentlyUsedDir", recentlyUsedDirectory);
    recentlyUsedSettings->sync();
  }
}

void ImportWindow::loadRecentlyUsedDirectory() {
  QVariant dir = recentlyUsedSettings->value("RecentlyUsedDir");
  if (!dir.isNull()) {
    recentlyUsedDirectory = dir.toString();
  } else {
    recentlyUsedDirectory = QString();
  }
}

void ImportWindow::selectRecentlyUsedFile(int index) {
  QStringList selectedFromRecentlyUsed = QStringList(
      QString(recentlyUsedFiles[index]));
  addFilesToSelected(selectedFromRecentlyUsed);
}

}
}

