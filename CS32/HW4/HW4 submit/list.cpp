
void listAll(string path, const File* f)  // two-parameter overload
{
    if (f == nullptr) return;
    if (f->files() == nullptr) std::cout << path << std::endl;
    else {
        path += "/";
        std::cout << path << std::endl;
        for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++) {
            listAll(path + (*it)->name(), *it);
        }   
    }
}
