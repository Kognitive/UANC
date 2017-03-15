//
// Created by markus on 12/12/16.
//

#include "Path.h"

namespace uanc {
namespace util {

/** \brief Passes back the filename of the given path */
std::string Path::getFileName(std::string path) {
	QFileInfo fileInfo(QString::fromStdString(path));
	QString filename(fileInfo.fileName());
	return filename.toUtf8().constData();
}
}
}
