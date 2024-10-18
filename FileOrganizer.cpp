#include <iostream>  
#include <filesystem>  
#include <map>  

namespace fs = std::filesystem;  

void organizeFiles(const fs::path& directory) {  
    
    std::map<std::string, std::string> ext_to_folder = {  
        {".txt", "TextFiles"},  
        {".jpg", "Images"},  
        {".png", "Images"},  
        {".cpp", "C++Files"},  
        {".docx", "WordDocuments"},  
        {".pdf", "PDFs"},  
        
    };  

    // Iterate through the directory  
    for (const auto& entry : fs::directory_iterator(directory)) {  
        if (fs::is_regular_file(entry.status())) {  
            std::string extension = entry.path().extension().string();  
            // Check if the extension is in our map  
            if (ext_to_folder.find(extension) != ext_to_folder.end()) {  
                fs::path destination = directory / ext_to_folder[extension] / entry.path().filename();  
                // Create the folder if it does not exist  
                fs::create_directories(directory / ext_to_folder[extension]);  
                // Move the file  
                fs::rename(entry.path(), destination);  
                std::cout << "Moved: " << entry.path() << " to " << destination << std::endl;  
            }  
        }  
    }  
}  

int main() {  
    std::string path;  
    std::cout << "Enter the directory path to organize: ";  
    std::getline(std::cin, path);  

    fs::path directoryPath(path);  
    
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {  
        organizeFiles(directoryPath);  
    } else {  
        std::cerr << "Invalid directory. Please check the path." << std::endl;  
    }  

    return 0;  
}
