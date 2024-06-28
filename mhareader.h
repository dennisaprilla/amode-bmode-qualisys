#ifndef MHAREADER_H
#define MHAREADER_H

#include <string>
#include <vector>
#include <fstream>

class MHAReader
{
public:
    MHAReader(std::string filename);

    struct MHAHeader {
        std::string         ObjectType;
        int                 NDims;
        bool                BinaryData;
        bool                BinaryDataByteOrderMSB;
        bool                CompressedData;
        std::vector<int>    TransformMatrix;
        std::vector<int>    DimSize;
        std::vector<double> Offset;
        std::vector<int>    CenterOfRotation;
        std::string         AnatomicalOrientation;
        std::vector<double> ElementSpacing;
        std::string         ElementType;
        std::string         UltrasoundImageOrientation;
        std::string         UltrasoundImageType;
        std::string         ElementDataFile;
    };


    bool readVolumeImage();
    MHAReader::MHAHeader getMHAHeader();
    std::vector<unsigned char> getMHAVolume();

private:
    bool readHeader(const std::string &text);
    std::vector<unsigned char> zlib_decompress(const std::vector<unsigned char>& Z);

    std::vector<unsigned char> volumeimage_;

    std::string filename_;
    MHAReader::MHAHeader header_;
    std::ifstream mhaFile_;
};

#endif // MHAREADER_H
