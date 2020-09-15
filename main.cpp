#include <iostream>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace std;

// https://github.com/unicode-org/cldr/blob/release-37/common/supplemental/windowsZones.xml

int main()
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml("windowsZones.xml", pt);

    boost::unordered_map<std::string, boost::unordered_set<std::string> > conversionMap;

    auto node = pt.get_child("supplementalData.windowsZones.mapTimezones");
    for (const auto& each : node) {
        std::string name = each.first.data();
        if (name != "mapZone") {
            continue;
        }

        const auto& attrs = each.second.get_child("<xmlattr>", boost::property_tree::ptree());
        std::string wName = attrs.get<std::string>("other");
        std::string idName = attrs.get<std::string>("type");

        if (!wName.empty() && !idName.empty()) {
            conversionMap[wName].insert("L\"" + idName + "\"");
        }
    }

    std::ostringstream oss;
    for (const auto& each : conversionMap) {
        std::string joined = boost::algorithm::join(each.second, ", ");
        oss << "s_abbrMapWin32Ext[L\"" << each.first << "\"] = { " << joined << " };" << std::endl;
    }

    std::cout << oss.str();

    return 0;
}
