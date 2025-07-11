// hyperscan_example.cpp
#include <hs.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

// 匹配回调函数
static int on_match(unsigned int id, unsigned long long from,
                    unsigned long long to, unsigned int flags, void *ctx) {
    std::cout << "Matched pattern ID " << id << " from "
              << from << " to " << to << std::endl;
    return 0; // 继续匹配
}

// 编译并保存数据库
bool compile_and_save(const char* filename) {
    hs_database_t* db = nullptr;
    hs_compile_error_t* compile_err = nullptr;
    
    // 定义要编译的正则表达式
    const char* patterns[] = {"test.*pattern", "\\d{3,}", "hyperscan"};
    unsigned flags[] = {HS_FLAG_DOTALL, HS_FLAG_SOM_LEFTMOST, HS_FLAG_CASELESS};
    unsigned ids[] = {1001, 1002, 1003}; // 自定义模式ID

    // 编译多个正则表达式
    hs_error_t err = hs_compile_multi(patterns, flags, ids, 3, HS_MODE_BLOCK,
                                      nullptr, &db, &compile_err);

    if (err != HS_SUCCESS) {
        std::cerr << "Compile error: " << compile_err->message << std::endl;
        hs_free_compile_error(compile_err);
        return false;
    }

    // 序列化数据库
    char* serialized_data;
    size_t data_size;
    if ((err = hs_serialize_database(db, &serialized_data, &data_size)) != HS_SUCCESS) {
        std::cerr << "Serialize error: " << err << std::endl;
        hs_free_database(db);
        return false;
    }

    // 写入文件
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.write(serialized_data, data_size)) {
        std::cerr << "File write error" << std::endl;
        hs_free_database(db);
        free(serialized_data);
        return false;
    }

    // 清理资源
    hs_free_database(db);
    free(serialized_data);
    std::cout << "Database saved: " << filename 
              << " (" << data_size << " bytes)" << std::endl;
    return true;
}

// 加载并扫描数据库
bool load_and_scan(const char* filename, const char* input) {
    // 读取文件
    std::ifstream infile(filename, std::ios::binary | std::ios::ate);
    if (!infile) {
        std::cerr << "File not found: " << filename << std::endl;
        return false;
    }

    size_t data_size = infile.tellg();
    infile.seekg(0, std::ios::beg);

    std::vector<char> buffer(data_size);
    if (!infile.read(buffer.data(), data_size)) {
        std::cerr << "File read error" << std::endl;
        return false;
    }

    // 反序列化数据库
    hs_database_t* db = nullptr;
    hs_error_t err = hs_deserialize_database(buffer.data(), data_size, &db);
    if (err != HS_SUCCESS) {
        std::cerr << "Deserialize error: " << err << std::endl;
        return false;
    }

    // 分配临时空间
    hs_scratch_t* scratch = nullptr;
    if ((err = hs_alloc_scratch(db, &scratch)) != HS_SUCCESS) {
        std::cerr << "Scratch alloc error: " << err << std::endl;
        hs_free_database(db);
        return false;
    }

    // 执行扫描
    err = hs_scan(db, input, strlen(input), 0, scratch, on_match, nullptr);
    
    // 清理资源
    hs_free_scratch(scratch);
    hs_free_database(db);
    
    if (err != HS_SUCCESS) {
        std::cerr << "Scan error: " << err << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage:\n"
                  << "  Compile mode: " << argv[0] << " -c <database_file>\n"
                  << "  Scan mode:    " << argv[0] << " -s <database_file> <input_text>\n";
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        return compile_and_save(argv[2]) ? 0 : 1;
    } 
    else if (strcmp(argv[1], "-s") == 0 && argc >= 4) {
        return load_and_scan(argv[2], argv[3]) ? 0 : 1;
    }
    
    std::cerr << "Invalid arguments" << std::endl;
    return 1;
}
