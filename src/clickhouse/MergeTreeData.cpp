#pragma once
#include <filesystem>
#include <unordered_set>
// #include "IO/ReadBuffer.h"
using namespace std;


// void readText(ReadBuffer & buf)
// {
//     const DataTypeFactory & data_type_factory = DataTypeFactory::instance();

//     size_t count;
//     DB::readText(count, buf);
//     assertString(" columns:\n", buf);

//     String column_name;
//     String type_name;
//     for (size_t i = 0; i < count; ++i)
//     {
//         readBackQuotedStringWithSQLStyle(column_name, buf);
//         assertChar(' ', buf);
//         readString(type_name, buf);
//         assertChar('\n', buf);

//         emplace_back(column_name, data_type_factory.get(type_name));
//     }

//     assertEOF(buf);
// }



// unique_ptr<ReadBufferFromFileBase> createReadBufferFromFileBase(const string & file_name)
// {
//     try
//     {
//         auto res = std::make_unique<MMapReadBufferFromFile>(filename_, 0);
//         ProfileEvents::increment(ProfileEvents::CreatedReadBufferMMap);
//         return res;
//     }
//     catch (const ErrnoException &)
//     {
//         /// Fallback if mmap is not supported (example: pipe).
//     }

//     return std::make_unique<ReadBufferFromFile>(filename_, buffer_size_, flags_, existing_memory_, alignment);
// }

bool MergeTreeDataPart::checkDataPart(
    // const NamesAndTypesList & columns_list，
    // const string & full_relative_path) {

    // static const unordered_set<string>  files_without_checksums = {
    //     "checksums.txt", 
    //     "columns.txt",
    //     "default_compression_codec.txt"};

    // string path = full_relative_path;
    // if (!path.empty() && path.back() != '/')
    //     path += "/";

    //  columns_txt;
    // {
    //     auto buf = disk->readFile(path + "columns.txt");
    //     columns_txt.readText(*buf);
    //     assertEOF(*buf);
    // }

    // if (columns_txt != columns_list)
    //     throw Exception("Columns doesn't match in part " + path
    //         + ". Expected: " + columns_list.toString()
    //         + ". Found: " + columns_txt.toString(), ErrorCodes::CORRUPTED_DATA);

    // /// Real checksums based on contents of data. Must correspond to checksums.txt. If not - it means the data is broken.
    // IMergeTreeDataPart::Checksums checksums_data;

    // /// This function calculates checksum for both compressed and decompressed contents of compressed file.
    // auto checksum_compressed_file = [](const DiskPtr & disk_, const String & file_path)
    // {
    //     auto file_buf = disk_->readFile(file_path);
    //     HashingReadBuffer compressed_hashing_buf(*file_buf);
    //     CompressedReadBuffer uncompressing_buf(compressed_hashing_buf);
    //     HashingReadBuffer uncompressed_hashing_buf(uncompressing_buf);

    //     uncompressed_hashing_buf.ignoreAll();
    //     return IMergeTreeDataPart::Checksums::Checksum
    //     {
    //         compressed_hashing_buf.count(), compressed_hashing_buf.getHash(),
    //         uncompressed_hashing_buf.count(), uncompressed_hashing_buf.getHash()
    //     };
    // };

    // /// This function calculates only checksum of file content (compressed or uncompressed).
    // auto checksum_file = [](const DiskPtr & disk_, const String & file_path)
    // {
    //     auto file_buf = disk_->readFile(file_path);
    //     HashingReadBuffer hashing_buf(*file_buf);
    //     hashing_buf.ignoreAll();
    //     return IMergeTreeDataPart::Checksums::Checksum{hashing_buf.count(), hashing_buf.getHash()};
    // };

    // bool check_uncompressed = true;
    // /// First calculate checksums for columns data
    // for (const auto & column : columns_list)
    // {
    //     column.type->enumerateStreams([&](const IDataType::SubstreamPath & substream_path, const IDataType & /* substream_type */)
    //     {
    //         String file_name = IDataType::getFileNameForStream(column, substream_path) + ".bin";
    //         checksums_data.files[file_name] = checksum_compressed_file(disk, path + file_name);
    //     }, {});
    // }


    // /// Checksums from the rest files listed in checksums.txt. May be absent. If present, they are subsequently compared with the actual data checksums.
    // IMergeTreeDataPart::Checksums checksums_txt;

    // if (disk->exists(path + "checksums.txt"))
    // {
    //     auto buf = disk->readFile(path + "checksums.txt");
    //     checksums_txt.read(*buf);
    //     assertEOF(*buf);
    // }

    // const auto & checksum_files_txt = checksums_txt.files;
    // filesystem::directory_iterator sub_dirs(path);
    // for (auto& it : sub_dirs) {
    // {
    //     const String & file_name = it->name();
    //     auto checksum_it = checksums_data.files.find(file_name);

    //     /// Skip files that we already calculated. Also skip metadata files that are not checksummed.
    //     if (checksum_it == checksums_data.files.end() && !files_without_checksums.count(file_name))
    //     {
    //         auto txt_checksum_it = checksum_files_txt.find(file_name);
    //         if (txt_checksum_it == checksum_files_txt.end() || txt_checksum_it->second.uncompressed_size == 0)
    //         {
    //             /// The file is not compressed.
    //             checksums_data.files[file_name] = checksum_file(disk, it->path());
    //         }
    //         else /// If we have both compressed and uncompressed in txt, than calculate them
    //         {
    //             checksums_data.files[file_name] = checksum_compressed_file(disk, it->path());
    //         }
    //     }
    // }

    // if (!checksums_txt.files.empty())
    //     checksums_txt.checkEqual(checksums_data, check_uncompressed);

    // return checksums_data;
    return true;
}
