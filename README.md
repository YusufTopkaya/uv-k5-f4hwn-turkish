# UV-K5/K6/5R Türkçe Firmware (F4HWN)

Bu proje, [armel/uv-k5-firmware-custom](https://github.com/armel/uv-k5-firmware-custom) (F4HWN özelleştirmesi) çatalının Türkçe arayüz ile yerelleştirilmiş halidir.

> [!NOTE]
> Radyonun LCD fontu yalnızca 7-bit ASCII karakterleri desteklediği için Türkçe karakterler (ç, ğ, ı, ö, ş, ü, İ) ASCII karşılıklarıyla yazılmıştır. Örneğin:
> - `Güç` → `Guc`
> - `Tüm` → `Tum`
> - `Sürüm` → `Surum`
> - `Hoşgeldin` → `Hosgeldin`

## 🇹🇷 F4HWN Türkçe Çeviri

Bu sürümde F4HWN firmware'i için **iki farklı Türkçe çeviri seçeneği** bulunmaktadır.

### 📌 Basic

**Basic** sürümünde, F4HWN firmware'indeki metinler mümkün olduğunca birebir Türkçe'ye çevrilmiştir. (Teknik terim ve kısaltmalar korunmuştur.)

#### Tarayıcı üzerinden doğrudan yüklemek için:

https://egzumer.github.io/uvtools/?firmwareURL=https://github.com/YusufTopkaya/uv-k5-f4hwn-turkish/releases/download/v0.0.1/f4hwn-basic.packed.bin

---

### 📌 Long-text

**Long-text** sürümünde ise menü metinleri daha açıklayıcı ve anlaşılır olacak şekilde çevrilmiştir. Uzun metinler, menülerde gezinirken kayan (marquee) yazı olarak gösterilir; böylece metnin tamamı okunabilir. Fakat Quansheng telsizlerde kullanılan ekran buna çok uygun olmadığı için ghosting sebepli gözlerini yorabilir.

#### Tarayıcı üzerinden doğrudan yüklemek için:

https://egzumer.github.io/uvtools/?firmwareURL=https://github.com/YusufTopkaya/uv-k5-f4hwn-turkish/releases/download/v0.0.1/f4hwn-longtext.packed.bin

---

### 📋 Değişiklik Geçmişi

**Full Changelog:** https://github.com/YusufTopkaya/uv-k5-f4hwn-turkish

## Bu fork'ta neler değişti?

- **Tam Türkçe arayüz çevirisi** yapıldı.
- Açılıştaki sürüm yazısı artık **"Turkce Surum"** olarak görünüyor.
- Açılış ekranına **tam ekran Türk bayrağı** logosu eklendi (Power-On Message **TUM** modunda).
- **Basic** sürümünde menü etiketleri mümkün olduğunca kısa ve birebir çevrilmiştir.
- **Long-text** sürümünde menü etiketleri daha açıklayıcı uzun karşılıklarla değiştirilmiş, sol panelde sığmayan etiketler **kayan yazı (marquee)** ile gösterilmektedir.
- Birden fazla yerde kullanılan tüm kelimeler tek merkezi tabloda (`ui/strings.h` / `ui/strings.c`) toplanarak dinamik referansla kullanılıyor.

## Kayan menü etiketleri (Long-text sürümü)

Sol menü paneli 48 piksel genişliğinde (6 büyük karakter). Bu alana sığmayan etiketler için `ui/menu.c`'de `UI_PrintMenuLabelScroll()` fonksiyonu eklendi.

- **Marquee tarzı:** Metin sürekli sola kayar, ekrandan tamamen çıktıktan sonra sağ taraftan tekrar girer.
- **Hız:** Yaklaşık 150 ms'de bir piksel kayar.
- **Kırpma:** Metin dikey ayırıcı çizgiyi ve sağ paneli asla ezmez; panel dışında kalan pikseller çizilmez.
- **Yan etiketler:** Özel menü düzeninde (custom layout) üstteki ve alttaki küçük yazılı etiketler 8 karakterle sınırlandırılır; seçili ortadaki büyük etiket kayar.

> [!WARNING]
> Quansheng telsizlerdeki STN LCD ekran hızlı hareketli metinlere tam olarak uygun olmadığı için long-text sürümünde ghosting (gölge/iz kalma) ve buna bağlı göz yorgunluğu görülebilir. Bu durum ekranın donanım özelliğinden kaynaklanır.

## Çeviri notları ve kısaltmalar

LCD ekrandaki sınırlı alan yüzünden bazı teknik kısaltmalar korunmuştur. Aşağıda menü başlıkları, alt menü değerleri ve diğer mesajlarda kullanılan terimler ile açıklamaları verilmiştir.

### Menü başlıkları

| Görünen | Açıklama |
|---------|----------|
| `Adim` | Kanal adımı |
| `TXGucu` | TX gücü |
| `RxDCS` / `RxCTCS` | Alıcı DCS / CTCSS kodu |
| `TxDCS` / `TxCTCS` | Verici DCS / CTCSS kodu |
| `TxOfsetYon` | Verici ofset yönü (Shift Direction) |
| `Ofset` | Frekans ofseti |
| `BantGenis` | Bant genişliği (Wide / Narrow) |
| `Karistirici` | Karıştırıcı (Scrambler) |
| `MesgulKilit` | Meşgul kanal kilidi (Busy Channel Lockout) |
| `Kompander` | Sıkıştırıcı / açıcı (Compander) |
| `Modulasyon` | Modülasyon (AM/FM) |
| `TXKiliti` | TX kilidi |
| `ListeyeEkle1` / `2` / `3` | Tarama listesine ekleme |
| `Kaydet` / `Sil` | Kanalı kaydet / sil |
| `KanalIsmi` | Kanal ismi |
| `TaramaList` / `1` / `2` / `3` | Tarama listeleri |
| `Tarama` | Tarama yönü / modu |
| `F1Kisa` / `F1Uzun` | F1 tuşu kısa / uzun basış fonksiyonu |
| `F2Kisa` / `F2Uzun` | F2 tuşu kısa / uzun basış fonksiyonu |
| `MUzun` | M tuşu uzun basış fonksiyonu |
| `OtoKilit` | Otomatik tuş kilidi |
| `TXSuresi` | TX Süre / TOT (Time-Out Timer) |
| `PilTasarruf` | Pil tasarrufu |
| `PilGostergesi` | Pil göstergesi |
| `Mikrofon` | Mikrofon kazancı |
| `MikrofonBar` | Mikrofon bar göstergesi |
| `KanalGorunumu` | Kanal göstergesi |
| `AcilisEkrani` | Açılış mesajı |
| `ArkaIsikZaman` | Arka ışık zamanı |
| `ArkaIsikMin` / `ArkaIsikMax` | Arka ışık minimum / maksimum seviyesi |
| `ArkaIsikTxRx` | Arka ışık TX/RX davranışı |
| `TusSesi` | Tuş sesi |
| `SesDili` | Sesli uyarı dili |
| `RogerBeep` | Roger beep |
| `KuyrukKes` / `TersKuyruk` | Squelch kuyruk kesme / ters kuyruk |
| `TekKanalAra` | Tek kanal arama |
| `AlarmModu` | Alarm modu |
| `YukariKod` / `AsagiKod` | Yukarı / Aşağı DTMF kodu |
| `PTT ID` | PTT tanıtma kimliği |
| `VOX` | Sesle tetikleme |
| `RXModu` | RX modu (RX Mode) |
| `Susturma` | Squelch (parazit kısma) |
| `GucAyar` | Güç seviyesi ayarı |
| `PTTAyar` | PTT modu ayarı |
| `TXSureAyar` / `EOTUyari` | TX / EOT uyarı ayarı |
| `KontrastAyar` | Kontrast ayarı |
| `TersAyar` | Ters (invert) ekran ayarı |
| `KilitAyar` | Kilit ayarı |
| `MetreAyar` | S-meter (sinyal göstergesi) stili ayarı |
| `ArayuzAyar` | Arayüz yazı boyutu ayarı |
| `ZamanAyar` | Zamanlayıcı ayarı |
| `UykuAyar` | Uyku gecikmesi ayarı |
| `NFMAyar` | Dar bant (NFM) ayarı |
| `SesAyar` | Ses ayarı |
| `TusAyar` | Tuş ayarı |
| `SistemBilgi` / `PilVoltaji` | Sistem bilgisi / pil voltajı ekranı |
| `FrekansKilit` | Frekans kilidi (F Lock) |
| `Tx 200` / `Tx 350` / `Tx 500` | 200 / 350 / 500 MHz TX izni |
| `350MHzAc` | 350 MHz bandı açma |
| `KaristiriciAc` | Karıştırıcıyı açma |
| `FrekansKal` | Frekans kalibrasyonu |
| `PilKalibrasyon` | Pil voltaj kalibrasyonu |
| `PilTipi` | Pil tipi (1600 / 2200 / 3500 mAh) |
| `FabrikaSifir` | Fabrika ayarlarına sıfırlama |

### Alt menü değerleri

| Görünen | Anlamı |
|---------|--------|
| `ACIK` / `KAPALI` | Açık / Kapalı |
| `TUMUNU ACIK` / `TUMUNU KAPAT` | Tüm bantları aç / kapat |
| `GENIS` / `DAR` / `DAR+` | Geniş bant / Dar bant / Daha dar bant |
| `OZEL` | Özel (kullanıcı) güç seviyesi |
| `DUSUK 1` … `DUSUK 5` | Düşük güç seviyeleri (dinamik olarak oluşturulur) |
| `ORTA` | Orta güç |
| `YUKSEK` | Yüksek güç |
| `KUCUK` / `KLASIK` | Küçük (Tiny) / Klasik yazı stili |
| `TEK BAS` / `KLASIK` | Tek basışlı / Klasik PTT modu |
| `TUM` | Tüm açılış bilgileri (Türk bayrağı logosu modu) |
| `MESAJ` | Açılış mesajı metni |
| `VOLTAJ` | Pil voltajı |
| `SES` | Açılış sesi |
| `YOK` | Hiçbir şey gösterme |
| `CIN` / `ING` | Çince / İngilizce sesli uyarı dili |
| `FREKANS` / `KANAL NO` / `ISIM` | Kanal gösterim modu |
| `YER` / `TON` | Alarm modu (yerel / ton) |

### Ana ekran ve diğer mesajlar

| Görünen | Anlamı |
|---------|--------|
| `RX` / `TX` | Alıcı / Verici (radyo standardı olarak korundu) |
| `ARALIK` | Tarama aralığı (Scan Range) |
| `KARIS` | Karıştırıcı aktif (SCR) |
| `GOZLEM` | Monitör modu |
| `DTMF` | DTMF kod çözme aktif |
| `G` / `D` / `D+` | Kompakt bant genişliği göstergesi (Geniş / Dar / Daha dar) |
| `PIL DUSUK` | Pil düşük |
| `TX KAPALI` | Verici kapalı |
| `SURE DOLDU` | TX süre limiti doldu |
| `VOLTAJ YUKSEK` | Pil voltajı yüksek |
| `MESGUL` | Kanal meşgul |
| `KILIT AC` / `KILIDI AC` | Tuş kilidini aç |
| `HOSGELDIN` | Hoşgeldiniz |
| `BIRAK` / `TUM TUSLARI` | Bırak / tüm tuşları (kilit açma ekranı) |
| `CIKIS BAS` | Çıkış bas |
| `SIFRE` | Şifre (açılış şifresi) |
| `Turkce Surum` | Türkçe Sürüm |

> [!NOTE]
> "Kapalı" anlamındaki tüm kısaltmalar yerine **KAPALI**, "Açık" anlamındaki kısaltmalar yerine **ACIK** tam olarak yazılmıştır. Düşük güç seviyeleri `DUS 1` … `DUS 5` yerine **DUSUK 1** … **DUSUK 5** şeklinde dinamik olarak üretilmiştir. Teknik olarak uluslararası standarda bağlı kısaltmalar (DCS, CTCSS, RX, TX, PTT, VOX, FM, DTMF, MDC, NOAA, ANI, ROGER, SQL, dBm) korunmuştur.

## Merkezi string tablosu

Yeni eklenen dosyalar:

- `ui/strings.h` – Tüm UI dosyalarının paylaştığı Türkçe metinlerin bildirimleri.
- `ui/strings.c` – Bu metinlerin tanımları.

Bu tablo sayesinde `KAPALI`, `ACIK`, `YOK`, `TUM`, `TARA`, `DUSUK`, `ORTA`, `YUKSEK`, `GENIS`, `DAR`, `SES`, `GUC`, `MOD`, `PTT`, `VFO`, `RX`, `TX`, `GOZLEM`, `KARIS` gibi birden fazla ekranda geçen kelimeler tek noktadan yönetilir. `Makefile`'a `ui/strings.o` eklendi.

## Türk bayrağı logosu

- `logo_bitmap.inc` dosyası 128×64 piksel monokrom Türk bayrağı bitmap'ini içerir.
- Bayrak logosu, menüden **AcilisEkrani** seçeneği **TUM** yapıldığında açılışta tam ekran gösterilir.
- **Mesaj** modunda ise metin tabanlı açılış ekranı görünür ve alt kısımda **"Turkce Surum"** yazar.
- Diğer modlarda (Voltaj, Ses, Yok) ilgili bilgiler görünür.

## Derleme

Docker imajı daha önce oluşturulmadıysa önce şu komutla oluşturun:

```powershell
docker build -t uvk5 .
```

Ardından firmware'i derlemek için:

```powershell
docker run --rm -v ${PWD}:/app -w /app uvk5 make
```

> Git Bash kullanıyorsanız MSYS yol dönüşümünü devre dışı bırakmak gerekebilir:
> ```bash
> MSYS_NO_PATHCONV=1 docker run --rm -v "C:/Users/KULLANICI/source/uv-k5-firmware-custom:/app" -w /app uvk5 make
> ```

Derleme sonucunda `f4hwn.packed.bin` dosyası oluşur; bu dosyayı radyonuza yükleyin.

## Uyarı

Bu firmware radyonuzu kullanılamaz hale getirebilir (brick). Yüklemeden önce EEPROM yedeği almanız önerilir. Tüm sorumluluk size aittir.
