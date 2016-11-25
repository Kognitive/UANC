/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UANC_DIALOGUTIL_H
#define UANC_DIALOGUTIL_H

#include <string>

namespace uanc { namespace util {

/** \brief This class can be used to access various dialogs
 *
 * Can open various dialogs, for example an open file dialog or an open save dialog
 */
class DialogUtil {

 public:

  /** \brief Constructor basically saves the passed parent internally.
   *
   * Can be used to create a dialogutil with the specified parent
   *
   * @param parent the parent to use
   */
  DialogUtil(QWidget* parent = 0) {
    _parent = parent;
  }

  /** \brief Should basically return a path of an existing file
   *
   * This method should open a dialog and return a path to an
   * existing file
   *
   * @return The path to the choosen file.
   */
  std::string chooseLoadPath() {
    auto parent = getParent();
    // TODO Wave laden
  }

  /** \brief Should basically reutrn a path to an existing or not existent file
   *
   * This method should display a save dialog and gain a path to any file.
   *
   * @return The choosen path
   */
  std::string chooseSavePath() {
    //TODO Wave speichern
  }
 private:

  /** \brief Gives back the parent
   *
   * This basically gets used to access the parents.
   */
  QWidget* getParent() {
    return _parent;
  }

  /** \brief This field holds a pointer to the parent widget.
   *
   * This is useful to make a dialog modal.
   */
  QWidget* _parent;
};

}}

#endif //UANC_DIALOGUTIL_H
