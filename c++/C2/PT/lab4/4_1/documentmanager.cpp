#include "documentmanager.hpp"
#include <fstream>

DocumentManager::DocumentManager() {}

void
DocumentManager::promt() {
    int n;

    // Спрашиваем кол-во документов
    std::cout << "Enter number of your documents: ";
    std::cin  >> n;
    std::cout << std::endl;

    for(int i = 0; i < n; i++) {
        doclist.push_back(std::move(DocumentFactory::promt()));
    }
}

void
DocumentManager::save(const std::string& filename) const {
    std::ofstream file(filename);

    for(auto& doc : doclist) {
        file << *doc;
    }
}

void
DocumentManager::load(const std::string& filename) {
    std::ifstream file(filename);

    int type;
    while(file >> type) {
        auto doc = DocumentFactory::create(type);
        file >> *doc;
    }
}

void
DocumentManager::push(DocumentPointer doc) {
    doclist.push_back(std::move(doc));
}

void
DocumentManager::push(AbstractDocument* docptr) {
    doclist.emplace_back(docptr);
}


void
DocumentManager::del(int type) {
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        if(it->get()->type == type) {
            doclist.erase(it);
        }
    }
}

uint
DocumentManager::count() const {
    return static_cast<uint>(doclist.size());
}

uint
DocumentManager::count(int type) const {
    uint cnt = 0;
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        if(it->get()->type == type) {
            cnt++;
        }
    }
    return cnt;
}

void
DocumentManager::show() const {
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        std::cout << *it->get() << std::endl;
    }
}

void
DocumentManager::show(int type) const {
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        if(it->get()->type == type) {
             std::cout << *it->get() << std::endl;
        }
    }
}

void
DocumentManager::show(const std::string& sname) const {
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        if(it->get()->secondName == sname) {
             std::cout << *it->get() << std::endl;
        }
    }
}

void
DocumentManager::show(time_t bd) const {
    for(auto it = doclist.begin(); it != doclist.end(); ++it) {
        if(!it->get()->dated) continue;
        auto datedDocument = dynamic_cast<AbstractDatedDocument*>(it->get());
        if(datedDocument->birthDate == bd) {
             std::cout << *it->get() << std::endl;
        }
    }
}
