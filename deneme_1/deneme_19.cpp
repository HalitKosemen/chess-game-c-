
/*WARNÝNG !!!!!!!!!!!!!!!!! 
 FÝL HAREKET OKEY MÝ FONKSÝYONU BOZUK FÝL HAREKET ETMESÝ GEREKTÝÐÝ GÝBÝ HAREKET ETMIYOR UYARRIIIIIRIR DÜZELT*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

bool game_continous = true;
char santrac_tahtasi[64]; //santraç tahtasindaki kareleri dizi elemanlarýna çevirdigim yer
bool tas_rengi[64]; // eger tas_rengi mesela 9 karedeki beyaz ise true yapýcaz

std::string oynancak_tas_konumu;
std::string oynancak_hamle_konumu;
int oynancak_hamle_konum_index;
int oynancak_tas_konum_index;


int girilen_hamlenin_index_hesaplamasi(std::string& girilen_deger) {

	if (girilen_deger.length() != 2) {
		return -1;
	}
	char birinci_eleman = girilen_deger[1]; //satýr sutun harf ve sayý atamasý yapýlabiliyor
	char ikinci_eleman = girilen_deger[0];
	if (birinci_eleman < '1' || birinci_eleman > '8') {
		return -1;
	}
	if (ikinci_eleman < 'a' || ikinci_eleman >'h') {
		return -1;
	}
	int birinci_eleman_indx = birinci_eleman - '1';
	int ikinci_eleman_indx = ikinci_eleman - 'a';

	return birinci_eleman_indx * 8 + ikinci_eleman_indx;
}

void tahta_baslangic_dizilimi() {
	for (int i = 0;i < 64;i++) {
		santrac_tahtasi[i] = ' '; //oncelik ile her kareyi boþ ayarlýyorum ' ' arasýnda space var
		tas_rengi[i] = false; // ve her kareyi beyaz olmadýðýný gösteriyorum
	}

	//beyaz taslar için tanýmlama
	santrac_tahtasi[0] = 'K'; tas_rengi[0] = true;
	santrac_tahtasi[1] = 'A'; tas_rengi[1] = true;
	santrac_tahtasi[2] = 'F'; tas_rengi[2] = true;
	santrac_tahtasi[3] = 'V'; tas_rengi[3] = true;
	santrac_tahtasi[4] = 'S'; tas_rengi[4] = true;
	santrac_tahtasi[5] = 'F'; tas_rengi[5] = true;
	santrac_tahtasi[6] = 'A'; tas_rengi[6] = true;
	santrac_tahtasi[7] = 'K'; tas_rengi[7] = true;
	for (int i = 8;i < 16;i++) {
		santrac_tahtasi[i] = 'P'; tas_rengi[i] = true;
	}

	//siyah taþlar için tanýmlama
	santrac_tahtasi[56] = 'k'; tas_rengi[56] = false;
	santrac_tahtasi[57] = 'a'; tas_rengi[57] = false;
	santrac_tahtasi[58] = 'f'; tas_rengi[58] = false;
	santrac_tahtasi[59] = 'v'; tas_rengi[59] = false;
	santrac_tahtasi[60] = 's'; tas_rengi[60] = false;
	santrac_tahtasi[61] = 'f'; tas_rengi[61] = false;
	santrac_tahtasi[62] = 'a'; tas_rengi[62] = false;
	santrac_tahtasi[63] = 'k'; tas_rengi[63] = false;
	for (int i = 48;i < 56;i++) {
		santrac_tahtasi[i] = 'p'; tas_rengi[i] = false;
	}
}

void tahta_yazdirma() {
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == ' ') {
			cout << ". ";
		}
		else {
			if (tas_rengi[i]) {
				cout << santrac_tahtasi[i] << " "; //beyaz tas ise direkt büyük yaz
			}
			else {
				cout << (char)tolower(santrac_tahtasi[i]) << " "; //siyah ise küçük harf ile yaz
			}
		}
		if ((i + 1) % 8 == 0) {
			cout << endl;
		}
	}
}
//oynancak hamlelerin indexlerini gir ama
void hamle_oynadiginda_dizi_guncelleme() {

	santrac_tahtasi[oynancak_hamle_konum_index] = santrac_tahtasi[oynancak_tas_konum_index];
	tas_rengi[oynancak_hamle_konum_index] = tas_rengi[oynancak_tas_konum_index];
	santrac_tahtasi[oynancak_tas_konum_index] = '. ';
	tas_rengi[oynancak_tas_konum_index] = true;
	tahta_yazdirma();

}

//coutta cagirirken (char) fonksiyon yap
int tahta_kutu_tas_kontrol(std::string& girilen_hamle) {
	int index_hesap = girilen_hamlenin_index_hesaplamasi(girilen_hamle);
	char hangi_tas = santrac_tahtasi[index_hesap];
	return hangi_tas;
}
int tahta_kutu_renk_kontrol(std::string girilen_hamle) {
	int index_hesap = girilen_hamlenin_index_hesaplamasi(girilen_hamle);
	bool tas_rengi_ne = tas_rengi[index_hesap];
	return tas_rengi_ne;
}

// bu piyon hareket_kontrol fonksiyonu çalýþýyor bþ kutuya hareket için ' ' arada bi boþluk býraktan yeterli  
bool piyon_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	int fark = oynancak_hamle_konum_index - oynancak_tas_konum_index;
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	if (renk_kontrol == 1 && tas_harf == 'P') {
		if (fark == 8 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if (oynancak_tas_konum_index >= 8 && oynancak_tas_konum_index <= 15 && fark == 16 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ' && santrac_tahtasi[oynancak_tas_konum_index + 8] == ' ') {
			return true;
		}
		if ((fark == 7 || fark == 9) && santrac_tahtasi[oynancak_hamle_konum_index] != ' ' && tas_rengi[oynancak_hamle_konum_index] != 1) {
			return true;
		}
	}
	else if (renk_kontrol == 0 && tas_harf == 'p') {
		if (oynancak_tas_konum_index >= 48 && oynancak_tas_konum_index <= 55 && fark == -16 && santrac_tahtasi[oynancak_tas_konum_index - 8] == ' ' && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if (fark == -8 && santrac_tahtasi[oynancak_hamle_konum_index] == ' ') {
			return true;
		}
		if ((fark == -7 || fark == -9) && santrac_tahtasi[oynancak_hamle_konum_index] != ' ' && tas_rengi[oynancak_hamle_konum_index] == 1) {
			return true;
		}
	}
	return false;
}

bool kale_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	int fark = oynancak_hamle_konum_index - oynancak_tas_konum_index;
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);
	int adim = 0;

	if (renk_kontrol == 1 && tas_harf == 'K') { //beyaz kale için hareket sýnýrlamalarý 
		if (fark % 8 == 0) {
			adim = (fark > 0) ? 8 : -8;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
		if (oynancak_tas_konum_index / 8 == oynancak_hamle_konum_index / 8) {
			adim = (fark > 0) ? 1 : -1;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
	}
	if (renk_kontrol == 0 && tas_harf == 'k') {
		if (fark % 8 == 0) {
			adim = (fark > 0) ? 8 : -8;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
		if (oynancak_tas_konum_index / 8 == oynancak_hamle_konum_index / 8) {
			adim = (fark > 0) ? 1 : -1;
			for (int i = oynancak_tas_konum_index + adim; i != oynancak_hamle_konum_index; i += adim) {
				if (santrac_tahtasi[i] != ' ') {
					return false;
				}
			}
			if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
				return true;
			}
		}
	}
	return false;
}

bool at_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	//at olasý hareketleri tanýmlýcaz

	/* atýn oynayabilcegi olasý konum doðruluðunu satýr ve sutundan kontrol edicez
	   at - 2 yukarý 1 sola - 2 yukarý 1 saga - 1 yukarý 2 sol - 1 yukarý 2 sað
		  - 2 aþaðý 1 sola - 2 aþaðý 1 sað - 1 aþaðý 2 sol - 1 aþaðý 2 sað
		  þeklinde oynayabilceði 4 olasý konum bilgisi vardir bunlarý kontol edicez*/

	int oynancak_tas_satir_hesaplama = (oynancak_tas_konum_index / 8) + 1;
	int oynancak_tas_sutun_hesaplama = (oynancak_tas_konum_index % 8) + 1;
	int oynancak_hamle_satir_hesaplama = (oynancak_hamle_konum_index / 8) + 1;
	int oynancak_hamle_sutun_hesaplama = (oynancak_hamle_konum_index % 8) + 1;

	//oynicagin tas at degilse false döndür
	if (!((renk_kontrol == 1 && tas_harf == 'A') || (renk_kontrol == 0 && tas_harf == 'a'))) {
		return false;
	}
	int satir_farki = abs(oynancak_hamle_satir_hesaplama - oynancak_tas_satir_hesaplama);
	int sutun_farki = abs(oynancak_hamle_sutun_hesaplama - oynancak_tas_sutun_hesaplama);
	if ((satir_farki == 2 && sutun_farki == 1) || (satir_farki == 1 && sutun_farki == 2)) {
		if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
			return true;
		}
	}
	return false;
}

