#include "AssetManager.h"

using namespace ShooterTrainer;

AssetManager::AssetManager(){

}
AssetManager::~AssetManager(){

}
bool AssetManager::setupFilesystem(const std::string& dir){
    directories.parent = dir;
    directories.assets = directories.parent + "Assets/";

    // Check paths are good
    try {
        if(!ensureDirectory(directories.parent)){
            std::cerr << "Error finding or creating [" << directories.parent << "]";
            return false;
        }
        if(!ensureDirectory(directories.assets)){
            std::cerr << "Error finding or creating [" << directories.assets << "]";
            return false;
        }
    }
    catch(std::filesystem::filesystem_error& e){
        std::cerr << "Fatal error in filesystem setup.\n\tWhat: " << e.what() << "\n\tFile: " << e.path1().string() << "\n";
        return false;
    }

    return true;
}

bool ShooterTrainer::ensureDirectory (const std::string& path){
    if(std::filesystem::exists(path))
        return true;
      
    return std::filesystem::create_directories(path);
}
bool ShooterTrainer::ensureFile     (const std::string& path){
    if(std::filesystem::exists(path))
       return true;
 
    std::ofstream file(path);
    return std::filesystem::exists(path);
}
