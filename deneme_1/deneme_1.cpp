#include <iostream>
#include <string>
using namespace std;


bool game_continous = true;


char santrac_tahtasi[64]; //0 tahtanýn en sol altý 63 tahtanýn sað en üstü...
bool tas_rengi[64];

//fonksiyon tanimi santraç tahtasýný 0 dan 63 e diziye tanýmladýk bu fonksiyon c6 girildiðinde 42 elemana denk geliceðini biliyor santraç tahtasinda...
int santrac_tahtasi_oynancak_hamle_okeymi_fonksiyonu(std::string& kare_pozisyon) {
	if (kare_pozisyon.length() != 2) {
		return -1; //boyutu 4ten büyük bir girdi girilirse giricek if
	}
	char sutun_1 = kare_pozisyon[0]; //girilen 0. eleman 
	char satir_1 = kare_pozisyon[1]; //girilen 1. eleman
	if (sutun_1 < 'a' || sutun_1 > 'h') {
		return -1;
	}
	if (satir_1 < '1' || satir_1 >'8') {
		return -1;
	}
	int sutun_1_index = sutun_1 - 'a';
	int satir_1_index = satir_1 - '1';
	return satir_1_index * 8 + sutun_1_index;
}

//bu fonksiyon oynacaðin taþýn konumunu döndüren bir fonksiyon mesela c6 oynican 42 konumunu döndürüyo
int santran_tahtasi_oynancak_tas_secimi_konumu_fonksiyonu(std::string& oynancak_tas) {
	if (oynancak_tas.length() != 2) {
		return -1;
	}
	char sutun_1 = oynancak_tas[0];
	char satir_1 = oynancak_tas[1];
	if (sutun_1 < 'a' || sutun_1 > 'h') {
		return -1;
	}
	if (satir_1 < '1' || satir_1 >'8') {
		return -1;
	}
	int sutun_1_index = sutun_1 - 'a';
	int satir_1_index = satir_1 - '1';
	return satir_1_index * 8 + sutun_1_index;
}


void tahta_Baslangic_dizilimi() {
	for (int i = 0;i < 64;i++) {
		santrac_tahtasi[i] = ' ';
		tas_rengi[i] = false;
	}

	//beyaz taslar
	santrac_tahtasi[0] = 'K'; tas_rengi[0] = true;
	santrac_tahtasi[1] = 'A'; tas_rengi[1] = true;
	santrac_tahtasi[2] = 'F'; tas_rengi[2] = true;
	santrac_tahtasi[3] = 'V'; tas_rengi[3] = true;
	santrac_tahtasi[4] = 'S'; tas_rengi[4] = true;
	santrac_tahtasi[5] = 'F'; tas_rengi[5] = true;
	santrac_tahtasi[6] = 'A'; tas_rengi[6] = true;
	santrac_tahtasi[7] = 'K'; tas_rengi[7] = true;
	for (int i = 8; i < 16; i++) {
		santrac_tahtasi[i] = 'P'; tas_rengi[i] = true;
	}

	//siyah taslar	
	santrac_tahtasi[56] = 'K'; tas_rengi[56] = false;
	santrac_tahtasi[57] = 'A'; tas_rengi[57] = false;
	santrac_tahtasi[58] = 'F'; tas_rengi[58] = false;
	santrac_tahtasi[59] = 'V'; tas_rengi[59] = false;
	santrac_tahtasi[60] = 'S'; tas_rengi[60] = false;
	santrac_tahtasi[61] = 'F'; tas_rengi[61] = false;
	santrac_tahtasi[62] = 'A'; tas_rengi[62] = false;
	santrac_tahtasi[63] = 'K'; tas_rengi[63] = false;
	for (int i = 48; i < 56; i++) {
		santrac_tahtasi[i] = 'P'; tas_rengi[i] = false;
	}
}

void tahta_yazdirma() {
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == ' ') {
			cout << ". ";
		}
		else {
			if (tas_rengi[i]) {
				cout << santrac_tahtasi[i] << " "; //beyaz tas
			}
			else {
				cout << (char)tolower(santrac_tahtasi[i]) << " ";
			}
		}
		if ((i + 1) % 8 == 0) {
			cout << endl;
		}
	}
}

bool piyon_hareket_kontrol(int baslangic_index , int hedef_index, bool beyaz_mi) {

	int fark = hedef_index - baslangic_index; // beyaz piyon için pozitif çünkü beyaz yukarda siyah için negatif siyah yukarda 
	if (beyaz_mi) {
		//ilk hamle 2 ileri koþulu
		if (baslangic_index >= 48 && baslangic_index <= 55 && fark == -16 && santrac_tahtasi[baslangic_index - 8] == '. ' &&santrac_tahtasi[hedef_index] == '. ') { //zoru bu iþlem piyon 2 birim için önü açýksa oynayabilir demek 
			return true;
		}
		//normel 1 hamle ileri
		if (fark == -8 && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if ((fark == -7 || fark == -9) && santrac_tahtasi[hedef_index] != '. ' && !tas_rengi[hedef_index]) {
			return true;
		}
	}
	else {
		if (baslangic_index >= 8 && baslangic_index <= 15 && fark == 16 && santrac_tahtasi[baslangic_index + 8] == '. ' && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if (fark == 8 && santrac_tahtasi[hedef_index] == '. ') {
			return true;
		}
		if ((fark == 7 || fark == 9) && santrac_tahtasi[hedef_index] != '. ' && tas_rengi[hedef_index]) {
			return true;
		}
	}
	return false;
}

std::string oynancak_hamle_gir;
std::string oynancak_tas_secimi_konumu;


int main() {

	tahta_Baslangic_dizilimi();
	tahta_yazdirma();


	while (game_continous) {

		//bu algortima geliþtirilmek zorunda fakat piyonlar oynuyor ve hareket ediyor fakat ilk hamle sonrasýnda bile 2 ileri gidebiliyor düzeltilcek 
		cout << "oynicaginiz hamle nedir :";
		cin >> oynancak_hamle_gir;
		int oynancak_tas_index = santrac_tahtasi_oynancak_hamle_okeymi_fonksiyonu(oynancak_hamle_gir);
		cout << "tasi oynamak istediginiz konumu secin :";
		cin >> oynancak_tas_secimi_konumu;
		int oynancak_tas_secim_index = santran_tahtasi_oynancak_tas_secimi_konumu_fonksiyonu(oynancak_tas_secimi_konumu);

		piyon_hareket_kontrol(oynancak_tas_index, oynancak_tas_index, false);
		santrac_tahtasi[oynancak_tas_secim_index] = santrac_tahtasi[oynancak_tas_index];
		tas_rengi[oynancak_tas_secim_index] = tas_rengi[oynancak_tas_index];
		santrac_tahtasi[oynancak_tas_index] = '. ';
		tas_rengi[oynancak_tas_index] = false;
		tahta_yazdirma();
	}



	return 0;
}