bool fil_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	if (!((renk_kontrol == 1 && tas_harf == 'F') || (renk_kontrol == 0 && tas_harf == 'f'))) {
		return false;
	}
	int oynancak_tas_satir_hesaplama = (oynancak_tas_konum_index / 8) + 1;
	int oynancak_tas_sutun_hesaplama = (oynancak_tas_konum_index % 8) + 1;
	int oynancak_hamle_satir_hesaplama = (oynancak_hamle_konum_index / 8) + 1;
	int oynancak_hamle_sutun_hesaplama = (oynancak_hamle_konum_index % 8) + 1;

	int satir_farki = abs(oynancak_hamle_satir_hesaplama - oynancak_tas_satir_hesaplama);
	int sutun_farki = abs(oynancak_hamle_sutun_hesaplama - oynancak_tas_sutun_hesaplama);

	if (satir_farki != sutun_farki) {
		return false;
	}
	int satir_adim = (oynancak_hamle_satir_hesaplama > oynancak_tas_satir_hesaplama) ? 1 : -1;
	int sutun_adim = (oynancak_hamle_sutun_hesaplama > oynancak_tas_sutun_hesaplama) ? 1 : -1;

	for (int i = 1; i < satir_farki;i++) {
		int kontrol_satir = oynancak_tas_satir_hesaplama + i * satir_adim;
		int kontrol_sutun = oynancak_tas_sutun_hesaplama + i * sutun_adim;
		int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
		if (santrac_tahtasi[kontrol_index] != ' ') {
			return false;
		}
	}
	if (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol) {
		return true;
	}
	return false;
}

