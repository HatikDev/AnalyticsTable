#ifndef CLASSESMODEL_H
#define CLASSESMODEL_H

#include "classlabel.h"
#include "result.h"

#include <map>
#include <vector>

#include <QAbstractTableModel>

class ClassesModel : public QAbstractTableModel {

    Q_OBJECT

public:
    explicit ClassesModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void loadEthalonData(std::string datasetPath);

    void loadRealData(std::string datasetPath);

private:
    // TODO: refactor this in one class Dataset
    std::vector<ClassLabel> m_classes;

    std::vector<Result> m_ethalonResults;

    std::vector<Result> m_realResults;

    void loadPredefinedClasses(const std::string& datasetPath);

    void loadResults(const std::string& datasetPath, std::vector<Result>& results);
};

#endif // CLASSESMODEL_H