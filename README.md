# UV-K5/K6/5R Türkçe Firmware

Bu proje, [armel/uv-k5-firmware-custom](https://github.com/armel/uv-k5-firmware-custom) (F4HWN özelleştirmesi) çatalının Türkçe arayüz ile yerelleştirilmiş halidir.

## Bu fork'ta neler değişti?

- **Tam Türkçe arayüz çevirisi** yapıldı.
- Açılıştaki sürüm yazısı artık **"Turkce Surum"** olarak görünüyor.
- Açılış ekranına **tam ekran Türk bayrağı** logosu eklendi (Power-On Message **TÜM** modunda).
- Menülerde açılabilen kısaltmalar mümkün olan en uzun Türkçe karşılıklarıyla değiştirildi.
- Birden fazla yerde kullanılan tüm kelimeler tek merkezi tabloda (`ui/strings.h` / `ui/strings.c`) toplanarak dinamik referansla kullanılıyor; böylece çeviri tutarlılığı artırıldı ve gereksiz tekrar azaltıldı.
- Sol menü paneline sığmayan uzun etiketler artık **kayan yazı** ile gösteriliyor; metin yavaşça kayarak tamamı okunabiliyor.

> [!NOTE]
> Radyonun LCD fontu yalnızca 7-bit ASCII karakterleri desteklediği için Türkçe karakterler (ç, ğ, ı, ö, ş, ü, İ) ASCII karşılıklarıyla yazılmıştır. Örneğin:
> - `Güç` → `Guc`
> - `Tüm` → `Tum`
> - `Sürüm` → `Surum`
> - `Hoşgeldin` → `Hosgeldin`

## Çevrilen menüler ve ekranlar

Aşağıdaki kaynak dosyalar Türkçeleştirilmiştir:

| Dosya | Açıklama |
|-------|----------|
| `ui/menu.c` | Ana menü etiketleri ve alt menü değerleri |
| `ui/main.c` | Ana ekran / VFO göstergeleri |
| `ui/welcome.c` | Açılış (welcome) ekranı |
| `ui/fmradio.c` | FM radyo ekranı |
| `ui/aircopy.c` | Air Copy (veri kopyalama) ekranı |
| `ui/lock.c` | Tuş kilidi ekranı |
| `ui/helper.c` | Genel yardımcı mesajlar |
| `ui/scanner.c` | Tarayıcı (scanner) ekranı |
| `app/breakout.c` | Breakout oyunu ekranları |
| `ui/strings.c` / `ui/strings.h` | Ortak Türkçe metin tablosu |

`ui/menu.h` içindeki paylaşılan alt menü dizileri (`gSubMenu_OFF_ON`, `gSubMenu_W_N`, `gSubMenu_TXP`, vb.) artık `ui/strings.c`'deki tek bir kaynağı işaret eden `const char * const` dizileri şeklindedir. Düşük güç seviyeleri `DUSUK 1` … `DUSUK 5` şeklinde dinamik olarak oluşturulur.

## Çeviri notları ve kısaltmalar

LCD ekrandaki sınırlı alan yüzünden bazı kelimeler hâlâ kısaltılmıştır. Aşağıda menü başlıkları, alt menü değerleri ve diğer mesajlarda kullanılan kısaltmalar ile açıklamaları verilmiştir.

### Menü başlıkları

| Görünen | Açıklama |
|---------|----------|
| `Adim` | Kanal adımı |
| `Guc` | TX gücü |
| `RxDCS` / `RxCTCS` | Alıcı DCS / CTCSS kodu |
| `TxDCS` / `TxCTCS` | Verici DCS / CTCSS kodu |
| `TxODir` | Verici ofset yönü (Shift Direction) |
| `Ofset` | Frekans ofseti |
| `Bant` | Bant genişliği (Wide / Narrow) |
| `Karist` | Karıştırıcı (Scrambler) |
| `Mesgul` | Meşgul kanal kilidi (Busy Channel Lockout) |
| `Compnd` | Sıkıştırıcı / açıcı (Compander) |
| `Mod` | Modülasyon (AM/FM) |
| `TXKil` | TX kilidi |
| `Ekle1` / `Ekle2` / `Ekle3` | Tarama listesine ekleme |
| `Kaydet` / `Sil` | Kanalı kaydet / sil |
| `Isim` | Kanal ismi |
| `Liste` / `Liste1` / `Liste2` / `Liste3` | Tarama listeleri |
| `Tarama` | Tarama yönü / modu |
| `F1Kisa` / `F1Uzun` | F1 tuşu kısa / uzun basış fonksiyonu |
| `F2Kisa` / `F2Uzun` | F2 tuşu kısa / uzun basış fonksiyonu |
| `MUzun` | M tuşu uzun basış fonksiyonu |
| `Kilit` | Otomatik tuş kilidi |
| `TXSure` | TX Süre / TOT (Time-Out Timer) |
| `PilTas` | Pil tasarrufu |
| `PilGor` | Pil göstergesi |
| `KanGor` | Kanal göstergesi |
| `Acilis` | Açılış mesajı |
| `BLZmn` | Arka ışık zamanı |
| `BLMin` / `BLMax` | Arka ışık minimum / maksimum seviyesi |
| `BLTxRx` | Arka ışık TX/RX davranışı |
| `Bip` | Tuş bip sesi |
| `Roger` | Roger beep |
| `STE` / `RP STE` | Squelch kuyruk kesme |
| `1 Ara` | Tek kanal arama |
| `Alarm` | Alarm modu |
| `D Dur` | DTMF başlangıç durumu |
| `DCevap` | DTMF yanıt modu |
| `DBekle` | DTMF tutma süresi |
| `DGecik` | DTMF gecikme (pre-load) |
| `DKodCo` | DTMF kod çözücü |
| `DListe` | DTMF liste |
| `DCanli` | DTMF canlı çözücü |
| `YukKod` / `AsaKod` | Yukarı / Aşağı DTMF kodu |
| `PTT ID` | PTT tanıtma kimliği |
| `VOX` | Sesle tetikleme |
| `RXModu` | RX modu (RX Mode) |
| `Sql` | Squelch (parazit kısma) |
| `SetGuc` | Güç seviyesi ayarı |
| `SetPTT` | PTT modu ayarı |
| `SetTOT` / `SetEOT` | TX / EOT uyarı ayarı |
| `SetKon` | Kontrast ayarı |
| `SetTrs` | Ters (invert) ekran ayarı |
| `SetKil` | Kilit ayarı |
| `SetMet` | S-meter (sinyal göstergesi) stili ayarı |
| `SetGUI` | Arayüz yazı boyutu ayarı |
| `SetZmn` | Zamanlayıcı ayarı |
| `SetKpt` | Uyku gecikmesi ayarı |
| `SetNFM` | Dar bant (NFM) ayarı |
| `FKilit` | Frekans kilidi (F Lock) |
| `Tx 200` / `Tx 350` / `Tx 500` | 200 / 350 / 500 MHz TX izni |
| `350 Ac` | 350 MHz bandı açma |
| `KarAc` | Karıştırıcıyı açma |
| `FrKal` | Frekans kalibrasyonu |
| `PilKal` | Pil voltaj kalibrasyonu |
| `PilTip` | Pil tipi (1600 / 2200 / 3500 mAh) |
| `Sifir` | Fabrika ayarlarına sıfırlama |

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

## Kayan menü etiketleri

Sol menü paneli 6 büyük karakterlik (`48 piksel`) bir alana sahip. Bu alana sığmayan etiketler için `ui/menu.c`'de `UI_PrintMenuLabelScroll()` fonksiyonu eklendi.

- Seçili menü öğesinin etiketi panelden uzunsa metin yavaşça sağa kayar, sona ulaştığında geri döner.
- Kayma hızı yaklaşık **200 ms**'de bir piksel olarak ayarlanmıştır.
- Sola/sağa git-gel (ping-pong) yaparak hem başlangıcı hem sonunu okumak mümkündür.
- Kısa etiketler eskisi gibi sabit kalır.

## Türk bayrağı logosu

- `logo_bitmap.inc` dosyası 128×64 piksel monokrom Türk bayrağı bitmap'ini içerir.
- Bayrak logosu, menüden **Acilis** seçeneği **TUM** yapıldığında açılışta tam ekran gösterilir.
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
