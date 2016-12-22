/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * PerformanceMeasureTest.cc
 *
 *  Created on: 16.12.2016
 *      Author: Vladimir Roskin
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <iostream>
#include <QCoreApplication>
#include "../UANC/algorithm/PerformanceMeasure.h"
#include <QtTest/QtTest>

using namespace uanc::algorithm;

class TestQString: public QObject
{
    Q_OBJECT
private slots:
  void measureTest();
};

void TestQString::measureTest()
{
  PerformanceMeasure <>* testMeasure = new PerformanceMeasure <> ();
  testMeasure->start("TestMeasure");
  std::this_thread::sleep_for (std::chrono::seconds(1));
  testMeasure->startSubMeasure("TestSubMeasure1");
  std::this_thread::sleep_for (std::chrono::seconds(1));
  testMeasure->restart();
  std::this_thread::sleep_for (std::chrono::seconds(2));
  testMeasure->start("SubMeasure2");
  std::this_thread::sleep_for (std::chrono::seconds(1));
  testMeasure->stopAllMeasurements();

  //Get the root measurement node
  std::shared_ptr<PerformanceMeasureNode<> > testNode = testMeasure->getRootMeasure();

  //Test the first measurement
  QVERIFY(testNode->measureTitle == "TestMeasure");
  //Round the measurement to seconds
  QVERIFY((testNode->getNodeDuration().count())/1000000 == 5);

  //Test the first sub-measurement
  testNode = testNode->measureSubMeasureChild;
  QVERIFY(testNode->measureTitle == "TestSubMeasure1");
  QVERIFY((testNode->getNodeDuration().count())/1000000 == 2);

  //Test the subsequent sub-measure
  testNode = testNode->subsequentMeasure;
  QVERIFY(testNode->measureTitle == "SubMeasure2");
  QVERIFY((testNode->getNodeDuration().count())/1000000 == 1);



}


QTEST_MAIN(TestQString)
#include "PerformanceMeasureTest.moc"