bool vezir_hareket_okey_mi() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	if (!((renk_kontrol == 1 && tas_harf == 'V') || (renk_kontrol == 0 && tas_harf == 'v'))) {
		return false;
	}
	int oynancak_tas_satir_hesaplama = (oynancak_tas_konum_index / 8) + 1;
	int oynancak_tas_sutun_hesaplama = (oynancak_tas_konum_index % 8) + 1;
	int oynancak_hamle_satir_hesaplama = (oynancak_hamle_konum_index / 8) + 1;
	int oynancak_hamle_sutun_hesaplama = (oynancak_hamle_konum_index % 8) + 1;

	int satir_farki = abs(oynancak_hamle_satir_hesaplama - oynancak_tas_satir_hesaplama);
	int sutun_farki = abs(oynancak_hamle_sutun_hesaplama - oynancak_tas_sutun_hesaplama);

	if (satir_farki == sutun_farki) {
		int satir_adim = (oynancak_hamle_satir_hesaplama > oynancak_tas_satir_hesaplama) ? 1 : -1;
		int sutun_adim = (oynancak_hamle_sutun_hesaplama > oynancak_tas_sutun_hesaplama) ? 1 : -1;
		for (int i = 1;i < satir_farki;i++) {
			int kontrol_satir = oynancak_tas_satir_hesaplama + i * satir_adim;
			int kontrol_sutun = oynancak_tas_sutun_hesaplama + i * sutun_adim;
			int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
			if (santrac_tahtasi[kontrol_index] != ' ') {
				return false;
			}
		}
		return (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol);
	}
	if (satir_farki == 0 || sutun_farki == 0) {
		int satir_adim = (satir_farki == 0) ? 0 : (oynancak_hamle_satir_hesaplama > oynancak_tas_satir_hesaplama ? 1 : -1);
		int sutun_adim = (sutun_farki == 0) ? 0 : (oynancak_hamle_sutun_hesaplama > oynancak_tas_sutun_hesaplama ? 1 : -1);
		int uzunluk = max(satir_farki, sutun_farki);
		for (int i = 1;i < uzunluk;i++) {
			int kontrol_satir = oynancak_tas_satir_hesaplama + i * satir_adim;
			int kontrol_sutun = oynancak_tas_sutun_hesaplama + i * sutun_adim;
			int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
			if (santrac_tahtasi[kontrol_index] != ' ') {
				return false;
			}
		}
		return (santrac_tahtasi[oynancak_hamle_konum_index] == ' ' || tas_rengi[oynancak_hamle_konum_index] != renk_kontrol);
	}
	return false;
}

