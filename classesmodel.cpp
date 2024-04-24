#include "classesmodel.h"
#include "constants.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include <QBrush>

namespace fs = std::filesystem;

ClassesModel::ClassesModel(QObject* parent) {}

int ClassesModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(m_ethalonResults.size());
}

int ClassesModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<int>(m_classes.size());
}

QVariant ClassesModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        auto& realResults = m_realResults[index.row()].data();
        auto resultIt = realResults.find(index.column());
        size_t realCount = (resultIt == realResults.end()) ? 0 : (resultIt->second);

        auto& ethalonResults = m_ethalonResults[index.row()].data();
        auto ethalonIt = ethalonResults.find(index.column());
        size_t ethalonCount = (ethalonIt == ethalonResults.end()) ? 0 : (ethalonIt->second);

        if (ethalonCount || realCount)
            return QString("%1/%2").arg(realCount).arg(ethalonCount);
    }

    if (role == Qt::BackgroundRole) {
        auto& ethalonData = m_ethalonResults[index.row()].data();
        auto& realData = m_realResults[index.row()].data();

        // process case if only ethalon data is loaded
        auto ethalonIt = ethalonData.find(index.column());
        if (realData.empty() && ethalonIt != ethalonData.end())
            return QBrush(kOkColor);

        // process case if only real data is loaded
        auto realIt = realData.find(index.column());
        if (ethalonData.empty() && realIt != realData.end())
            return QBrush(kOkColor);

        // process case if ethalon data and real data is loaded. We must compare them
        if (ethalonIt != ethalonData.end() && realIt != realData.end()) {
            if ((*ethalonIt) == (*realIt))
                return QBrush(kOkColor);

            return QBrush(kErrorColor);
        }

        if (ethalonIt == ethalonData.end() && realIt != realData.end())
            return QBrush(kErrorColor);

        if (ethalonIt != ethalonData.end() && realIt == realData.end())
            return QBrush(kErrorColor);
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}

QVariant ClassesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section < 0 || section >= m_classes.size())
                return QVariant();

            auto& classes = m_classes[section];

            return QString("%1 (%2)").arg(classes.name().c_str()).arg(std::to_string(classes.index()).c_str());
        }

        if (orientation == Qt::Vertical) {
            if (section < 0 || section >= m_ethalonResults.size())
                return QVariant();

            return m_ethalonResults[section].name();
        }
    }

    return QVariant();
}

void ClassesModel::loadEthalonData(std::string datasetPath)
{
    loadPredefinedClasses(datasetPath); // TODO: make loading predefined classes clever

    loadResults(datasetPath, m_ethalonResults);
}

void ClassesModel::loadRealData(std::string datasetPath)
{
    loadPredefinedClasses(datasetPath);

    loadResults(datasetPath, m_realResults);
}

void ClassesModel::loadPredefinedClasses(const std::string& datasetPath)
{
    std::ifstream file(datasetPath + "/predefined_classes.txt");
    if (!file)
        throw std::exception("Can't find predefined classes file"); // TableException("Can't find predefined classes file");

    m_classes.clear();

    std::string line;
    size_t index;
    std::string classLabel;
    while (getline(file, line)) {
        std::stringstream ss;
        ss << line;
        ss >> index;
        getline(ss, classLabel);

        m_classes.push_back({ classLabel, index });
    }
}

void ClassesModel::loadResults(const std::string& datasetPath, std::vector<Result>& results)
{
    std::vector<std::string> resultsFiles;
    for (const auto& entry : fs::directory_iterator(datasetPath + "/images_labels/"))
        resultsFiles.push_back(entry.path().stem().string());

    size_t index;
    results.reserve(resultsFiles.size());
    for (auto& file : resultsFiles) {
        std::ifstream fis(datasetPath + "/images_labels/" + file + ".txt");

        std::string line;
        results.push_back(Result(file.c_str()));
        while (getline(fis, line)) {
            std::stringstream ss;
            ss << line;
            ss >> index;

            results.back().add(index);
        }
    }
}
