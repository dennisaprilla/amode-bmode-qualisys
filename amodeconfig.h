#ifndef AMODECONFIG_H
#define AMODECONFIG_H

#include <map>
#include <string>
#include <vector>

/**
 * @brief AmodeConfig class is used for reading the a-mode probe configurations that is saved in a table in csv format.
 */
class AmodeConfig {
public:

    // Define a struct to hold your data.
    struct Data {
        int number;
        int group;
        std::string groupname;
        std::vector<double> local_R;
        std::vector<double> local_t;
    };

    /**
     * @brief Constructor function, it loads the csv file directly by calling loadData() function
     */
    AmodeConfig(const std::string& filename);

    /**
     * @brief To get the configuration data with the provided probe number
     */
    Data getDataByNumber(int number) const;

    /**
     * @brief To get the collection of configuration data with the provided group name
     */
    std::vector<Data> getDataByGroupName(const std::string& groupname) const;

    /**
     * @brief To get unique group names in the configuration file
     */
    std::vector<std::string> getAllGroupNames() const;

private:

    /**
     * @brief For loading data, called by constructor
     */
    void loadData(const std::string& filename);

    std::map<int, Data> dataMap;    //!< a map variable that maps index to data, used for storing the configuration data
};

#endif // AMODECONFIG_H