bool kullanicinin_girdigi_hamleler_okey_mi(std::string kullanici_ilk_girilen, std::string kullanici_ikinci_girilen) {

	if (kullanici_ilk_girilen.length() != 2 || kullanici_ikinci_girilen.length() != 2) {
		return false;
	}
	char ilk_harf = kullanici_ilk_girilen[0];
	char ilk_sayi = kullanici_ilk_girilen[1];
	if (ilk_harf < 'a' || ilk_harf > 'h' || ilk_sayi < '1' || ilk_sayi > '8') {
		return false;
	}

	char ikinci_harf = kullanici_ikinci_girilen[0];
	char ikinci_sayi = kullanici_ikinci_girilen[1];
	if (ikinci_harf < 'a' || ikinci_harf > 'h' || ikinci_sayi < '1' || ikinci_sayi > '8') {
		return false;
	}
	return true;
}

std::vector<int> beyaz_piyon_konumlari() {

	std::vector<int> butun_beyaz_piyon_konum_indx;
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'P' && tas_rengi[i] == true) {
			butun_beyaz_piyon_konum_indx.push_back(i);
		}
	}
	return butun_beyaz_piyon_konum_indx;
}
std::vector<int> beyaz_kale_konumlari() {
	
	std::vector<int> butun_beyaz_kale_konum_indx;
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'K' && tas_rengi[i] == true) {
			butun_beyaz_kale_konum_indx.push_back(i);
		}
	}
	return butun_beyaz_kale_konum_indx;
}
std::vector<int> beyaz_at_konumlari() {

	std::vector<int> butun_beyaz_at_konum_indx;
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'A' && tas_rengi[i] == true) {
			butun_beyaz_at_konum_indx.push_back(i);
		}
	}
	return butun_beyaz_at_konum_indx;
}
std::vector<int> beyaz_fil_konumlari() {

	std::vector<int> butun_beyaz_fil_konum_indx;
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'F' && tas_rengi[i] == true) {
			butun_beyaz_fil_konum_indx.push_back(i);
		}
	}
	return butun_beyaz_fil_konum_indx;
}
std::vector<int> beyaz_vezir_konuumlari() {

	std::vector<int> butun_beyaz_vezir_konum_indx;
	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'V' && tas_rengi[i] == true) {
			butun_beyaz_vezir_konum_indx.push_back(i);
		}
	}
	return butun_beyaz_vezir_konum_indx;
}


int vezir_olasi_hareketler(int vezir_index, int hamle_index) {

	std::vector<int> dizi = beyaz_vezir_konuumlari();
	for (size_t i = 0;i < dizi.size();i++) {
		char tas_harf = (char)santrac_tahtasi[dizi[i]];
		int renk_kontrol = (bool)tas_rengi[dizi[i]];
		if (!((renk_kontrol == 1 && tas_harf == 'V'))) {
			continue;
		}
		int vezir_satir = (vezir_index / 8) + 1;
		int vezir_sutun = (vezir_index % 8) + 1;
		int hamle_satir = (hamle_index / 8) + 1;
		int hamle_sutun = (hamle_index % 8) + 1;

		int satir_farki = abs(hamle_satir - vezir_satir);
		int sutun_farki = abs(hamle_sutun - vezir_sutun);

		if (satir_farki == sutun_farki) {
			int satir_adim = (hamle_satir > vezir_satir) ? 1 : -1;
			int sutun_adim = (hamle_sutun > vezir_sutun) ? 1 : -1;
			for (int j = 1;j < satir_farki;j++) {
				int kontrol_satir = vezir_satir + j * satir_adim;
				int kontrol_sutun = vezir_sutun + j * sutun_adim;
				int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
				if (santrac_tahtasi[kontrol_index] != ' ') {
					return -1;
				}
			}
			return hamle_index;
		}
		if (satir_farki == 0 || sutun_farki == 0) {
			int satir_adim = (satir_farki == 0) ? 0 : (hamle_satir > vezir_satir ? 1 : -1);
			int sutun_adim = (sutun_farki == 0) ? 0 : (hamle_sutun > vezir_sutun ? 1 : -1);
			int uzunluk = max(satir_farki, sutun_farki);
			for (int k = 1;k < uzunluk;k++) {
				int kontrol_satir = vezir_satir + k * satir_adim;
				int kontrol_sutun = vezir_sutun + k * sutun_adim;
				int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
				if (santrac_tahtasi[kontrol_index] != ' ') {
					return -1;
				}
			}
			return hamle_index;
		}
		return -1;
	}
	return -1;
}



