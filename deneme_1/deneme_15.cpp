
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

bool game_continous = true;
char santrac_tahtasi[64]; //santraç tahtasindaki kareleri dizi elemanlarýna çevirdigim yer
bool tas_rengi[64]; // eger tas_rengi mesela 9 karedeki beyaz ise true yapýcaz
bool oynama_sirasi = true; // eðer true ise beyazda false ise siyahta

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

	oynama_sirasi = !oynama_sirasi;
	cout << (oynama_sirasi ? "Beyaz oyuncu sýrada." : "Siyah oyuncu sýrada.") << endl;

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
	int sutun_adim = (oynancak_hamle_sutun_hesaplama - oynancak_tas_sutun_hesaplama) ? 1 : -1;

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


//fonksiyon oynamak istediðin taþýn hangi kareli indexlere oynayabilceðini gösteriyor iyi çalýþýyor gibide duruyor 
//bu fonksiyon o an oynadýðýn taþýn olasý hamlelerini veriyor 
std::vector<int> olasi_hamleler_1(int olasi_fonks_hamle_indx) { //oynancak tasin hamle indeksi gelicek

	std::vector<int> hamleler_dizisi;
	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	int tas_index = olasi_fonks_hamle_indx;
	int oynn_hamle_index = oynancak_hamle_konum_index;
	int hamle_index = 0;

	if (tas_harf == 'P' || tas_harf == 'p') {
		for (int i = 0;i < 64;i++) { // santranc tahtasýndaki her kareyi teker teker tarýcam hangi hamleleri oynayabiliyorsa diziye kaydedicem
			oynancak_hamle_konum_index = hamle_index;
			if (piyon_hareket_okey_mi()) {
				hamleler_dizisi.push_back(hamle_index);
			}
			hamle_index++;
		}
		oynancak_hamle_konum_index = oynn_hamle_index;
	}
	else if (tas_harf == 'K' || tas_harf == 'k') {
		for (int j = 0;j < 64;j++) {
			oynancak_hamle_konum_index = hamle_index;
			if (kale_hareket_okey_mi()) {
				hamleler_dizisi.push_back(hamle_index);
			}
			hamle_index++;
		}
		oynancak_hamle_konum_index = oynn_hamle_index;
	}
	else if (tas_harf == 'F' || tas_harf == 'f') {
		for (int k = 0;k < 64;k++) {
			oynancak_hamle_konum_index = hamle_index;
			if (fil_hareket_okey_mi()) {
				hamleler_dizisi.push_back(hamle_index);
			}
			hamle_index++;
		}
		oynancak_hamle_konum_index = oynn_hamle_index;
	}
	else if (tas_harf == 'A' || tas_harf == 'a') {
		for (int l = 0;l < 64;l++) {
			oynancak_hamle_konum_index = hamle_index;
			if (at_hareket_okey_mi()) {
				hamleler_dizisi.push_back(hamle_index);
			}
			hamle_index++;
		}
		oynancak_hamle_konum_index = oynn_hamle_index;
	}
	else if (tas_harf == 'V' || tas_harf == 'v') {
		for (int h = 0;h < 64;h++) {
			oynancak_hamle_konum_index = hamle_index;
			if (vezir_hareket_okey_mi()) {
				hamleler_dizisi.push_back(hamle_index);
			}
			hamle_index++;
		}
		oynancak_hamle_konum_index = oynn_hamle_index;
	}


	cout << "piyon_hamleleri :";
	for (size_t j = 0;j < hamleler_dizisi.size();++j) {
		cout << hamleler_dizisi[j] << "";
	}
	cout << endl;
	return hamleler_dizisi;
}


// kod satýrý butun beyaz piyonlarýn olasý hamlelerini bulmamýza yardýmcý oluyor ve gayette iyi çalýþýyor þimdi bunu diðer beyaz taþlar için tanýmlamaya çalýþ
std::vector<int> piyonlarin_olasi_hamlelerini_bulma_fonks() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	int oynn_hamle_index = oynancak_hamle_konum_index;
	int oynn_tas_index = oynancak_tas_konum_index;

	std::vector<int> butun_beyaz_piyon_konum_indx;
	std::vector<int> butun_beyaz_piyon_olasi_hamleler;

	std::vector<int> butun_siyah_piyon_konum_indx;
	std::vector<int> butun_siyah_piyon_olasi_hamleler;

	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'P' && tas_rengi[i] == true) {
			butun_beyaz_piyon_konum_indx.push_back(i);
		}
		if (santrac_tahtasi[i] == 'p' && tas_rengi[i] == false) {
			butun_siyah_piyon_konum_indx.push_back(i);
		}
	}
	for (size_t i = 0; i < butun_beyaz_piyon_konum_indx.size();i++) {
		oynancak_tas_konum_index = butun_beyaz_piyon_konum_indx[i];
		butun_beyaz_piyon_olasi_hamleler = olasi_hamleler_1(oynancak_tas_konum_index);
	}
	oynancak_tas_konum_index = oynn_tas_index;

	for (size_t i = 0; i < butun_siyah_piyon_konum_indx.size();i++) {
		oynancak_tas_konum_index = butun_siyah_piyon_konum_indx[i];
		butun_siyah_piyon_olasi_hamleler = olasi_hamleler_1(oynancak_tas_konum_index);
	}
	oynancak_tas_konum_index = oynn_tas_index;


	return butun_beyaz_piyon_olasi_hamleler;
}

