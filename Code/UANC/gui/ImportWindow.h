/*
 * ImportWindow.h
 *
 *  Created on: 06.02.2017
 *      Author: Vladimir Roskin
 */

#ifndef CODE_UANC_GUI_IMPORTWINDOW_H_
#define CODE_UANC_GUI_IMPORTWINDOW_H_

#include <memory>
#include <iostream>
#include <unordered_map>
#include <algorithm>

//QT-stuff
#include <QSettings>
#include <QSignalMapper>
#include <QFileInfo>
#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

//The util for loading and saving files
#include "Code/UANC/util/DialogUtil.h"
#include "Code/UANC/gui/MainWindow.h"

//The Filemanager and the signal class
#include "Code/libs/aquila/source/SignalSource.h"
#include "Code/UANC/util/SignalManager.h"
#include "Code/UANC/util/SignalFileActor.h"

namespace uanc {
namespace gui {

//Forward declaration
class MainWindow;

class ImportWindow : public QMainWindow {

Q_OBJECT

 public:

  /** \brief Obtain a reference to the Importer window.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the main window.
   *
   * @return The shared pointer containing the Importer Window
   */
  static std::shared_ptr<ImportWindow> get();

signals:
  /** \brief: Slot that indicates that signals have been selected and loaded successfully into the
   * SignalManager
   */
  void indicesLoaded(std::vector<int> loadedIndices);

 private:

  /** \brief This resets the parameters of the import window, before new files are imported.
   */
  void resetImporter();

  /** Adds new files to list of selected files.
   * @param selectedFiles: A list of files which should be displayed in the GUI.
   *
   */
  void addFilesToSelected(QStringList selectedFiles);

  /**
   * Loads the list of recently used signals
   */
  void loadRecentlyUsedSignals();

  /**
   * Saves the list of recently used signals permanently
   */
  void saveRecentlyUsedSignals();

  /**
   * Saves the recently used directory.
   */
  void saveRecentlyUsedDirectory();

  /**
   * Loads the recently used directory.
   */
  void loadRecentlyUsedDirectory();

  /** \brief Sets up the import window.
   *
   */
  void setupGUI();

  /** \bief The default constructor
   */
  ImportWindow();

  /**
   * This function manages the LRU Queue for loaded files.
   * There are maximum RECENTLY_USED_MAX_LENGTH elements in the Queue allowed.
   * If more new Elements than the length of the queue are passed to the function, only the first
   * RECENTLY_USED_MAX_LENGTH ones are inserted.
   */
  void updateRecentlyUsed(QStringList &newElements);

  //The signal mapper for the dynamic generated buttons
  std::shared_ptr<QSignalMapper> signalMapper;

  //Layout elements
  QWidget* centralWidget;
  QVBoxLayout* mainWidgetVerticalLayout;
  QGroupBox* filesGroupBox;
  QVBoxLayout* mainWidgetGroupLayout;
  QVBoxLayout* filesMainVerticalLayout;
  QPushButton* addSelectedFilesButton;
  QVBoxLayout* filesInnerVertivalLayout;
  QScrollArea* selectedFilesScrollArea;
  QWidget* scrollAreaWidgetContents;
  QVBoxLayout* scrollAreaVerticalLayout;
  QGroupBox* RecentlyUsedGroupBox;
  QVBoxLayout* verticalLayout_10;
  QComboBox* recentlyUsedCombo;
  QGroupBox* importGroupBox;
  QVBoxLayout* verticalLayout_7;
  QCheckBox* normalizeCheckBox;
  QGroupBox* actionsGroupBox;
  QHBoxLayout* actonLayout;
  QPushButton* importButton;
  QPushButton* cancelButton;
  QStatusBar* statusBar;

  //The storage for the recently used files full path
  QStringList recentlyUsedFiles;

  //The QSetting Object for storing the recently used files.
  std::shared_ptr<QSettings> recentlyUsedSettings;

  //The recently used directory
  QString recentlyUsedDirectory;

  //The maximum length of the recently used files
  const int RECENTLY_USED_MAX_LENGTH = 5;

  //Gui-Elements for a loaded file
  struct selectedPathLoadedElements {
    QHBoxLayout *selectedEntryHorizontalLayout;
    QLineEdit *selectedEntryPathLineEdit;
    QPushButton *selectEntryRemoveButton;

    ~selectedPathLoadedElements() {
      //Remove Elements from Widget when destructed
      selectedEntryHorizontalLayout->removeWidget(selectedEntryPathLineEdit);
      selectedEntryHorizontalLayout->removeWidget(selectEntryRemoveButton);
      delete selectedEntryHorizontalLayout;
      delete selectedEntryPathLineEdit;
      delete selectEntryRemoveButton;
    }
  };

  //Hash function for the keys of the selected files
  std::hash<std::string> pathHash;

  //Maps for selected files
  std::unordered_map<size_t, std::shared_ptr<selectedPathLoadedElements> > selectedPathHashMap;

  QHBoxLayout *selectedEntryHorizontalLayout_0;
  QLineEdit *selectedEntryPath_0;
  QPushButton *selectEntryRemove_0;

  /** \brief Shared pointer to the one and only instance of ImportWindow.
   */
  static std::shared_ptr<ImportWindow> _instance;

 private slots:

  /**
   * Calls addFilesToSelected with files selected in the
   * QFileDialog.
   */
  void selectFilesFromFS();

  /**
   * Closes the window if "cancel" is clicked.
   */
  void applyCancel();

  /**
   * Imports the selected files
   */
  void importFiles();

  /**
   * adds a recently used file to selected.
   * @param index: The index of the selected recently used file.
   */
  void selectRecentlyUsedFile(int index);

  /**
   * Removes the selected file from the import list
   * @param signalIndex:
   */
  void removeSelectedSignal(QString signalIndex);

};

}
}

#endif /* CODE_UANC_GUI_IMPORTWINDOW_H_ */