int kale_olasi_hareketler(int kale_index, int hamle_index) {

	std::vector<int> dizi = beyaz_kale_konumlari();
	int adim = 0;
	for (size_t i = 0;i < dizi.size();i++) {
		char tas_harf = (char)santrac_tahtasi[dizi[i]];
		int renk_kontrol = (bool)tas_rengi[dizi[i]];
		int fark = hamle_index - kale_index;
		if (renk_kontrol == 1 && tas_harf == 'K') {
			if (fark % 8 == 0) {
				adim = (fark > 0) ? 8 : -8;
				for (int k = kale_index + adim; k != hamle_index; k += adim) {
					if (santrac_tahtasi[k] != ' ') {
						return -1;
					}
				}
				if (santrac_tahtasi[hamle_index] == ' ' || tas_rengi[hamle_index] != renk_kontrol) {
					return hamle_index;
				}
			}
			if (kale_index / 8 == hamle_index / 8) {
				adim = (fark > 0) ? 1 : -1;
				for (int j = kale_index + adim; j != hamle_index; j += adim) {
					if (santrac_tahtasi[j] != ' ') {
						return -1;
					}
				}
				if (santrac_tahtasi[hamle_index] == ' ' || tas_rengi[hamle_index] != renk_kontrol) {
					return hamle_index;
				}
			}
		}
	}
	return -1;
}

int piyon_olasi_hareketler(int piyon_index, int hamle_index) {

	// renk_kontrol ve tas_harf fonksiyonlarý bunlari bozuyor çünkü oynancak_tas_konum verisini kullanýyor bunu kullanmamasý lazým
	//renk_kontrol fonksiyonuna bak içindekini direk buraya yaz onuda piyon_indexe göre ayarla anladýn yani renk_kontrol fonksiyonunda oynancak_tas_konum ile piyon_index deðiþtircen 
	std::vector<int> dizi = beyaz_piyon_konumlari();

	int fark = hamle_index - piyon_index;
	for (size_t i = 0;i < dizi.size();i++) {
		char tas_harf = (char)santrac_tahtasi[dizi[i]];
		int renk_kontrol = (bool)tas_rengi[dizi[i]];
		if (renk_kontrol == 1 && tas_harf == 'P') {
			if (fark == 8 && santrac_tahtasi[hamle_index] == ' ') {
				return hamle_index;
			}
			if (piyon_index >= 8 && piyon_index <= 15 && fark == 16 && santrac_tahtasi[hamle_index] == ' ' && santrac_tahtasi[piyon_index + 8] == ' ') {
				return hamle_index;
			}
			if ((fark == 7 || fark == 9) && santrac_tahtasi[hamle_index] != ' ' && tas_rengi[hamle_index] != 1) {
				return hamle_index;
			}
		}
		else if (renk_kontrol == 0 && tas_harf == 'p') {
			if (piyon_index >= 48 && piyon_index <= 55 && fark == -16 && santrac_tahtasi[piyon_index - 8] == ' ' && santrac_tahtasi[hamle_index] == ' ') {
				return hamle_index;
			}
			if (fark == -8 && santrac_tahtasi[hamle_index] == ' ') {
				return hamle_index;
			}
			if ((fark == -7 || fark == -9) && santrac_tahtasi[hamle_index] != ' ' && tas_rengi[hamle_index] == 1) {
				return hamle_index;
			}
		}
	}
	return -1;
}

