#ifndef WEGITS_COMMON_H
#define WEGITS_COMMON_H

#include <vector>
#include <map>
#include <QString>
#include <QStringList>

namespace AnnoTool {
enum class AnnoType {
    Points,
    Rectangle,
    Segement
};

struct attribute_desc_ {
    QString attri_name;
    QString default_value;
};

struct task_desc_ {
    QString stask_name;
    AnnoType anno_type;
    int points_num = 0;
    QStringList anno_labels;
    std::map<QString,  attribute_desc_> label_attri_map_;
};

struct anno_desc_ {
    std::vector<task_desc_> anno_desc_list_;
};



}


#endif // WEGITS_COMMON_H
