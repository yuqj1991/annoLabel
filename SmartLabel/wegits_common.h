#ifndef WEGITS_COMMON_H
#define WEGITS_COMMON_H

#include <vector>
#include <map>
#include <QString>
#include <QObject>
#include <QStringList>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

namespace AnnoTool {

class WidgtsException : public std::exception {
public:
  WidgtsException(std::string message) : message(message){};
  // 返回 message
  const char *what() const noexcept { return message.c_str(); };

private:
  // 用于存储异常的提示信息
  std::string message;
};

enum class AnnoType { Points,
                      Rectangle,
                      Segement,
                      Detection_3D,
                      Classifiy
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

class WidgetUtils : public QObject {
    Q_OBJECT
public:
   static  AnnoType getAnnoType(const QString &name) {
      if (name == "多边形_points") {
        return AnnoType::Points;
      } else if (name == "分类_classifiy") {
        return AnnoType::Classifiy;
      } else if (name == "矩形框_rect") {
        return AnnoType::Rectangle;
      } else if (name == "分割_segement") {
        return AnnoType::Segement;
      } else if (name == "3D_目标检测") {
        return AnnoType::Detection_3D;
      } else {
        throw WidgtsException(
            std::string("do not support anno_type: " + name.toStdString()));
      }
    }

    static QString ConvertJsonValue(const AnnoType &name) {
      if (name == AnnoType::Points) {
        return "多边形_points";
      } else if (name == AnnoType::Classifiy) {
        return "分类_classifiy";
      } else if (name == AnnoType::Rectangle) {
        return "矩形框_rect";
      } else if (name == AnnoType::Segement) {
        return "分割_segement";
      } else if (name == AnnoType::Detection_3D) {
        return "3D_目标检测";
      } else {
        throw WidgtsException(
            std::string("do not support anno_type"));
      }
    }

    static QString ConvertToQStringFromJsonObject(QJsonObject json_object) {
        QString result;

        auto keys = json_object.keys();
        for (auto i = 0; i < keys.size(); i++){
            result += keys[i];
            result += ": ";
            if (json_object.value(keys[i]).isObject()) {
                QString obj_result;
                QDebug str_stream(&obj_result);
                str_stream << json_object.value(keys[i]);
                result += obj_result.remove("QJsonValue(array, QJsonArray(").remove("))");
            } else if (json_object.value(keys[i]).isArray()){
                QString array_result;
                QDebug str_stream(&array_result);
                str_stream << json_object.value(keys[i]);
                result += array_result.remove("QJsonValue(array, QJsonArray(").remove("))");
            } else {
                result += json_object.value(keys[i]).toString();
            }

            result += ";\n";
        }
        return result;
    }

    static QString project_name;
    static QString images_path;
    static QString annos_path;
    static QString is_defaulted;
    static QString anno_name;
    static QString anno_type;
    static QString anno_points;
    static QString anno_attr;
    static QString anno_labels;
    static QString attr_name;
    static QString attr_map_labels;
    static QString anno_tasks;
};
}


#endif // WEGITS_COMMON_H