int at_olasi_hareketler(int at_index, int hamle_index) {

	std::vector<int> dizi = beyaz_at_konumlari();
	for (size_t i = 0;i < dizi.size();i++) {
		char tas_harf = (char)santrac_tahtasi[dizi[i]];
		int renk_kontrol = (bool)tas_rengi[dizi[i]];
		int oynancak_tas_satir_hesaplama = (at_index / 8) + 1;
		int oynancak_tas_sutun_hesaplama = (at_index % 8) + 1;
		int oynancak_hamle_satir_hesaplama = (hamle_index / 8) + 1;
		int oynancak_hamle_sutun_hesaplama = (hamle_index % 8) + 1;

		//oynicagin tas at degilse false döndür
		if (!((renk_kontrol == 1 && tas_harf == 'A'))) {
			return -1;
		}
		int satir_farki = abs(oynancak_hamle_satir_hesaplama - oynancak_tas_satir_hesaplama);
		int sutun_farki = abs(oynancak_hamle_sutun_hesaplama - oynancak_tas_sutun_hesaplama);
		if ((satir_farki == 2 && sutun_farki == 1) || (satir_farki == 1 && sutun_farki == 2)) {
			if (santrac_tahtasi[hamle_index] == ' ' || tas_rengi[hamle_index] != renk_kontrol) {
				return hamle_index;
			}
		}
		return -1;
	}
	return -1;
}

int fil_olasi_hareketler(int fil_index, int hamle_index) {

	std::vector<int> dizi = beyaz_fil_konumlari();
	for (size_t i = 0;i < dizi.size();i++) {
		char tas_harf = (char)santrac_tahtasi[dizi[i]];
		int renk_kontrol = (bool)tas_rengi[dizi[i]];

		if (!((renk_kontrol == 1 && tas_harf == 'F'))) {
			continue;
		}
		int fil_satir = (fil_index / 8) + 1;
		int fil_sutun = (fil_index % 8) + 1;
		int hamle_satir = (hamle_index / 8) + 1;
		int hamle_sutun = (hamle_index % 8) + 1;

		int satir_farki = abs(hamle_satir - fil_satir);
		int sutun_farki = abs(hamle_sutun - fil_sutun);

		if (satir_farki != sutun_farki) {
			continue;
		}
		int satir_adim = (hamle_satir > fil_satir) ? 1 : -1;
		int sutun_adim = (hamle_sutun > fil_sutun) ? 1 : -1;

		for (int j = 1; j < satir_farki;j++) {
			int kontrol_satir = fil_satir + j * satir_adim;
			int kontrol_sutun = fil_sutun + j * sutun_adim;
			int kontrol_index = (kontrol_satir - 1) * 8 + (kontrol_sutun - 1);
			if (santrac_tahtasi[kontrol_index] != ' ') {
				return -1;
			}
		}
		if (santrac_tahtasi[hamle_index] == ' ' || tas_rengi[hamle_index] != renk_kontrol) {
			return hamle_index;
		}
	}
	return -1;
}



//piyon için olasý hamleler
std::vector<int> olasi_hamleler_1() { //oynancak tasin hamle indeksi gelicek

	std::vector<int> hamleler_dizisi;
	std::vector<int> piyon_konumlari = beyaz_piyon_konumlari();
	int sonuc;

	for (size_t i = 0;i < piyon_konumlari.size();i++) {
		int renk_kontrol = (bool)tas_rengi[piyon_konumlari[i]];
		char tas_harf = (char)santrac_tahtasi[piyon_konumlari[i]];
		int xd = piyon_konumlari[i];
		if (tas_harf == 'P' && renk_kontrol == 1) {
			for (int j = 0;j < 64;j++) { // santranc tahtasýndaki her kareyi teker teker tarýcam hangi hamleleri oynayabiliyorsa diziye kaydedicem
				sonuc = piyon_olasi_hareketler(xd, j);
				if (sonuc != -1) {
					hamleler_dizisi.push_back(sonuc);
				}
			}
		}
	}
	cout << "olasi_piyon_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi.size();++j) {
		cout << hamleler_dizisi[j] << " ";
	}
	cout << endl;
	return hamleler_dizisi;
}

