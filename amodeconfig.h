#ifndef AMODECONFIG_H
#define AMODECONFIG_H

#include <map>
#include <optional>
#include <string>
#include <vector>
#include <filesystem>
#include <array>

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

    // Define a struct to hold our window data
    struct Window {
        int number;
        int group;
        std::string groupname;
        double lowerbound;
        double middle;
        double upperbound;
    };

    /**
     * @brief Constructor function, it loads the csv file directly by calling loadData() function
     */
    AmodeConfig(const std::string& filepath);

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

    /**
     * @brief To set the window configuration data with the provided probe number
     */
    void setWindowByNumber(int number, std::array<std::optional<double>, 3> window);

    /**
     * @brief To export dataWindow to a csv file in the directory provided by filename_
     */
    bool exportWindow();

private:

    /**
     * @brief For loading data, called by constructor
     */
    void loadData(const std::string& filepath);

    /**
     * @brief returns a string of current date and time
     */
    std::string getCurrentDateTime();

    std::string filepath_;              //!< a full path to the file
    std::string filename_;              //!< the name of the amode config file
    std::string filedir_;               //!< the directory to the amode config file
    std::string filepath_window;        //!< a full path to the window config file

    std::map<int, Data> dataMap;         //!< a map variable that maps index to data, used for storing the configuration data
    std::map<int, Window> dataWindow;    //!< a map variable that maps index to data, used for storing the configuration data

};

#endif // AMODECONFIG_H
