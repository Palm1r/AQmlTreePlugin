#include "treemodel.h"
#include <QtTest/QTest>

class TreeModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testRowCount();
    void testColumnCount();
    void testAddTreeItem();
    void testRemoveItemByIndex();
    void testRootItem();

private:
    TreeModel *model;
};

void TreeModelTest::initTestCase()
{
    model = new TreeModel();
}

void TreeModelTest::cleanupTestCase()
{
    delete model;
}

void TreeModelTest::testRowCount()
{
    int rowCount = model->rowCount(QModelIndex());
    QCOMPARE(rowCount, 0);
}

void TreeModelTest::testColumnCount()
{
    int columnCount = model->columnCount(QModelIndex());
    QCOMPARE(columnCount, 1);
}

void TreeModelTest::testAddTreeItem()
{
    QVariant data("Test Data");
    auto root = model->rootItem();
    model->addTreeItem(root, data);
    QCOMPARE(model->rowCount(QModelIndex()), 1);
}

void TreeModelTest::testRemoveItemByIndex()
{
    auto root = model->rootItem();
    model->removeItemByIndex(root, 0);
    QCOMPARE(model->rowCount(QModelIndex()), 0);
}

void TreeModelTest::testRootItem()
{
    auto root = model->rootItem();
    QVERIFY(root != nullptr);
}

QTEST_MAIN(TreeModelTest)
#include "tst_treemodeltest.moc"