//kale için olasý hamleler
std::vector<int> olasi_hamleler_2() {

	std::vector<int> hamleler_dizisi_2;
	std::vector<int> kale_konumlari = beyaz_kale_konumlari();
	int sonuc;

	for (size_t i = 0;i < kale_konumlari.size();i++) {
		int renk_kontrol = (bool)tas_rengi[kale_konumlari[i]];
		char tas_harf = (char)santrac_tahtasi[kale_konumlari[i]];
		int xd = kale_konumlari[i];
		if (tas_harf == 'K' && renk_kontrol == 1) {
			for (int j = 0;j < 64;j++) {
				sonuc = kale_olasi_hareketler(xd, j);
				if (sonuc != -1) {
					hamleler_dizisi_2.push_back(sonuc);
				}
			}
		}
	}
	cout << "olasi_kale_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi_2.size();++j) {
		cout << hamleler_dizisi_2[j] << " ";
	}
	cout << endl;
	return hamleler_dizisi_2;
}
//at için olasi hamleler
std::vector<int> olasi_hamleler_3() {

	std::vector<int> hamleler_dizisi_3;
	std::vector<int> at_konumlari = beyaz_at_konumlari();
	int sonuc;

	for (size_t i = 0;i < at_konumlari.size();i++) {
		int renk_kontrol = (bool)tas_rengi[at_konumlari[i]];
		char tas_harf = (char)santrac_tahtasi[at_konumlari[i]];
		int xd = at_konumlari[i];
		if (tas_harf == 'A' && renk_kontrol == 1) {
			for (int j = 0;j < 64;j++) {
				sonuc = at_olasi_hareketler(xd, j);
				if (sonuc != -1) {
					hamleler_dizisi_3.push_back(sonuc);
				}
			}
		}
	}
	cout << "olasi_at_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi_3.size();++j) {
		cout << hamleler_dizisi_3[j] << " ";
	}
	cout << endl;
	return hamleler_dizisi_3;
}
//fil için olasi hamleler
std::vector<int> olasi_hamleler_4() {

	std::vector<int> hamleler_dizisi_4;
	std::vector<int> fil_konumlari = beyaz_fil_konumlari();
	int sonuc;
	for (size_t i = 0;i < fil_konumlari.size();i++) {
		int renk_kontrol = (bool)tas_rengi[fil_konumlari[i]];
		char tas_harf = (char)santrac_tahtasi[fil_konumlari[i]];
		int xd = fil_konumlari[i];
		if (tas_harf == 'F' && renk_kontrol == 1) {
			for (int j = 0;j < 64;j++) {
				sonuc = fil_olasi_hareketler(xd, j);
				if (sonuc != -1) {
					hamleler_dizisi_4.push_back(sonuc);
				}
			}
		}
	}
	cout << "olasi_fil_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi_4.size();++j) {
		cout << hamleler_dizisi_4[j] << " ";
	}
	cout << endl;
	return hamleler_dizisi_4;
}
//vezir için olasi hamleler
std::vector<int> olasi_hamleler_5() {

	std::vector<int> hamleler_dizisi_5;
	std::vector<int> vezir_konumlari = beyaz_vezir_konuumlari();
	int sonuc;
	for (size_t i = 0;i < vezir_konumlari.size();i++) {
		int renk_kontrol = (bool)tas_rengi[vezir_konumlari[i]];
		char tas_harf = (char)santrac_tahtasi[vezir_konumlari[i]];
		int xd = vezir_konumlari[i];
		if (tas_harf == 'V' && renk_kontrol == 1) {
			for (int j = 0;j < 64;j++) {
				sonuc = vezir_olasi_hareketler(xd, j);
				if (sonuc != -1) {
					hamleler_dizisi_5.push_back(sonuc);
				}
			}
		}
	}
	cout << "olasi_veriz_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi_5.size();++j) {
		cout << hamleler_dizisi_5[j] << " ";
	}
	cout << endl;
	return hamleler_dizisi_5;
}


int main() {

	tahta_baslangic_dizilimi();
	tahta_yazdirma();

	while (game_continous) {

		cout << "oynancak_tas_konumu: ";
		cin >> oynancak_tas_konumu;
		oynancak_tas_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_tas_konumu);

		cout << "sectiginiz tas gitmesini istediginiz konum :";
		cin >> oynancak_hamle_konumu;
		oynancak_hamle_konum_index = girilen_hamlenin_index_hesaplamasi(oynancak_hamle_konumu);

		cout << "oynancak tas tipi :" << (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu) << " " << (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu) << endl;
		cout << "hamleyi oynicagin kutu bilgi:" << (char)tahta_kutu_tas_kontrol(oynancak_hamle_konumu) << " " << (bool)tahta_kutu_renk_kontrol(oynancak_hamle_konumu) << endl;
		if (kullanicinin_girdigi_hamleler_okey_mi(oynancak_tas_konumu, oynancak_hamle_konumu)) {
			olasi_hamleler_1();
			olasi_hamleler_2();
			olasi_hamleler_3();
			olasi_hamleler_4();
			olasi_hamleler_5();
			if (piyon_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
			if (kale_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
			if (at_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
			if (fil_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
			if (vezir_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
			}
		}
	}
	return 0;
}
