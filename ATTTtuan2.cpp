#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define KICH_THUOC 5

//Loại bỏ khoảng trắng và thay J bằng I
string xuLyVanBan(string vanBan) {
    string ketQua = "";
    for (char c : vanBan) {
        if (c != ' ') {
            if (c == 'J') c = 'I'; 
            ketQua += toupper(c);
        }
    }
    return ketQua;
}

//Tạo bảng Playfair từ khóa
vector<vector<char>> taoBangMaHoa(string khoa) {
    khoa = xuLyVanBan(khoa);
    vector<vector<char>> bang(KICH_THUOC, vector<char>(KICH_THUOC, ' '));
    map<char, bool> daSuDung;
    string chuCai = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    
    int hang = 0, cot = 0;
    for (char c : khoa + chuCai) {
        if (!daSuDung[c]) {
            bang[hang][cot] = c;
            daSuDung[c] = true;
            cot++;
            if (cot == KICH_THUOC) {
                cot = 0;
                hang++;
            }
        }
    }
    return bang;
}

//Tìm vị trí ký tự trong bảng
void timViTri(vector<vector<char>> &bang, char c, int &hang, int &cot) {
    for (int i = 0; i < KICH_THUOC; i++)
        for (int j = 0; j < KICH_THUOC; j++)
            if (bang[i][j] == c) {
                hang = i;
                cot = j;
                return;
            }
}

//Chia thành từng cặp ký tự
string chuanHoaVanBan(string vanBan) {
    vanBan = xuLyVanBan(vanBan);
    string vanBanMoi = "";
    
    for (size_t i = 0; i < vanBan.length(); i++) {
        vanBanMoi += vanBan[i];
        if (i + 1 < vanBan.length() && vanBan[i] == vanBan[i + 1]) {
            vanBanMoi += 'X';
        }
    }
    if (vanBanMoi.length() % 2 != 0) vanBanMoi += 'X'; 
    return vanBanMoi;
}

//Mã hóa Playfair
string maHoa(string vanBan, vector<vector<char>> &bang) {
    vanBan = chuanHoaVanBan(vanBan);
    string banMa = "";

    for (size_t i = 0; i < vanBan.length(); i += 2) {
        int hang1, cot1, hang2, cot2;
        timViTri(bang, vanBan[i], hang1, cot1);
        timViTri(bang, vanBan[i + 1], hang2, cot2);

        if (hang1 == hang2) { //Cùng hàng
            banMa += bang[hang1][(cot1 + 1) % KICH_THUOC];
            banMa += bang[hang2][(cot2 + 1) % KICH_THUOC];
        } else if (cot1 == cot2) { //Cùng cột
            banMa += bang[(hang1 + 1) % KICH_THUOC][cot1];
            banMa += bang[(hang2 + 1) % KICH_THUOC][cot2];
        } else { //Tạo hcn
            banMa += bang[hang1][cot2];
            banMa += bang[hang2][cot1];
        }
    }
    return banMa;
}

int main() {
    string khoa = "TUBIEM";
    string banRo = "CHAO CAC BAN";

    vector<vector<char>> bangMaHoa = taoBangMaHoa(khoa);
    string banMa = maHoa(banRo, bangMaHoa);

    cout << "Ban ma: " << banMa << endl;
    return 0;
}
