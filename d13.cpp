#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:
    char *name;
    char user[51];
    int h;
    int w;
public:
    Image(const char *name = "untitled", const char *user = "unknown", int h = 800, int w = 800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->user, user);
        this->h = h;
        this->w = w;
    }

    virtual ~Image() {
        delete[] name;
    }

    virtual int fileSize() const {
        return h * w * 3;
    }

    bool operator>(const Image &other) const {
        return this->fileSize() > other.fileSize();
    }

    friend ostream &operator<<(ostream &os, const Image &print) {
        return os << print.name << " " << print.user << " " << print.fileSize() << endl;
    }

};

class TransparentImage : public Image {
private:
    bool transparency = false;
public:
    TransparentImage(const char *name = "untitled", const char *user = "unknown", int h = 800, int w = 800,
                     bool transparency = true) : Image(name, user, h, w), transparency(transparency) {}

    ~TransparentImage() {}

    int fileSize() const {
        if(transparency){
            return w * h * 4;
        }else{
            return  w * h + (w * h)/8;
        }
    }
};

class Folder {
private:
    char name[256];
    char user[51];
    Image *images[100];
    int n;
public:
    Folder(const char *name = "", const char *user = "unknown") {
        this->n = 0;
        strcpy(this->name, name);
        strcpy(this->user, user);
    }

    int folderSize() const {
        int sum(0);
        for (int i = 0; i < n; ++i) {
            sum += images[i]->fileSize();
        }
        return sum;
    }

    Image *getMaxFile() {
        Image *max = images[0];
        for (int i = 0; i < n; ++i) {
            if (*images[i] > *max) {
                max = images[i];
            }
        }
        return max;
    }

    Folder &operator+=(Image &img) {
        images[n++] = &img;
        return *this;
    }

    friend ostream &operator<<(ostream &os, Folder &print) {
        os << print.name << " " << print.user << endl << "--" << endl;
        for (int i = 0; i < print.n; i++) {
            os << *print.images[i];
        }
        os << "--" << endl << "Folder size: " << print.folderSize() << endl;
        return os;
    }

    Image *operator[](int index) {
        if (index >= n) {
            return nullptr;
        }
        return images[index];
    }
};

Folder &max_folder_size(Folder *folders, int n) {
    double max(-1);
    int index(0);
    for (int i = 0; i < n; i++) {
        if (folders[i].folderSize() > max) {
            max = folders[i].folderSize();
            index = i;
        }
    }
    return folders[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, h, w);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, h, w, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, h, w);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, h, w, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, h, w);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, h, w, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, h, w);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, h, w, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, h, w);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, h, w, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
};
