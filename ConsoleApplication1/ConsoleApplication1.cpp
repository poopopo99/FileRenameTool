#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = filesystem;

// 新しいファイル名を生成する関数
string generateNewFileName(int index) {
    ostringstream oss;
    oss << setw(5) << setfill('0') << index;
    return oss.str();
}

// ディレクトリ内のファイルをリネームする関数
void renameFilesInDirectory(const string& directoryPath, int startNum) {
    try {
        vector<fs::path> files;

        // 最初にディレクトリ内のすべてのファイルのパスを取得
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }

        int index = startNum;
        // 取得したファイルのパスを使って名前を変更
        for (const auto& filePath : files) {
            string newFileName = generateNewFileName(index) + filePath.extension().string();
            fs::path newFilePath = filePath.parent_path() / newFileName;

            fs::rename(filePath, newFilePath);
            cout << "Renamed: " << filePath.filename() << " -> " << newFileName << endl;

            index++;
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "General error: " << e.what() << endl;
    }
}

int main() {
    string directoryPath,isOK;
    int startNum;
    cout << "リネームしたいファイルのあるフォルダパスを入力してください: ";
    cin >> directoryPath;
    cout << "最初のファイル番号: ";
    cin >> startNum;

    cout << "問題なければ[OK]と入力してください: ";
    cin >> isOK;

    if (isOK =="OK") {
        renameFilesInDirectory(directoryPath, startNum);
    }
    else {
        cout << "OK 以外が入力されたため、終了します。" << endl;
    }


    cout << "リネームが終了しました。" << endl;
    cout << "続行するには何かキーを押してください . . .";
    cin.ignore();
    cin.get();
    return 0;
}