std::vector<int> butun_beyaz_taslarýn_konumlari() {

	int renk_kontrol = (bool)tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	char tas_harf = (char)tahta_kutu_tas_kontrol(oynancak_tas_konumu);

	std::vector<int> butun_beyaz_piyon_konum_indx;
	std::vector<int> butun_beyaz_kale_konum_indx;
	std::vector<int> butun_beyaz_at_konum_indx;
	std::vector<int> butun_beyaz_fil_konum_indx;
	std::vector<int> butun_beyaz_vezir_konum_indx;

	for (int i = 0;i < 64;i++) {
		if (santrac_tahtasi[i] == 'P' && tas_rengi[i] == true) {
			butun_beyaz_piyon_konum_indx.push_back(i);
		}
		if (santrac_tahtasi[i] == 'K' && tas_rengi[i] == true) {
			butun_beyaz_kale_konum_indx.push_back(i);
		}
		if (santrac_tahtasi[i] == 'A' && tas_rengi[i] == true) {
			butun_beyaz_at_konum_indx.push_back(i);
		}
		if (santrac_tahtasi[i] == 'F' && tas_rengi[i] == true) {
			butun_beyaz_fil_konum_indx.push_back(i);
		}
		if (santrac_tahtasi[i] == 'V' && tas_rengi[i] == true) {
			butun_beyaz_vezir_konum_indx.push_back(i);
		}
	}

	for (size_t i = 0;i < butun_beyaz_piyon_konum_indx.size();i++) {
		cout << butun_beyaz_piyon_konum_indx[i] << " ";
	}
	cout << endl;
	for (size_t i = 0;i < butun_beyaz_kale_konum_indx.size();i++) {
		cout << butun_beyaz_kale_konum_indx[i] << " ";
	}
	cout << endl;
	for (size_t i = 0;i < butun_beyaz_at_konum_indx.size();i++) {
		cout << butun_beyaz_at_konum_indx[i] << " ";
	}
	cout << endl;
	for (size_t i = 0;i < butun_beyaz_fil_konum_indx.size();i++) {
		cout << butun_beyaz_fil_konum_indx[i] << " ";
	}
	cout << endl;
	for (size_t i = 0;i < butun_beyaz_vezir_konum_indx.size();i++) {
		cout << butun_beyaz_vezir_konum_indx[i] << " ";
	}
	cout << endl;

	return butun_beyaz_piyon_konum_indx, butun_beyaz_kale_konum_indx, butun_beyaz_at_konum_indx, butun_beyaz_fil_konum_indx, butun_beyaz_vezir_konum_indx;
}

bool hamle_sirasi_kontrol() {
	int renk_kontrol = tahta_kutu_renk_kontrol(oynancak_tas_konumu);
	if ((oynama_sirasi && renk_kontrol == 1) || (!oynama_sirasi && renk_kontrol == 0)) {
		return true;
	}
	return false;
}




bool sah_cekme_kontrol() {






	return 0;
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

		char tas_tipi = tahta_kutu_tas_kontrol(oynancak_tas_konumu);
		bool tas_rengi = tahta_kutu_renk_kontrol(oynancak_tas_konumu);
		cout << "Oynanacak taþ tipi: " << tas_tipi << " " << tas_rengi << endl;
		cout << "Hamle yapýlacak kutu bilgisi: "
			<< tahta_kutu_tas_kontrol(oynancak_hamle_konumu) << " "
			<< tahta_kutu_renk_kontrol(oynancak_hamle_konumu) << endl;
		if (tas_rengi != oynama_sirasi) {
			cout << "Bu taþ ile hamle yapma sýrasý deðil!\n";
			continue;
		}
		if (kullanicinin_girdigi_hamleler_okey_mi(oynancak_tas_konumu, oynancak_hamle_konumu)) {
			if (piyon_hareket_okey_mi() || kale_hareket_okey_mi() ||
				at_hareket_okey_mi() || fil_hareket_okey_mi() ||
				vezir_hareket_okey_mi()) {
				hamle_oynadiginda_dizi_guncelleme();
				oynama_sirasi != oynama_sirasi;
			}
			else {
				cout << "Geçersiz hamle!\n";
			}
		}
		else {
			cout << "Geçersiz hamle girdiniz!\n";
		}
	}
	return 0;
}
